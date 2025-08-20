import { setLicenseKey } from 'survey-core';
import { editorLocalization } from 'survey-creator-core';
import 'survey-creator-core/i18n/french';
import { surveyCreatorPlugin } from 'survey-creator-vue';
import { surveyPlugin } from 'survey-vue3-ui';
import { createApp } from 'vue';
import Webform from './WebformPage.vue';
import { getCurrentLanguage } from '../gofast/utils/utils';

window.$ = require('jquery');

window.jQuery = window.$;

const lang = getCurrentLanguage();
editorLocalization.currentLocale = lang;

setLicenseKey(process.env.SURVEY_LICENSE_KEY);

export default function mountWebform() {
  const app = createApp(Webform);
  app.use(surveyPlugin).use(surveyCreatorPlugin).mount('#webform');
}

mountWebform();
