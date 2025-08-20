<template>
  <SpinnerLoader v-if="isLoading" />
  <div :class="{ 'd-none': isLoading }">
    <AlertContent
      v-if="data != undefined && !data.length"
      :message="
        Drupal.t(
          'There are no results on this webform',
          {},
          { context: 'gofast:gofast_webform' },
        )
      "
    />
    <div v-else>
      <button class="btn btn-secondary btn-sm m-3" @click="refreshTable">
        <i class="fa-solid fa-arrows-rotate" />
        <span class="text-black-50">{{ Drupal.t('Refresh') }}</span>
      </button>
      <div class="w-100">
        <div id="surveyDataTable" />
      </div>
    </div>
  </div>
</template>

<script setup>
// Import dependencies
import { ref, onMounted, watch } from 'vue';
import axios from 'axios';
import jszip from 'jszip';

import 'tabulator-tables/dist/css/tabulator.min.css';
import 'survey-analytics/survey.analytics.tabulator.min.css';

import { Model } from 'survey-core';
import { Tabulator, localization } from 'survey-analytics/survey.analytics.tabulator';
import jsPDF from 'jspdf';
import 'jspdf-autotable';
import XLSX from 'xlsx';
import AlertContent from '../../../components/global/AlertContent.vue';
import SpinnerLoader from '../../../components/global/SpinnerLoader.vue';

// Import language settings
import { getCurrentLanguage, Drupal } from '../../gofast/utils/utils';

window.jsPDF = jsPDF;
window.XLSX = XLSX;
// pdfmake.vfs = pdfFonts.pdfMake.vfs;
window.JSZip = jszip;

const surveyJson = ref({});

const props = defineProps({
  nid: {
    type: String,
    required: true,
  },
  webform: {
    type: Object,
    required: true,
  },
});

const data = ref();
const isLoading = ref(true);
const emit = defineEmits(['update:submissions']);

let surveyDataTableInstance = null;

function getTableSubmissions() {
  isLoading.value = true;
  surveyJson.value = props.webform;
  const survey = new Model(surveyJson.value);
  // Add news questions
  survey.pages[0].addNewQuestion('text', 'uid', 0).title = Drupal.t(
    'User ID',
    {},
    { context: 'gofast:gofast_webform' },
  );
  survey.pages[0].addNewQuestion('text', 'name', 1).title = Drupal.t(
    'User name',
    {},
    { context: 'gofast:gofast_webform' },
  );
  survey.pages[0].addNewQuestion('text', 'remote_addr', 2).title = Drupal.t(
    'IP',
    {},
    { context: 'gofast:gofast_webform' },
  );
  survey.pages[0].addNewQuestion('file', 'submissionPdf', 3).title = Drupal.t(
    'Submission PDF',
    {},
    { context: 'gofast:gofast_webform' },
  );
  survey.pages[0].addNewQuestion('text', 'completed', 4).title = Drupal.t(
    'Submission date',
    {},
    { context: 'gofast:gofast_webform' },
  );
  if (data.value[0].percentage !== undefined) {
    survey.pages[0].addNewQuestion('text', 'percentage', 5).title = Drupal.t(
      'Percentage',
      {},
      { context: 'gofast:gofast_webform' },
    );
  }
  if (data.value[0].score !== undefined) {
    survey.pages[0].addNewQuestion('text', 'score', 6).title = Drupal.t(
      'Score',
      {},
      { context: 'gofast:gofast_webform' },
    );
  }
  if (data.value[0].timeSpent !== undefined) {
    survey.pages[0].addNewQuestion('text', 'timeSpent', 7).title = Drupal.t(
      'Time Spent',
      {},
      { context: 'gofast:gofast_webform' },
    );
  }
  const surveyDataTableElement = document.getElementById('surveyDataTable');
  Object.values(localization.locales).forEach((locale) => {
    locale.xlsxDownloadCaption = 'EXCEL';
  });
  surveyDataTableInstance = new Tabulator(survey, data.value);
  surveyDataTableInstance.locale = getCurrentLanguage();
  surveyDataTableInstance.render(surveyDataTableElement);
}

/**
 * Get webform submissions with a axios request
 */
async function getWebformSubmissions() {
  isLoading.value = true;
  try {
    const response = await axios.get(
      `/api/webform/webform_submissions?nid=${props.nid}`,
    );
    data.value = response.data;
    emit('update:submissions', data.value);
    getTableSubmissions();
  } catch (error) {
    // Handle error
  } finally {
    isLoading.value = false;
  }
}

const refreshTable = () => {
  getWebformSubmissions();
};

watch(data, (newData) => {
  emit('update:submissions', newData);
});

onMounted(() => {
  getWebformSubmissions();
});
</script>
