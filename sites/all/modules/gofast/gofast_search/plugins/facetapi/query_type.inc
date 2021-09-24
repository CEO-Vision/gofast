<?php

/**
 * @file
 * Date query/range type plugin for the Apache Solr adapter.
 */

/**
 * Plugin for building range + query date facetting.
 * 
 * facet.query is used to get customized date facetting (one day/week/month in 
 * the past or in the future from now). 
 * 
 * facet.range is used to get contextual date ranges with possibly different 
 * gaps on the same field in order to provide a hierarchical build. 
 * 
 * @extends FacetapiQueryTypeDate
 * @implements FacetapiQueryTypeInterface
 */
class GofastFacetapiDate extends FacetapiQueryTypeDate implements FacetapiQueryTypeInterface {
  
  /**
   * The adapter associated with facet being queried.
   *
   * @var FacetapiAdapter
   */
  protected $adapter;

  /**
   * The facet definition as returned by facetapi_facet_load().
   *
   * @var array
   */
  protected $facet;

  /**
   * Constructs a FacetapiQueryType object.
   *
   * @param FacetapiAdapter $adapter
   *   The adapter object associated with facet being queried.
   * @param array $facet
   *   The facet definition as returned by facetapi_facet_load().
   */
  public function __construct(FacetapiAdapter $adapter, array $facet) {
    module_load_include('inc', 'facetapi', 'facetapi.date');
    $this->adapter = $adapter;
    $this->facet = $facet;
  }
  
  /**
   * Defines facet query strings contants with custom date ranges.
   * 
   * The purpose of rounding down/up 'NOW' to the start/end of the current hour 
   * is to enable the use of Solr filterCache.
   */
  
  /**
   * Defines date ranges of one day/week/month in the past from now.
   */
  
  const GOFAST_FACET_QUERY_PAST_MONTH   = '[NOW/HOUR-1MONTH TO NOW/HOUR+1HOUR]';
  const GOFAST_FACET_QUERY_PAST_WEEK    = '[NOW/HOUR-7DAYS TO NOW/HOUR+1HOUR]';
  const GOFAST_FACET_QUERY_PAST_DAY     = '[NOW+1HOUR/HOUR-1DAY TO NOW/HOUR+1HOUR]';

  /**
   * Defines date ranges of one day/week/month in the future from now.
   */
  
  const GOFAST_FACET_QUERY_FUTURE_MONTH = '[NOW/HOUR+1HOUR TO NOW/HOUR+1MONTH]';
  const GOFAST_FACET_QUERY_FUTURE_WEEK  = '[NOW/HOUR+1HOUR TO NOW+7DAYS/HOUR]';
  const GOFAST_FACET_QUERY_FUTURE_DAY   = '[NOW/HOUR TO NOW/HOUR+1DAY]';
  
  /**
   * Identifier for a main date range facet, used to distinguish it from its 
   * children if any. 
   */
  const GOFAST_FACET_RANGE_KEY = 'range_main';
  
  /**
   * Identifier for nested date range facet, used to distinguish it from its 
   * parent. 
   */
  const GOFAST_FACET_RANGE_CHILDREN_KEY = 'range_children';
  
  /**
   * Returns the query type associated with the plugin.
   *
   * @return string
   *   The query type.
   */
  static public function getType() {
    return 'date_queries';
  }
  
  /**
   * Returns past date ranges as facet queries.
   * 
   * @return array
   *  The date range queries.
   */
  public function pastDateRangeQueries () {
    return array(
      $this->facet['field'] . ': '. self::GOFAST_FACET_QUERY_PAST_DAY,
      $this->facet['field'] . ': '. self::GOFAST_FACET_QUERY_PAST_WEEK,
      $this->facet['field'] . ': '. self::GOFAST_FACET_QUERY_PAST_MONTH,
    );
  }
  
  /**
   * Returns future date ranges as facet queries.
   * 
   * @return array
   *  The date range queries.
   */
  public function futureDateRangeQueries () {
    return array(
      $this->facet['field'] . ': '. self::GOFAST_FACET_QUERY_FUTURE_DAY,
      $this->facet['field'] . ': '. self::GOFAST_FACET_QUERY_FUTURE_WEEK,
      $this->facet['field'] . ': '. self::GOFAST_FACET_QUERY_FUTURE_MONTH,
    );
  }
  
  /**
   * Returns date range types for this facet.
   */
  public function getDateRangeTypes () {
    return isset($this->facet['range types']) ? $this->facet['range types'] : array('past');
  }
  
  /**
   * Returns custom date ranges as facet queries.
   * 
   * @return array
   *  The date range queries.
   */
  public function getDateRangeQueries () {
    $range_queries = array();
    foreach ($this->getDateRangeTypes() as $type) {
      if (!method_exists($this, $callback = $type . 'DateRangeQueries')) {
        continue;
      }
      $range_queries = array_merge($range_queries, $this->{$callback}());
    }
    return array_unique($range_queries);
  }
  
  /**
   * Returns a facet field identifier for the current facet. 
   * 
   * @return string
   */
  public function getDateRangeFacetIdentifier () {
    return $this->facet['field'] . '_' . self::GOFAST_FACET_RANGE_KEY;
  }  
  
