<?php

namespace Drupal\gofast_webform\Service;

use Drupal\gofast_core\Utils\RequestUtils;

/**
 * Service class for handling Drupal 7 webforms.
 */
class SurveyServiceD7 {

  /**
   * Constructor for the SurveyServiceD7 class.
   *
   * This method is intentionally left empty
   *  because there is no specific initialization logic required at the moment.
   * If any initialization logic needs to be added in the future
   *  it can be implemented here.
   */
  public function __construct() {
  }

  /**
   * Retrieves the Drupal 7 webform data for a given node ID.
   *
   * @param int $nid
   *   The node ID of the webform.
   *
   * @return string
   *   The webform data as a string.
   */
  public function getDrupal7Webform($nid) {
    $hostname = $_SERVER['HTTP_HOST'];
    $endpoint = "https://$hostname/api/webform/webform?nid={$nid}";
    $response = RequestUtils::request($endpoint, "GET");
    return $response->getBody()->getContents();
  }

  /**
   * Sets the Drupal 7 webform.
   *
   * @param int $nid
   *   The node ID of the webform.
   * @param array $data
   *   The data to be sent to the webform.
   *
   * @return string
   *   The response from the webform API.
   */
  public function setDrupal7Webform($nid, $data) {
    $hostname = $_SERVER['HTTP_HOST'];
    $endpoint = "https://$hostname/api/webform/webform";
    $response = RequestUtils::request(
      $endpoint,
      "POST",
      ["Content-Type" => "application/json"],
      ["nid" => $nid, "data" => $data]
    );
    $response = $response->getBody()->getContents();
    return $response;
  }

  /**
   * Retrieves the survey values for a given webform.
   *
   * @param int $nid
   *   The node ID of the webform.
   *
   * @return array
   *   The survey elements in SurveyJS format.
   *
   * @throws \Exception
   *   If the webform is not found.
   */
  public function getSurveyValues($nid) {
    $webform_data = json_decode($this->getDrupal7Webform($nid), TRUE);
    $webform = json_decode($webform_data['webform'], TRUE);
    if (empty($webform)) {
      throw new \Exception('Webform not found');
    }

    // Get form custom settings.
    $customProperties = [];
    if (!empty($webform['field_custom_properties'])) {
      $customProperties = json_decode($webform['field_custom_properties'], TRUE);
    }
    $elements = $webform['components'];

    // Transform it to SurveyJS format.
    $surveyElements = self::convertToSurvey($elements);
    $survey = [
      'surveyElements' => $surveyElements + $customProperties,
      'surveyTheme' => isset($webform_data['theme']) ? json_decode($webform_data['theme'], TRUE) : NULL,
    ];
    return $survey;
  }

  /**
   * Set the Survey values to the webform.
   *
   * @param int $nid
   *   The ID of the webform node.
   * @param string $surveyJson
   *   The SurveyJS JSON string.
   */
  public function setWebformValues($nid, $surveyJson) {
    $webform = json_decode($this->getDrupal7Webform($nid), TRUE)['webform'];

    if (!$webform) {
      throw new \Exception('Webform not found');
    }

    // surveyOptions is an array of surveyJson without $surveyJson['pages'].
    $surveyOptions = $surveyJson;
    unset($surveyOptions['pages']);

    // Transform SurveyJS JSON to Webform elements.
    $webformElements = self::convertToWebform($nid, $surveyJson);
    $webformElements['field_custom_properties'] = json_encode($surveyOptions);
    return $this->setDrupal7Webform($nid, json_encode($webformElements));
  }

  /**
   * Retrieves the webform submissions for a given node ID.
   *
   * @param int $nid
   *   The node ID of the webform.
   *
   * @return string
   *   The response body of the webform submissions.
   */
  public function getWebformSubmissions($nid) {
    $hostname = $_SERVER['HTTP_HOST'];
    $endpoint = "https://$hostname/api/webform/webform_submissions?nid={$nid}";
    $response = RequestUtils::request($endpoint, "GET");
    return $response->getBody()->getContents();
  }

