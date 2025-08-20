<?php

namespace Drupal\gofast_webform\Service;

use Drupal\webform\Entity\Webform;
use Drupal\Core\Entity\EntityTypeManagerInterface;
use Drupal\node\NodeInterface;

/**
 * Service class for handling SurveyJS data.
 */
class SurveyService {

  /**
   * The entity type manager service.
   *
   * @var \Drupal\Core\Entity\EntityTypeManagerInterface
   */
  protected $entityTypeManager;

  /**
   * Constructs a SurveyService object.
   *
   * @param \Drupal\Core\Entity\EntityTypeManagerInterface $entityTypeManager
   *   The entity type manager service.
   */
  public function __construct(EntityTypeManagerInterface $entityTypeManager) {
    $this->entityTypeManager = $entityTypeManager;
  }

  /**
   * Get the Survey values from the webform.
   *
   * @param int $nodeId
   *   The ID of the webform node.
   *
   * @return \Drupal\webform\WebformInterface
   *   The webform entity.
   */
  public function getSurveyValues($nodeId) {
    $node = $this->entityTypeManager->getStorage('node')->load($nodeId);
    if ($node instanceof NodeInterface) {
      $webform = Webform::load($node->get('webform')->target_id);
    }

    if (!$webform) {
      throw new \Exception('Webform not found');
    }

    // Get form custom settings.
    $settings = $webform->getSettings()['form_attributes']['customProperties'];

    // Transform it to SurveyJS format.
    $elements = $webform->getElementsDecoded();
    $survey_elements = self::convertToSurvey($elements);
    return $survey_elements + $settings;
  }

  /**
   * Set the Survey values to the webform.
   *
   * @param int $nodeId
   *   The ID of the webform node.
   * @param string $surveyJson
   *   The SurveyJS JSON string.
   */
  public function setWebformValues($nodeId, $surveyJson) {
    $node = $this->entityTypeManager->getStorage('node')->load($nodeId);
    if ($node instanceof NodeInterface) {
      $webform = Webform::load($node->get('webform')->target_id);
    }

    if (!$webform) {
      throw new \Exception('Webform not found');
    }

    // surveyOptions is an array of surveyJson without $surveyJson['pages'].
    $surveyOptions = $surveyJson;
    unset($surveyOptions['pages']);
    // Transform SurveyJS JSON to Webform elements.
    $webformElements = self::convertToWebform($surveyJson);
    // Set the webform elements.
    $webform->setElements($webformElements);
    $webform->setSettings([
      'form_attributes' => [
        'customProperties' => $surveyOptions,
      ],
    ]);

    $webform->save();
  }

  /**
   * Get the submissions of a webform.
   *
   * @param int $nodeId
   *   The ID of the webform node.
   *
   * @return array|null
   *   An array of webform submissions or NULL if none found.
   */
  public function getWebformSubmissions($nodeId) {
    $node = $this->entityTypeManager->getStorage('node')->load($nodeId);
    if ($node instanceof NodeInterface) {
      $webform = Webform::load($node->get('webform')->target_id);
    }

    if (!$webform) {
      return NULL;
    }

    $goodOrder = array_keys($webform->getElementsInitializedFlattenedAndHasValue());
    $storage = $this->entityTypeManager->getStorage('webform_submission');
    $webform_submission = $storage->loadByProperties([
      'entity_type' => 'node',
      'entity_id' => $nodeId,
    ]);
    $submission_data = [];
    foreach ($webform_submission as $key => $submission) {
      $data = $submission->getData();
      // Reorder data to match the order of the webform elements.
      $submission_data_reorder = [];
      foreach ($goodOrder as $element) {
        if (isset($data[$element])) {
          if ($data[$element] != 'Array' && !is_array($data[$element])) {
            $submission_data_reorder[$element] = $data[$element];
          }
        }
        else {
          $submission_data_reorder[$element] = '';
        }
      }
      // Get submission user / Ip address.
      $submission_data[$key]['user'] = $submission->getOwner()->getDisplayName();
      $submission_data[$key]['ip'] = $submission->get('remote_addr')->value;
      $submission_data[$key]['data'] = $submission_data_reorder;
    }
    return $submission_data;
  }