  /**
   * Returns a facet field identifier for the current facet (nested range). 
   * 
   * @return string
   */
  public function getDateRangeChildrenFacetIdentifier () {
    return $this->facet['field'] . '_' . self::GOFAST_FACET_RANGE_CHILDREN_KEY;
  }    
  
  /**
   * Gets the range of dates we are using.
   * 
   * @return array 
   *  An array containing the gap and range information.
   */
  function getDateRange() {
    $return = NULL;
    
    // Attempts to get next gap from passed date filters.
    foreach ($this->adapter->getActiveItems($this->facet) as $value => $item) {
      if ($gap = facetapi_get_date_gap($item['start'], $item['end'])) {
        $next_gap = facetapi_get_next_date_gap($gap, FACETAPI_DATE_SECOND);
        if ($next_gap == $gap) {
          $next_gap = NULL;
          return;
        }
        $return = array(
          "{$item['start']}/$next_gap",
          "{$item['end']}+1$next_gap/$next_gap",
          "+1$next_gap",
        );
      }
    }      

    // If no filters were passed, get default range.
    if ($return === NULL) {
      
      // Builds SQL that gets minimum and maximum values from node table.
      $minimum = $maximum = FALSE;
      if ($this->facet['min callback'] && is_callable($this->facet['min callback'])) {
        $minimum = $this->facet['min callback']($this->facet);
      }
      if ($this->facet['max callback'] && is_callable($this->facet['max callback'])) {
        $maximum = $this->facet['max callback']($this->facet);
      }

      // Gets the default gap.
      $gap = FACETAPI_DATE_YEAR;
      if ($minimum && $maximum) {
        $gap = facetapi_get_timestamp_gap($minimum, $maximum);
        $minimum = facetapi_isodate($minimum, $gap);
        $maximum = facetapi_isodate($maximum, $gap);
        $return = array(
          "$minimum/$gap",
          "$maximum+1$gap/$gap",
          "+1$gap",
        );
      }
    }

    return $return;
  }
  
  
  /**
   * Gets the range of dates for inactive children items.
   * 
   * @return array
   *   An array containing the gap and range information.
   */
  function getDateRangeChildren($current = NULL) {
    if (empty($current)) {
      $current = $this->getDateRange();
    }
    
    list ($start, $end, $gap) = $current;
    $start = preg_replace('/\/.*$/', '', $start);
    $end = preg_replace('/\+1.*$/', '', $end);
    $gap = preg_replace('/[^A-Z]/', '', $gap);
    
    // Attempts to get next gap from passed date filters.
    $next_gap = facetapi_get_next_date_gap($gap, FACETAPI_DATE_SECOND);
    
    return $next_gap == $gap ? NULL : array(
      "{$start}/{$next_gap}",
      "{$end}+1{$gap}/{$next_gap}",
      "+1{$next_gap}",
    );
  }
   
  /**
   * Adds the filter to the query object.
   *
   * @param DrupalSolrQueryInterface $query
   *   An object containing the query in the backend's native API.
   */
  public function execute($query) {
    // Gets the date range in formats that Solr understands.
    $date_range = $this->getDateRange($query);
    if (empty($date_range)) {
      return;
    }
    
    list ($start, $end, $gap) = $date_range;
    
    // Use local parameters to define facet.range because we can't get multiple 
    // ranges on the same facet field otherwise (ie. ranges with different gaps 
    // would override each other). We use !key param to distinguish a main (or 
    // parent) range facet from its children. 
    $key = $this->getDateRangeFacetIdentifier();
    $start = 'f.' . $this->facet['field'] . '.facet.range.start=' . $start;
    $end = 'f.' . $this->facet['field'] . '.facet.range.end=' . $end;
    $gap = 'f.' . $this->facet['field'] . '.facet.range.gap=' . $gap;
    $local_params = implode(' ', [$start, $end, $gap]);
    $query->addParam('facet.range', '{!key=' . $key . ' ' . $local_params . '}' . $this->facet['field']);
    
    // Try to get an appropriated date range for any facets children.
    $next_date_range = $this->getDateRangeChildren();
    
    if ($next_date_range !== NULL) {
      list ($start, $end, $gap) = $this->getDateRangeChildren();
      $child_key = $this->getDateRangeChildrenFacetIdentifier();
      $start = 'f.' . $this->facet['field'] . '.facet.range.start=' . $start;
      $end = 'f.' . $this->facet['field'] . '.facet.range.end=' . $end;
      $gap = 'f.' . $this->facet['field'] . '.facet.range.gap=' . $gap;
      $local_params = implode(' ', [$start, $end, $gap]);
      $query->addParam('facet.range', '{!key=' . $child_key . ' ' . $local_params . '}' . $this->facet['field']);      
    }
    
    // Adds custom ranges using solr facet queries.
    $query->addParam('facet.query', $this->getDateRangeQueries());
    
    // Adds "hard limit" parameter to prevent too many return values.
    $settings = $this->adapter->getFacet($this->facet)->getSettings();
    $limit = empty($settings->settings['hard_limit']) ? 20 : (int) $settings->settings['hard_limit'];
    $query->addParam('f.' . $this->facet['field'] . '.facet.limit', $limit);    
    
    // Adds "facet mincount" parameter to limit the number of facets.
    if (isset($settings->settings['facet_mincount'])) {
      $count = $settings->settings['facet_mincount'];
      $query->addParam('f.' . $this->facet['field'] . '.facet.mincount', $count);
    }

    // Adds the filter to the query object.
    foreach ($this->adapter->getActiveItems($this->facet) as $value => $item) {
      $query->addFilter($this->facet['field'], $value);
    }

  }