  /**
   * Sets the webform submissions for a given node ID.
   *
   * @param int $nid
   *   The node ID.
   * @param array $data
   *   The data to be submitted.
   *
   * @return string
   *   The response from the API.
   */
  public function setWebformSubmissions($nid, $data) {
    $hostname = $_SERVER['HTTP_HOST'];
    $endpoint = "https://$hostname/api/webform/webform_submissions";
    $response = RequestUtils::request(
      $endpoint,
      "POST",
      ["Content-Type" => "application/json"],
      ["nid" => $nid, "data" => $data]
    );
    $response = $response->getBody()->getContents();
    return $response;
  }

  /**
   * Converts a SurveyJS JSON to a Webform JSON.
   *
   * @param int $nid
   *   The node ID of the webform.
   * @param array $surveyArray
   *   The SurveyJS JSON to convert.
   *
   * @return array
   *   The converted Webform JSON.
   */
  private static function convertToWebform($nid, $surveyArray) {
    $webformElements = [];
    if (isset($surveyArray['pages'])) {
      $cid = 1;
      foreach ($surveyArray['pages'] as $key => $page) {

        if ($cid != 1) {
          // Add page break.
          $webformElements[$cid] = [
            'nid' => $nid,
            'pid' => 0,
            'form_key' => 'page_break',
            'name' => 'Page Break',
            'type' => 'page_break',
            'value' => '',
            'weight' => 0,
            'extra' => [
              'page_title' => $page['name'],
              'page_description' => '',
            ],
          ];
          $cid++;
        }
        if (isset($page['elements'])) {
          foreach ($page['elements'] as $element) {
            $webformElement = self::convertElementToWebformElement($nid, $element);
            // Add page number.
            $webformElement['page_num'] = $key + 1;
            $webformElement['cid'] = $cid;
            $webformElements[$cid] = $webformElement;
            $parent_cid = $cid;
            $cid++;
            if (isset($webformElement['elements']) && !empty($webformElement['elements'])) {
              unset($webformElements[$parent_cid]['elements']);
              $webformElements = array_merge($webformElements, self::getFlatElements($webformElement['elements'], $parent_cid, $cid));
            }
          }
        }
      }
    }
    return $webformElements;
  }

  /**
   * Converts an array of elements into a survey JSON format.
   *
   * @param array $elements
   *   The array of elements to convert.
   *
   * @return array
   *   The survey JSON format.
   */
  private static function convertToSurvey($elements) {
    $surveyJson = [
      'pages' => [],
    ];

    asort($elements);
    $num_page = 0;
    foreach ($elements as $element) {
      // Check if the element is a page break.
      if ($element['type'] === 'page_break') {
        $page = [
          'name' => $element['extra']['page_title'],
          'elements' => [],
        ];
        $num_page++;
        $surveyJson['pages'][$num_page] = $page;
      }
      else {

        // We dont want to include these elements.
        if (in_array($element['form_key'], ['timeSpent', 'score', 'percentage', 'submissionPdf'])) {
          continue;
        }

        // Regular element outside of any wizard.
        $elementData = self::convertElementToSurveyElement($element);

        // Assuming these elements belong to a default page.
        if (empty($surveyJson['pages'])) {
          $surveyJson['pages'][$num_page] = ['name' => 'Default Page', 'elements' => []];
        }
        self::addElementToPage($surveyJson['pages'][$num_page]['elements'], $elementData);
      }
    }
    return $surveyJson;
  }