  /**
   * Convert SurveyJS JSON format to Webform elements array.
   *
   * @param array $surveyArray
   *   The SurveyJS JSON array.
   *
   * @return array
   *   Webform elements array.
   */
  private static function convertToWebform($surveyArray) {
    $webformElements = [];
    if (isset($surveyArray['pages'])) {
      foreach ($surveyArray['pages'] as $page) {

        // Create wizard page.
        if (isset($page['name'])) {
          $page['title'] = $page['title'] ?? $page['name'];
          $webformElements[$page['name']] = [
            '#type' => 'webform_wizard_page',
            '#title' => $page['title'],
          ];
        }
        else {
          $uuid_service = \Drupal::service('uuid');
          $uuid = $uuid_service->generate();
          $page['title'] = $page['title'] ?? $uuid;
          $page['name'] = $uuid;
          $webformElements[$page['name']] = [
            '#type' => 'webform_wizard_page',
            '#title' => $page['title'],
          ];
        }
        if (isset($page['elements'])) {
          foreach ($page['elements'] as $element) {
            $webformElement = self::convertElementToWebformElement($element);
            $webformElements[$page['name']] += $webformElement;
          }
        }
      }
    }
    return $webformElements;
  }

  /**
   * Convert Webform elements to SurveyJS JSON format.
   *
   * @param array $elements
   *   Webform elements.
   *
   * @return array
   *   JSON formatted for SurveyJS.
   */
  private static function convertToSurvey($elements) {
    $surveyJson = [
      'pages' => [],
    ];
    foreach ($elements as $element) {
      // Check if the element is a wizard page.
      if ($element['#type'] === 'webform_wizard_page') {
        $page = [
          'name' => $element['#title'],
          'elements' => [],
        ];

        // Iterate through elements within the wizard page.
        foreach ($element as $subElement) {
          if (is_array($subElement) && isset($subElement['#type'])) {
            $elementData = self::createSurveyElement($subElement);
            $page['elements'][] = $elementData;
          }
        }

        $surveyJson['pages'][] = $page;
      }
      else {
        // Regular element outside of any wizard page.
        $elementData = self::createSurveyElement($element);
        // Assuming these elements belong to a default page.
        if (empty($surveyJson['pages'])) {
          $surveyJson['pages'][] = ['name' => 'Default Page', 'elements' => []];
        }

        // Add $elementData to the default page.
        $surveyJson['pages'][0]['elements'][] = $elementData;
      }
    }

    return $surveyJson;
  }

