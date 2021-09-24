<?php

/**
 * @file
 * The facetapi_links widget plugin classes.
 */

/**
 * Widget that renders facets as a list of clickable links.
 *
 * Links make it easy for users to narrow down their search results by clicking
 * on them. The render arrays use theme_item_list() to generate the HTML markup.
 */
class GofastFacetapiWidgetLinks extends FacetapiWidget {

  /**
   * Overrides FacetapiWidget::__construct().
   *
   * For links, it is better to use the machine name of the facet as opposed to
   * the alias for the key. Alias are usually, but not necessarily, unique. It
   * doesn't make sense to group links in the same element as they are usually
   * rendered in blocks with are separate from one another.
   */
  public function __construct($id, array $realm, FacetapiFacet $facet, stdClass $settings) {
    parent::__construct($id, $realm, $facet, $settings);
    $this->jsSettings['limit'] = $this->settings->settings['soft_limit'];
    $this->key = $facet['name'];
  }

  /**
   * Implements FacetapiWidget::execute().
   *
   * Transforms the render array into something that can be themed by
   * theme_item_list().
   *
   * @see FacetapiWidgetLinks::setThemeHooks()
   * @see FacetapiWidgetLinks::buildListItems()
   */
  public function execute() {
    $element = &$this->build[$this->facet['field alias']];

    // Sets each item's theme hook.
    $this->setThemeHooks($element);

    // Add settings for collapsible facets.
    $settings = $this->settings->settings;
    $keep_open = isset($settings['keep_open']) ? $settings['keep_open'] : 0;
    
    // Hardcoded override here as defaults are not relaiable.
    $expand = 0;// isset($settings['expand']) ? $settings['expand'] : 0;
    $collapsible_children = isset($settings['collapsible_children']) ? $settings['collapsible_children'] : 1;
    
    $js_settings = array(
      'gofast_search' => array(
        $this->facet['field alias'] => array(
          'keep_open' => $keep_open,
          'expand' => $expand,
          'collapsible_children' => $collapsible_children
        )
      )
    );
      
    // Builds item list, apply setttings.
    $element = array(
      '#theme' => 'item_list',
      '#items' => $this->buildListItems($element),
      '#prefix' => '<div class="facet-collapsible-wrapper" id="facet-collapsible-' . str_replace('_', '-', $this->facet['field alias']) .'">',
      '#suffix' => '</div>',
      '#attributes' => array_merge_recursive($this->build['#attributes'], array('class' => array('facetapi-collapsible'))),
      '#attached' => array(
        'css' => array(drupal_get_path('module', 'gofast_search') .'/css/facetapi_collapsible.css'),
        'library' => array(array('system', 'jquery.cookie')),
        'js' => array(
          drupal_get_path('module', 'gofast_search') .'/js/facetapi_collapsible.js' => array(
            'group' => JS_DEFAULT + 1
          ),
          array(
            'type' => 'setting',
            'data' => $js_settings
          )
        )
      )
    );
  }

  /**
   * Recursive function that sets each item's theme hook.
   *
   * The indivual items will be rendered by different theme hooks depending on
   * whether or not they are active.
   *
   * @param array &$build
   *   A render array containing the facet items.
   *
   * @return FacetapiWidget
   *   An instance of this class.
   *
   * @see theme_facetapi_link_active()
   * @see theme_facetapi_link_inactive()
   */
  protected function setThemeHooks(array &$build) {
    foreach ($build as $value => &$item) {
      $item['#theme'] = ($item['#active']) ? 'facetapi_link_active' : 'facetapi_link_inactive';
      if (!empty($item['#item_children'])) {
        $this->setThemeHooks($item['#item_children']);
      }
    }
    return $this;
  }