  /**
   * Recursively flattens the nested elements of a webform.
   *
   * This function takes an array of webform elements and recursively flattens
   * the nested elements into a single-dimensional arrayEach element is assigned
   * a unique cid (component ID)
   * a parent_cid (parent component ID) to maintain
   * the hierarchical structure of the webform.
   *
   * @param array $elements
   *   The array of webform elements to flatten.
   * @param int $parent_cid
   *   The parent component ID of the current element.
   * @param int $cid
   *   The current component ID.
   *
   * @return array
   *   The flattened array of webform elements.
   */
  private static function getFlatElements($elements, $parent_cid, &$cid) {
    $webformElements = [];
    foreach ($elements as $element) {
      $element['pid'] = $parent_cid;
      $element['cid'] = $cid;
      $current_cid = $cid;
      $webformElements[$cid] = $element;
      unset($webformElements[$cid]['elements']);
      // Increment cid for the next element.
      $cid++;
      if (isset($element['elements']) && is_array($element['elements']) && !empty($element['elements'])) {
        $nestedElements = self::getFlatElements($element['elements'], $current_cid, $cid);
        $webformElements = array_merge($webformElements, $nestedElements);
      }
    }
    return $webformElements;
  }

  /**
   * Adds an element to the page.
   *
   * This method is responsible for adding an element to the page
   *  based on its parent ID.
   * If the parent ID is 0, the element is added directly to the page.
   *  Otherwise, it is added
   * to the corresponding parent element.
   *
   * @param array $elements
   *   The array of elements representing the page.
   * @param array $elementData
   *   The data of the element to be added.
   *
   * @return void
   *   No value is returned.
   */
  private static function addElementToPage(&$elements, $elementData) {
    if ($elementData['pid'] == 0) {
      $elements[] = $elementData;
    }
    else {
      foreach ($elements as &$pageElement) {
        if ($pageElement['cid'] == $elementData['pid']) {
          if (!isset($pageElement['elements'])) {
            $pageElement['elements'] = [];
          }
          if ($pageElement['type'] == 'multipletext') {
            $pageElement['items'][] = $elementData;
          }
          else {
            $pageElement['elements'][] = $elementData;
          }
          return;
        }
        elseif (isset($pageElement['elements']) && is_array($pageElement['elements'])) {
          self::addElementToPage($pageElement['elements'], $elementData);
        }
      }
    }
  }