  /**
   * Convert SurveyJS element to Webform element.
   */
  private static function convertElementToWebformElement($element, $required = FALSE) {
    $uuid_service = \Drupal::service('uuid');
    $name = $element['name'] ?? $uuid_service->generate();

    if (isset($element['cellType'])) {
      $element['type'] = $element['cellType'];
    }
    $webformElement[$name] = [
      '#type' => self::mapSurveyJsTypeToWebform($element['type']),
      '#title' => $element['title'] ?? '',
      '#name' => $element['name'] ?? '',
    ];

    // Handling options.
    if (isset($element['choices'])) {
      $webformElement[$name]['#options'] = [];
      foreach ($element['choices'] as $key => $choice) {
        if (isset($choice['value']) && isset($choice['text'])) {
          $webformElement[$name]['#options'][$choice['value']] = $choice['text'];
        }
        else {
          $webformElement[$name]['#options'][$choice] = $choice;
        }
      }
    }

    // Handling other specifics like multiple files.
    if (isset($element['allowMultiple'])) {
      $webformElement[$name]['#multiple'] = $element['allowMultiple'];
    }

    // If the element is required.
    if ((isset($element['isRequired']) && $element['isRequired']) || $required) {
      $webformElement[$name]['#required'] = TRUE;
      $required = TRUE;
    }

    // If the element is read-only.
    if (isset($element['readOnly']) && $element['readOnly']) {
      $webformElement[$name]['#readonly'] = TRUE;
    }

    // If the element is hidden.
    if (isset($element['visible']) && !$element['visible']) {
      $webformElement[$name]['#access'] = FALSE;
    }

    if (isset($element['elements']) && is_array($element['elements']) && $element['type'] !== 'matrixdropdown' && $element['type'] !== 'matrixdynamic') {
      foreach ($element['elements'] as $subElement) {
        $subElementData = self::convertElementToWebformElement($subElement, $required);
        $webformElement[$name] = array_merge($webformElement[$name], $subElementData);
      }
    }

    if ($element['type'] === 'tagbox') {
      $webformElement[$name]['#customProperties']['tagbox'] = TRUE;
    }

    // Handling for matrix.
    if ($element['type'] === 'matrix') {
      $webformElement[$name]['#questions'] = [];
      $webformElement[$name]['#answers'] = [];

      // Get value from columns and rows.
      foreach ($element['rows'] as $key => $column) {
        $value = $column['value'] ?? $name . '_' . $key;
        $text = $column['text'] ?? $column;
        $webformElement[$name]['#questions'][$value] = $text;
      }

      foreach ($element['columns'] as $key => $column) {
        $value = $column['value'] ?? $name . '_' . $key;
        $text = $column['text'] ?? $column;
        $webformElement[$name]['#answers'][$value] = $text;
      }
    }
    // Handling for matrixdropdown.
    if ($element['type'] === 'matrixdropdown') {
      $columnData = [];
      foreach ($element['columns'] as $column) {
        if (!isset($column['cellType'])) {
          $column['cellType'] = 'dropdown';
        }
        $columnElement = self::convertElementToWebformElement($column, $required);
        $columnData = array_merge($columnData, $columnElement);
      }
      foreach ($element['rows'] as $key => $row) {

        // Create a unique machine name for the row.
        $rowMachineName = is_array($row) ? ($row['value'] ?: $key) : $name . '_' . $key;
        $rowData[$rowMachineName] = [
          '#type' => 'webform_custom_composite',
          '#title' => is_array($row) ? ($row['text'] ?: $row['value']) : $row,
          '#element' => $columnData,
          '#required' => $required,
        ];
      }

      $webformElement[$name] = array_merge($webformElement[$name], $rowData);
    }

    if ($element['type'] === 'matrixdynamic') {
      $webformElement[$name]['#element'] = [];
      foreach ($element['columns'] as $column) {
        $columnElement = self::convertElementToWebformElement($column, $required);
        $webformElement[$name]['#element'] = array_merge($webformElement[$name]['#element'], $columnElement);
      }
    }

    if ($element['type'] === 'multipletext') {
      $webformElement[$name]['#type'] = 'webform_multipletext';

      foreach ($element['items'] as $key => $item) {
        $webformElement[$name] = array_merge($webformElement[$name], self::convertElementToWebformElement($item, $required));
      }
    }

    // For other custom properties.
    foreach ($element as $key => $value) {
      if (!in_array(
        $key,
        [
          'name',
          'type',
          'title',
          'choices',
          'allowMultiple',
          'isRequired',
          'readOnly',
          'visible',
          'columns',
          'rows',
          'elements',
          'items',
        ]
      )) {
        $webformElement[$name]['#customProperties'][$key] = $value;
      }
    }

    return $webformElement;
  }