  /**
   * Transforms the render array for use with theme_item_list().
   *
   * The recursion allows this function to act on the various levels of a
   * hierarchical data set.
   *
   * @param array $build
   *   The items in the facet's render array being transformed.
   *
   * @return array
   *   The "items" parameter for theme_item_list().
   */
  function buildListItems($build) {
    $settings = $this->settings->settings;
     
    // Initializes links attributes, adds rel="nofollow" if configured.
    $attributes = ($settings['nofollow']) ? array('rel' => 'nofollow') : array();
    $attributes += array('class' => $this->getItemClasses());

    // Builds rows.
    $items = array();
    foreach ($build as $value => $item) {
      $row = array('class' => array());

      // Allow adding classes via altering.
      if (isset($item['#class'])) {
        $attributes['class'] = array_merge($attributes['class'], $item['#class']);
      }
      // Initializes variables passed to theme hook.
      $variables = array(
        'text' => $item['#markup'],
        'path' => $item['#path'],
        'count' => $item['#count'],
        'options' => array(
          'attributes' => $attributes,
          'html' => $item['#html'],
          'query' => $item['#query'],
          'field alias' => $this->facet['field alias'],
          'value' => $value
        )
      );

      // Adds the facetapi-zero-results class to items that have no results.
      if (!$item['#count']) {
        $variables['options']['attributes']['class'][] = 'facetapi-zero-results';
      }

      // Add an ID to identify this link.
      $variables['options']['attributes']['id'] = drupal_html_id('facetapi-link');

      // If the item has no children, it is a leaf.
      if (empty($item['#item_children'])) {
        $row['class'][] = 'leaf';
      }
      else {
        $row['children'] = $this->buildListItems($item['#item_children']);
        // If the item is active or the "show_expanded" setting is selected,
        // show this item as expanded so we see its children.
        $row['class'][] = $item['#active'] || empty($settings['show_expanded']) ? 'expanded' : 'collapsed';
      }

      // Gets theme hook, adds last minute classes.
      $class = ($item['#active']) ? 'facetapi-active' : 'facetapi-inactive';
      $variables['options']['attributes']['class'][] = $class;

      // Themes the link, adds row to items.
      $row['data'] = theme($item['#theme'], $variables);
      $items[] = $row;
    }

    return $items;
  }

  /**
   * Gets the base class array for a facet item.
   *
   * Classes that extend FacetapiWidgetLinks will often overide this method to
   * alter the link displays via CSS without having to touch the render array.
   *
   * @return array
   *   An array of classes.
   */
  function getItemClasses() {
    return array();
  }