  /**
   * Convert SurveyJS element to Webform element.
   *
   * @param int $nid
   *   The node ID.
   * @param array $element
   *   The SurveyJS element to convert.
   * @param bool $required
   *   (optional) Whether the element is required. Default is false.
   *
   * @return array
   *   The converted Webform element.
   */
  private static function convertElementToWebformElement($nid, $element, $required = FALSE) {
    $uuid_service = \Drupal::service('uuid');
    $name = $element['name'] ?? $uuid_service->generate();

    if (isset($element['cellType']) && $element['type'] !== 'matrixdropdown' && $element['type'] !== 'matrixdynamic') {
      $element['type'] = $element['cellType'];
    }

    // Encode the title if it is an array.
    // This means that there are several languages for the title.
    if (is_array($element['title'])) {
      $element['title'] = json_encode($element['title']);
    }

    $element_name = $element["title"];
    if (!$element_name) {
      // If component title is empty, use the form_key value.
      // Unless it's a panel can have empty title.
      $element_name = $element["type"] == "panel" ? "" : $element["name"];
    }

    $webformElement = [
      'nid' => $nid,
      'pid' => 0,
      'form_key' => $name,
      'name' => $element_name,
      'type' => self::mapSurveyJsTypeToWebform($element['type']),
      'value' => $element['value'] ?? '',
      'weight' => $element['weight'] ?? 0,
    ];

    // Handling options.
    if (isset($element['choices'])) {
      $webformElement['extra']['items'] = "";
      $choices = [];
      foreach ($element['choices'] as $key => $choice) {

        // Need to implode the value and text of the choice with a pipe.
        if (isset($choice['value']) && isset($choice['text'])) {
          if (is_array($choice['text'])) {
            $choices[] = $choice['value'] . '|' . json_encode($choice['text']);
          }
          else {
            $choices[] = $choice['value'] . '|' . $choice['text'];
          }
        }
        elseif (isset($choice['value']) && isset($choice['imageLink'])) {
          $choices[] = $choice['value'] . '|' . $choice['imageLink'];
        }
        else {
          // If the value is not set, then use the key.
          $choices[] = $key . '|' . $choice;
        }
        $webformElement['extra']['items'] = implode("\n", $choices);
      }
    }

    if ($element['type'] == "dropdown" || $element['type'] == "tagbox") {
      $webformElement['extra']['aslist'] = TRUE;
    }

    if ($element['type'] == "checkbox" || $element['type'] == "tagbox") {
      $webformElement['extra']['multiple'] = TRUE;
    }

    if ($element['type'] == "matrix" || $element['type'] == "matrixdropdown" || $element['type'] == "matrixdynamic") {
      $questions = [];
      $options = [];
      if (isset($element['rows'])) {
        foreach ($element['rows'] as $key => $row) {
          // Implem value & text of the choice with a pipe if row is an array.
          if (is_array($row) && !empty($row['value']) && !empty($row['text'])) {
            $questions[] = $row['value'] . '|' . $row['text'];
          }
          else {
            $questions[] = $row;
          }
        }
      }

      if (isset($element['columns'])) {
        foreach ($element['columns'] as $key => $column) {
          if (is_array($column)) {
            if (isset($column['value']) && isset($column['text'])) {
              $options[] = $column['value'] . '|' . $column['text'];
            }
            elseif (isset($column['name'])) {
              $options[] = $column['name'];
            }
            $webformElement['extra']['other_option']['columns'][$key] = $column;
          }
          else {
            $options[] = $column;
          }
        }
      }
      $webformElement['extra']['questions'] = implode("\n", $questions);
      $webformElement['extra']['options'] = implode("\n", $options);
    }

    // Handling other specifics like multiple files.
    if (isset($element['allowMultiple'])) {
      $webformElement['extra']['multiple'] = $element['allowMultiple'];
    }

    // If the element is required.
    if ((isset($element['isRequired']) && $element['isRequired']) || $required) {
      $webformElement['required'] = TRUE;
      $required = TRUE;
    }

    // If the element is read-only.
    if (isset($element['readOnly']) && $element['readOnly']) {
      $webformElement['extra']['disabled'] = TRUE;
    }

    if (isset($element['elements'])) {
      $webformElement['elements'] = [];
      foreach ($element['elements'] as $subElement) {
        $subElementData = self::convertElementToWebformElement($nid, $subElement, $required);
        $webformElement['elements'][] = $subElementData;
      }
    }

    if ($element['type'] === 'multipletext') {
      foreach ($element['items'] as $key => $item) {
        $subItem = self::convertElementToWebformElement($nid, $item, $required);
        $webformElement['elements'][] = $subItem;
      }
    }

    // For other custom properties.
    foreach ($element as $key => $value) {
      if (!in_array($key, [
        'name',
        'type',
        'title',
        'choices',
        'allowMultiple',
        'isRequired',
        'readOnly',
        'columns',
        'rows',
        'elements',
        'items',
      ])) {
        $webformElement['extra']['other_option'][$key] = $value;
      }
    }

    return $webformElement;
  }