  /**
   * Create a SurveyJS element array from a Webform element.
   *
   * @param array $elementData
   *   The webform element array.
   *
   * @return array
   *   The SurveyJS element array.
   */
  private static function createSurveyElement($elementData) {

    $surveyElement = [
      'name' => $elementData['#name'],
      'type' => self::mapWebformTypeToSurveyJs($elementData['#type']),
      'title' => $elementData['#title'] ?? '',
    ];

    // If options are available.
    if (isset($elementData['#options'])) {
      $surveyElement['choices'] = [];
      foreach ($elementData['#options'] as $value => $label) {
        if ($value !== $label) {
          $surveyElement['choices'] = array_merge($surveyElement['choices'], [['value' => $value, 'text' => $label]]);
        }
        else {
          $surveyElement['choices'] = array_merge($surveyElement['choices'], [$label]);
        }
      }
    }

    // If the element is required.
    if (isset($elementData['#required']) && $elementData['#required']) {
      $surveyElement['isRequired'] = TRUE;
    }

    // If the element is read-only.
    if (isset($elementData['#readonly']) && $elementData['#readonly']) {
      $surveyElement['readOnly'] = TRUE;
    }

    // If the element is hidden.
    if (isset($elementData['#access']) && !$elementData['#access']) {
      $surveyElement['visible'] = FALSE;
    }

    // Handling other specifics like multiple files.
    if ($surveyElement['type'] === 'file') {
      $surveyElement['allowMultiple'] = $elementData['#multiple'] ?? FALSE;
    }

    // For other custom properties.
    if (isset($elementData['#customProperties'])) {
      $surveyElement = array_merge($surveyElement, $elementData['#customProperties']);
    }
    if ($elementData['#type'] === 'webform_matrixdropdown') {
      $surveyElement['columns'] = [];
      $surveyElement['rows'] = [];
      $columnAlreadySet = FALSE;
      foreach ($elementData as $key => $value) {
        if (is_array($value) && isset($value['#element']) && is_array($value['#element'])) {
          // Take the first element as the column.
          if ($columnAlreadySet === FALSE) {
            foreach ($value['#element'] as $column) {
              $columnData = self::createSurveyElement($column);
              // If cellType is defined, remove type.
              if (isset($columnData['type'])) {
                unset($columnData['type']);
              }
              $surveyElement['columns'][] = $columnData;
              $columnAlreadySet = TRUE;
            }
          }
          // Bulk add rows.
          if (isset($value['#title'])) {
            $surveyElement['rows'][] = ['value' => $key, 'text' => $value['#title']];
          }
          else {
            $surveyElement['rows'][] = $key;
          }
        }
      }
    }

    if ($elementData['#type'] == "webform_custom_composite") {
      $surveyElement['columns'] = [];
      foreach ($elementData['#element'] as $key => $value) {
        if (is_array($value) && isset($value['#type'])) {
          $surveyElement['columns'][] = self::createSurveyElement($value);
        }
      }
    }

    if ($elementData['#type'] == "webform_likert") {
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
    if ($elementData['#type'] === 'webform_multipletext') {
      $surveyElement['items'] = [];
      foreach ($elementData as $key => $value) {
        if (is_array($value) && isset($value['#type'])) {
          $surveyElement['items'][] = self::createSurveyElement($value);
        }
      }
    }

    if ($elementData['#type'] == 'checkboxes' && isset($elementData['#customProperties']['tagbox']) && $elementData['#customProperties']['tagbox'] === TRUE) {
      $surveyElement['type'] = 'tagbox';
    }

    // If it's a panel.
    if ($elementData['#type'] === 'webform_panel') {
      $surveyElement['elements'] = [];
      foreach ($elementData as $key => $value) {
        if (is_array($value) && isset($value['#type'])) {
          $surveyElement['elements'][] = self::createSurveyElement($value);
        }
      }
    }

    return $surveyElement;
  }

  /**
   * Map Webform element type to SurveyJS element type.
   *
   * @param string $webformType
   *   The Webform element type.
   *
   * @return string
   *   The corresponding SurveyJS element type.
   */
  private static function mapWebformTypeToSurveyJs($webformType) {
    $map = [
      'textfield' => 'text',
      'textarea' => 'comment',
      'radios' => 'radiogroup',
      'checkboxes' => 'checkbox',
      'select' => 'dropdown',
      'webform_rating' => 'rating',
      'file' => 'file',
      'webform_likert' => 'matrix',
      'webform_matrixdropdown' => 'matrixdropdown',
      'webform_custom_composite' => 'matrixdynamic',
      'webform_table_sort' => 'ranking',
      'webform_image_select' => 'imagepicker',
      'processed_text' => 'html',
      'webform_file_image' => 'image',
      'webform_signature' => 'signaturepad',
      'webform_panel' => 'panel',
      'webform_multipletext' => 'multipletext',
      // Add more mappings as needed.
    ];

    return $map[$webformType] ?? 'text';
  }

  /**
   * Map SurveyJS element type to Webform element type.
   *
   * @param string $surveyJSType
   *   The SurveyJS element type.
   *
   * @return string
   *   The corresponding Webform element type.
   */
  private static function mapSurveyJsTypeToWebform($surveyJSType) {
    $map = [
      'text' => 'textfield',
      'comment' => 'textarea',
      'radiogroup' => 'radios',
      'rating' => 'webform_rating',
      'checkbox' => 'checkboxes',
      'tagbox' => 'checkboxes',
      'dropdown' => 'select',
      'file' => 'file',
      'matrixdropdown' => 'webform_matrixdropdown',
      'matrixdynamic' => 'webform_custom_composite',
      'matrix' => 'webform_likert',
      'ranking' => 'webform_table_sort',
      'imagepicker' => 'webform_image_select',
      'html' => 'processed_text',
      'image' => 'webform_file_image',
      'signaturepad' => 'webform_signature',
      'panel' => 'webform_panel',
      'multipletext' => 'webform_multipletext',
      // Add more mappings as needed.
    ];

    return $map[$surveyJSType] ?? 'textfield';
  }

}