  /**
   * Overrides FacetapiWidget::settingsForm().
   */
  function settingsForm(&$form, &$form_state) {
    // @see http://drupal.org/node/735528 for supporting multiple values in the
    // FAPI #states. The following hack adds multiple form elements and uses CSS
    // and JavaScript to ensure only one is displayed at a time. Only the last
    // form element actually passes the value.
    $form['widget']['widget_settings']['links'][$this->id]['soft_limit'] = array(
      '#type' => 'select',
      '#title' => t('Soft limit', array(), array('context' => 'gofast:gofast_search')),
      '#default_value' => $this->getSetting('soft_limit'),
      '#options' => array(0 => t('No limit', array(), array('context' => 'gofast:gofast_search'))) + drupal_map_assoc(array(50, 40, 30, 20, 15, 10, 5, 3)),
      '#description' => t('Limits the number of displayed facets via JavaScript.', array(), array('context' => 'gofast:gofast_search')),
      '#states' => array(
        'visible' => array(
          'select[name="widget"]' => array('value' => $this->id),
        )
      )
    );

    // @see http://drupal.org/node/1370342
    $form['widget']['widget_settings']['links'][$this->id]['nofollow'] = array(
      '#type' => 'checkbox',
      '#title' => t('Prevent crawlers from following facet links', array(), array('context' => 'gofast:gofast_search')),
      '#default_value' => $this->getSetting('nofollow'),
      '#description' => t('Add the <code>rel="nofollow"</code> attribute to facet links to maximize SEO '
                        .'by preventing crawlers from indexing duplicate content and getting stuck in loops.'
                        , array(), array('context' => 'gofast:gofast_search')),
      '#states' => array(
        'visible' => array(
          'select[name="widget"]' => array('value' => $this->id),
        )
      )
    );

    // @see http://drupal.org/node/735528
    /**
     * We have a bug with the option 'show_expanded' (described in comments,  
     * link above) : when #default_value is set to 0, user cannot check the
     * see checkbox, when it is set to 1, user can uncheck it but setting 
     * won't  apply the form submission.
     */
    if ($this->facet['hierarchy callback']) {
      $form['widget']['widget_settings']['links'][$this->id]['show_expanded'] = array(
        '#type' => 'checkbox',
        '#title' => t('Expand hierarchy', array(), array('context' => 'gofast:gofast_search')),
        '#default_value' => $this->getSetting('show_expanded'),
        '#description' => t('Show the entire tree regardless of whether the parent items are active.', array(), array('context' => 'gofast:gofast_search')),
        '#states' => array(
          'visible' => array(
            'select[name="widget"]' => array('value' => $this->id),
          )
        )
      );

      // We do want some of our facets to be 'expanded', so we have no other
      // choice but to hardcode this settings.
      $date_queries = gofast_facet_check_query_type($this->settings->facet, 'date_queries');
      $og_hierarchy = $this->settings->facet === 'sm_' . GOFAST_OG_CONTENT_MEMBERSHIP_FIELD;
      if ($date_queries || $og_hierarchy) {
        $form['widget']['widget_settings']['links'][$this->id]['show_expanded']['#default_value'] = 1;
      }
    }

    // Hides all but the last element. The #states system will override this,
    // however it is necessary if JavaScript is disabled so multiple elements
    // aren't displayed to the user.
    $last = end($form['widget']['widget_settings']['links']);
    foreach ($form['widget']['widget_settings']['links'] as $id => $element) {
      if ($last != $element) {
        $form['widget']['widget_settings']['links'][$id]['#attributes']['style'] = 'display: none;';
      }
    }
    
    // Collapsible Facets
    
    $form['widget']['widget_settings']['collapsible_links'][$this->id] = array(
      // Keep expanded facet blocks expanded when expanding another facet.
      'keep_open' => array(
        '#type' => 'checkbox',
        '#title' => t('Keep open', array(), array('context' => 'gofast:gofast_search')),
        '#default_value' => $this->getSetting('keep_open'),
        '#description' => t('If checked, facets that are already expanded will stay expanded when you click on another facet, otherwise they will close.'
                          , array(), array('context' => 'gofast:gofast_search')),
        '#states' => array(
          'visible' => array(
            'select[name="widget"]' => array('value' => $this->id)
          )
        )
      ),
      // Expand facet block even there is no active link.
      'expand' => array(
        '#type' => 'checkbox',
        '#title' => t('Expand', array(), array('context' => 'gofast:gofast_search')),
        '#default_value' => $this->getSetting('expand'),
        '#description' => t('If checked, this facet will automatically expand.', array(), array('context' => 'gofast:gofast_search')),
        '#states' => array(
          'visible' => array(
            'select[name="widget"]' => array('value' => $this->id)
          )
        )
      ),
      // Expand facet block even there is no active link.
      'collapsible_children' => array(
        '#type' => 'checkbox',
        '#title' => t('Collapsible children', array(), array('context' => 'gofast:gofast_search')),
        '#default_value' => $this->getSetting('collapsible_children'),
        '#description' => t('If checked, this facet\'s children will be collapsible as well.', array(), array('context' => 'gofast:gofast_search')),
        '#states' => array(
          'visible' => array(
            'select[name="widget"]' => array('value' => $this->id)
          )
        )
      )
    );    
  }
  
/**
 * Get a setting value, or an array of settings. This function ensures to get a 
 * value if set, or fallback to default if not.
 * 
 * @param mixed $setting [optional] 
 *  A setting name, or a falsy value. Default to FALSE.
 * 
 * @return mixed 
 *  A setting value or an array of settings depending on the parameter.
 */
  function getSetting($setting = FALSE) {
    $settings = $this->settings->settings + $this->getDefaultSettings();  
    if ($setting && isset($settings[$setting])) {
      return $settings[$setting];
    }
    return $settings;
  }

  /**
   * Overrides FacetapiWidget::getDefaultSettings().
   * Provides default values for the plugin settings.
   *
   * All settings added via FacetapiWidget::settingsForm() should have
   * corresponding defaults in this method.
   *
   * @return array
   *   The defaults keyed by setting name to value.
   */
  function getDefaultSettings() {
    return array(
      'soft_limit' => 0,
      'nofollow' => 1,
      'show_expanded' => 0,
      'keep_open' => 1,
      'expand' => 0, 
      'collapsible_children' => 1
    );
  }
}