  /**
   * Creates a survey element based on the given element data.
   *
   * @param array $elementData
   *   The data of the element.
   *
   * @return array
   *   The created survey element.
   */
  private static function convertElementToSurveyElement($elementData) {

    // If $elementData['name'] is a JSON object then decode it.
    // This means that there are several languages for the title.
    if (is_string($elementData['name']) && json_decode($elementData['name'], TRUE)) {
      $elementData['name'] = json_decode($elementData['name'], TRUE);
    }

    $surveyElement = [
      'name' => $elementData['form_key'],
      'type' => self::mapWebformTypeToSurveyJs($elementData['type']),
      'title' => $elementData['name'] ?? '',
    ];

    // Hidden Field D7.
    if ($elementData['type'] === 'hidden') {
      $surveyElement['visible'] = FALSE;
    }

    // Select / Radio / Checkbox / Tagbox D7.
    if ($elementData['type'] === 'select') {
      if (!$elementData['extra']['aslist']) {
        if ($elementData['extra']['multiple']) {
          $surveyElement['type'] = 'checkbox';
        }
        else {
          $surveyElement['type'] = 'radiogroup';
        }
      }
      else {
        if ($elementData['extra']['multiple']) {
          $surveyElement['type'] = 'tagbox';
        }
        else {
          $surveyElement['type'] = 'dropdown';
        }
      }
    }

    // Input Type D7.
    if ($elementData['type'] === 'email' || $elementData['type'] === 'time' || $elementData['type'] === 'date' || $elementData['type'] === 'number') {
      $surveyElement['inputType'] = $elementData['type'];
    }

    // If options are available.
    if (isset($elementData['extra']['items'])) {
      $surveyElement['choices'] = [];
      $elementDataOptions = explode("\n", $elementData['extra']['items']);

      foreach ($elementDataOptions as $value => $label) {
        if (strpos($label, "|") != TRUE) {
          $surveyElement['choices'][] = ['value' => $label, 'text' => $label];
        }
        else {
          $elementExplode = explode("|", $label);
          $value = $elementExplode[0];
          $label = $elementExplode[1];
          if ($elementData['type'] === 'wf_imgpckr') {
            $surveyElement['choices'] = array_merge(
              $surveyElement['choices'],
              [['value' => $value, 'imageLink' => $label]]
            );
          }
          else {
            // Check if $label is a JSON string.
            if (json_decode($label, TRUE)) {
              $surveyElement['choices'] = array_merge(
                $surveyElement['choices'],
                [['value' => $value, 'text' => json_decode($label, TRUE)]]
              );
            }
            else {
              $surveyElement['choices'] = array_merge(
                $surveyElement['choices'],
                [['value' => $value, 'text' => $label]]
              );
            }
          }
        }
      }
    }

    // If the element is required.
    if (isset($elementData['required']) && $elementData['required']) {
      $surveyElement['isRequired'] = TRUE;
    }

    // If the element is read-only.
    if (isset($elementData['extra']['disabled']) && $elementData['extra']['disabled']) {
      $surveyElement['readOnly'] = TRUE;
    }

    // Handling other specifics like multiple files.
    if ($surveyElement['type'] === 'file') {
      // Convert string $elementData['multiple'] to bool.
      $surveyElement['allowMultiple'] = filter_var($elementData['extra']['multiple'], FILTER_VALIDATE_BOOLEAN) ?? FALSE;
      $surveyElement['storeDataAsText'] = FALSE;
    }

    // For other custom properties.
    if (isset($elementData['extra']['other_option'])) {
      $surveyElement = array_merge($surveyElement, $elementData['extra']['other_option']);
    }

    if ($elementData['type'] === 'grid' || $elementData['type'] === 'wf_matrixdrop' || $elementData['type'] == 'wf_matrixdyn') {
      $surveyElement['columns'] = [];
      $surveyElement['rows'] = [];
      $gridQuestions = $elementData['extra']['questions'];
      $gridOptions = $elementData['extra']['options'];

      $gridQuestionsArray = explode("\n", $gridQuestions);
      $gridOptionsArray = explode("\n", $gridOptions);

      foreach ($gridQuestionsArray as $key => $value) {
        // Explode by "|", if there is no "|", just use the value.
        if (strpos($value, "|") != TRUE) {
          $surveyElement['rows'][] = ['value' => $value, 'text' => $value];
        }
        else {
          $elementExplode = explode("|", $value);
          $surveyElement['rows'][] = ['value' => $elementExplode[0], 'text' => $elementExplode[1]];
        }
      }

      foreach ($gridOptionsArray as $key => $value) {
        // Explode by "|", if there is no "|", just use the value.
        if (strpos($value, "|") != TRUE) {
          if ($elementData['type'] === 'wf_matrixdrop' || $elementData['type'] === "wf_matrixdyn") {
            if ($elementData['extra']['other_option']['columns']) {
              $other_options = $elementData['extra']['other_option']['columns'];
              $surveyElement['columns'] = $other_options;
              break;
            }
            else {
              $surveyElement['columns'][] = ['name' => $value];
            }
          }
          else {
            $surveyElement['columns'][] = ['value' => $value, 'text' => $value];
          }
        }
        else {
          $elementExplode = explode("|", $value);
          $surveyElement['columns'][] = ['value' => $elementExplode[0], 'text' => $elementExplode[1]];
        }
      }
    }
    if ($elementData['type'] == "webform_custom_composite") {
      $surveyElement['columns'] = [];
      foreach ($elementData['#element'] as $key => $value) {
        if (is_array($value) && isset($value['type'])) {
          $surveyElement['columns'][] = self::convertElementToSurveyElement($value);
        }
      }
    }

    if ($elementData['type'] == "webform_likert") {
      $surveyElement['columns'] = [];
      $surveyElement['rows'] = [];
      foreach ($elementData['#questions'] as $key => $question) {
        $surveyElement['rows'][] = ['value' => $key, 'text' => $question];
      }
      foreach ($elementData['#answers'] as $key => $answer) {
        $surveyElement['columns'][] = ['value' => $key, 'text' => $answer];
      }
    }

    // If an element is a multipletext.
    if ($elementData['type'] === 'wf_multipletext') {
      $surveyElement['items'] = [];
      foreach ($elementData as $key => $value) {
        if (is_array($value) && isset($value['type'])) {
          $surveyElement['items'][] = self::convertElementToSurveyElement($value);
        }
      }
    }

    // If it's a panel.
    $surveyElement['cid'] = $elementData['cid'];

    // If the element have pid.
    if ($elementData['pid'] != 0) {
      // Store the pid.
      $surveyElement['pid'] = $elementData['pid'];
    }
    else {
      $surveyElement['pid'] = 0;
    }
    return $surveyElement;
  }

