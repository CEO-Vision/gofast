<template>
  <div class="h-100">
    <AlertContent
      v-if="props.webformStatus === 'open'"
      :message="props.webformStatusMessage"
    />
    <div id="page-manage-webform">
      <SurveyCreatorComponent
        v-if="props.webformStatus !== 'open'"
        :model="creator"
      />
    </div>
  </div>
</template>

<script setup>
import '../surveyOverride.css';
import 'survey-core/survey.i18n';
import 'survey-creator-core/survey-creator-core.i18n';
import 'survey-creator-core/survey-creator-core.min.css';
import { onMounted } from 'vue';
import {
  SurveyCreatorModel,
  editorLocalization,
  DefaultFonts,
} from 'survey-creator-core';
import { surveyLocalization } from 'survey-core';
import axios from 'axios';
import { defaultTheme } from '../survey_default_theme';
import AlertContent from '../../../components/global/AlertContent.vue';
import { getCurrentUser, getCurrentLanguage } from '../../gofast/utils/utils';

const props = defineProps({
  nid: {
    type: String,
    required: true,
  },
  webform: {
    type: Object,
    required: true,
  },
  webformTheme: {
    type: Object,
    required: false,
    default: defaultTheme,
  },
  webformStatus: {
    type: String,
    required: true,
  },
  webformStatusMessage: {
    type: String,
    required: false,
    default: '',
  },
});

let user = getCurrentUser();
if (user === undefined) {
  user = 0;
}

// Push our fonts int the default fonts array
DefaultFonts.push('Poppins, Helvetica, "sans-serif"');

const creatorOptions = {
  showTestSurveyTab: true,
  showLogicTab: true,
  showTranslationTab: true,
  showJSONEditorTab: true,
  showThemeTab: true,
  isAutoSave: true,
};

// Get language
const lang = getCurrentLanguage();
editorLocalization.defaultLocale = lang;
surveyLocalization.supportedLocales = ['en', 'de', 'fr'];

const creator = new SurveyCreatorModel(creatorOptions);
creator.locale = lang;

// Change the data panel title
creator.onPropertyGridSurveyCreated.add((sender, options) => {
  const dataTab = options.survey.getPanelByName('data');
  if (dataTab) {
    dataTab.title = Drupal.t('Data (Default value and Good Answers)');
  }
});

/**
 * Add custom error message on property change
 */
creator.onPropertyValidationCustomError.add((sender, options) => {
  // Prevent setting -Comment at the end of question name preventing conflict with questions integrated comment field
  if (options.propertyName === 'name' && options.value.endsWith('-Comment')) {
    options.error = Drupal.t(
      'The question name cannot end with "-Comment"',
      {},
      { context: 'gofast:gofast_webform' },
    );
  }
});

creator.onUploadFile.add(async (_, options) => {
  const formData = new FormData();

  options.files.forEach((file) => {
    formData.append(options.question.name, file);
  });

  try {
    const apiResponse = await fetch(
      `/api/webform/file?nid=${props.nid}&editor=true`,
      {
        method: 'POST',
        body: formData,
        mode: 'cors',
      },
    );

    const data = await apiResponse.json();
    options.callback(
      'success',
      // A link to the uploaded file
      `/api/webform/get_image?reference=${data[options.question.name].file_reference}`,
    );
  } catch (error) {
    console.error('Error uploading files:', error);
    options.callback('error');
  }
});

const saveSurveyFunc = async (surveyData) => {
  try {
    await axios.post('/drupal/api/webform/webform?_format=json', {
      nid: props.nid,
      survey_json: surveyData,
    });
  } catch (error) {
    // Handle error
  }
};

creator.saveSurveyFunc = (saveNo, callback) => {
  saveSurveyFunc(creator.JSON)
    .then(() => {
      if (callback) {
        callback(saveNo, true);
      }
    })
    .catch(() => {
      if (callback) {
        callback(saveNo, false);
      }
    });
};

// If you use a web service:
const saveThemeJson = async (url, json) => {
  try {
    await axios.post('/api/webform/theme', {
      nid: props.nid,
      themeJson: JSON.stringify(json),
    });
  } catch (error) {
    // Handle error
  }
};

creator.saveThemeFunc = (saveNo, callback) => {
  // If you use localStorage:
  window.localStorage.setItem('survey-theme-json', creator.theme);
  callback(saveNo, true);

  // If you use a web service:
  saveThemeJson('/api/webform/theme', creator.theme, saveNo, callback);
};

onMounted(() => {
  if (props.nid && props.webformStatus === 'closed') {
    if (props.webformTheme && Object.keys(props.webformTheme).length > 0) {
      creator.theme = props.webformTheme;
    } else {
      creator.theme = defaultTheme;
    }
    window.localStorage.setItem('survey-theme-json', creator.theme);
    creator.JSON = props.webform;
  }
});
</script>