  /**
   * Initializes the facet's build array.
   *
   * @return array
   *   The initialized render array.
   */
  public function build() {
    // Initializes build and gets static response.
    if (!$response = apachesolr_static_response_cache($this->adapter->getSearcher())) {
      return array();
    }
    $build = array();

    // Gets total number of documents matched in search.
    $total = $response->response->numFound;

    // Gets the active date facets, starts to builds the "parent - child"
    // relationships.
    $parent = NULL;
    foreach ($this->adapter->getActiveItems($this->facet) as $value => $item) {
      // Builds the raw facet "value", the count for selected items will be the
      // total number of rows returned in the query.
      $build[$value] = array('#count' => $total);

      // If there is a previous item, there is a parent, uses a reference so the
      // arrays are populated when they are updated.
      if ($parent !== NULL) {
        $build[$parent]['#item_children'][$value] = &$build[$value];
        $build[$value]['#item_parents'][$parent] = $parent;
      }

      // Stores the last value iterated over.
      $parent = $value;
    }

    // Gets raw facet data from the Solr server.
    $raw_data = $raw_data_children = array(); 
    
    $key = $this->getDateRangeFacetIdentifier();
    if (isset($response->facet_counts->facet_ranges) && isset($response->facet_counts->facet_ranges->{$key})) {
      $raw_data = (array) $response->facet_counts->facet_ranges->{$key}->counts;
      $gap = $response->facet_counts->facet_ranges->{$key}->gap;
    }
    
    $child_key = $this->getDateRangeChildrenFacetIdentifier();
    if (isset($response->facet_counts->facet_ranges) && isset($response->facet_counts->facet_ranges->{$child_key}->counts)) {
      $raw_data_children = (array) $response->facet_counts->facet_ranges->{$child_key}->counts;
      $children_gap = $response->facet_counts->facet_ranges->{$child_key}->gap;
    }
    
    // We cannot list anything below a minute (range of 00 till 59 seconds).
    if (isset($gap) && $gap != '+1SECOND') {
      // Builds facet counts object used by the server.
      foreach ($raw_data as $value => $count) {
        if ($count) {
          $to = facetapi_isodate(strtotime($value . $gap));
          $new_value = '[' . $value . ' TO ' . $to . ']';
          $build[$new_value] = array('#count' => $count, '#active' => 0);
          
          // If there is an active parent item, process the hierarchy.
          if ($parent !== NULL) {
            $build[$parent]['#item_children'][$new_value] = &$build[$new_value];
            $build[$new_value]['#item_parents'][$parent] = $parent;
          }
          
          if (!empty($raw_data_children)) {
            // Grab (inactive) facets children.
            $_parent = $new_value;
            $children_count = $child_pos = 0;
            
            foreach ($raw_data_children as $child => $child_count) {
              $children_count += $child_count; $child_pos++;
              $to = facetapi_isodate(strtotime($child . $children_gap));
              $new_child = '[' . $child . ' TO ' . $to . ']';
              $build[$new_child] = array(
                '#count' => $child_count,
                '#active' => 0,
                '#item_parents' => array($_parent => $_parent)
               );
              // Use a reference so the tree updates itself when populated.
              $build[$_parent]['#item_children'][$new_child] = &$build[$new_child];
              if ($children_count === $count) {
                // Remove processed data for next iterations and break the loop.
                array_splice($raw_data_children, 0, $child_pos);
                break 1;
              }
            }
          }
        }
      }
    }
    
    // Merge in facet queries output (custom date ranges).
    $settings = $this->adapter->getFacet($this->facet)->getSettings();
    foreach ($this->getDateRangeQueries() as $query) {
      if (isset($response->facet_counts->facet_queries->{$query})) {
        list (, $range) = explode(': ', $query);
        $count = $response->facet_counts->facet_queries->{$query};
        // Facet missing may return 0 even if mincount is 1.
        if (empty($settings->settings['facet_mincount']) || $count) {
          $build[$range] = array('#count' => $count);
        }
      }
    }

    return ($build);
  }
  
  /**
   * Overrides FacetapiQueryType::extract().
   *
   * Adds the "start" and "end" values for the range using appropriated regex.
   */
  public function extract(array $item) {
    $return = array();
    if (preg_match(FACETAPI_REGEX_RANGE, $item['value'], $matches)) {
      $return['start'] = $matches[1];
      $return['end'] = $matches[2];
    }
    return $return;
  }  
}