  /**
   * Maps a webform type to its corresponding SurveyJS type.
   *
   * @param string $webformType
   *   The webform type to be mapped.
   *
   * @return string
   *   The corresponding SurveyJS type.
   */
  private static function mapWebformTypeToSurveyJs($webformType) {
    $map = [
      'textfield' => 'text',
      'hidden' => 'text',
      'textarea' => 'comment',
      'file' => 'file',
      'grid' => 'matrix',
      'wf_boolean' => 'boolean',
      'wf_rating' => 'rating',
      'wf_matrixdrop' => 'matrixdropdown',
      'wf_matrixdyn' => 'matrixdynamic',
      'wf_ranking' => 'ranking',
      'wf_imgpckr' => 'imagepicker',
      'processed_text' => 'html',
      'wf_file_image' => 'image',
      'wf_signature' => 'signaturepad',
      'wf_panel' => 'panel',
      'wf_paneldynamic' => 'paneldynamic',
      'wf_multipletext' => 'multipletext',
      // Add more mappings as needed.
    ];

    return $map[$webformType] ?? 'text';
  }

  /**
   * Maps a SurveyJS type to a Webform type.
   *
   * @param string $surveyJSType
   *   The SurveyJS type to be mapped.
   *
   * @return string
   *   The corresponding Webform type.
   */
  private static function mapSurveyJsTypeToWebform($surveyJSType) {
    $map = [
      'text' => 'textfield',
      'rating' => 'wf_rating',
      'boolean' => 'wf_boolean',
      'comment' => 'textarea',
      'matrix' => 'grid',
      'radiogroup' => 'select',
      'checkbox' => 'select',
      'tagbox' => 'select',
      'dropdown' => 'select',
      'file' => 'file',
      'multipletext' => 'wf_multipletext',
      'matrixdropdown' => 'wf_matrixdrop',
      'matrixdynamic' => 'wf_matrixdyn',
      'ranking' => 'wf_ranking',
      'imagepicker' => 'wf_imgpckr',
      'html' => 'processed_text',
      'image' => 'wf_file_image',
      'signaturepad' => 'wf_signature',
      'panel' => 'wf_panel',
      'paneldynamic' => 'wf_paneldynamic',
      'multipletext' => 'wf_multipletext',
    ];

    return $map[$surveyJSType] ?? 'textfield';
  }

}
