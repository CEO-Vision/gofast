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
    <div v-else class="w-100 p-3">
      <div id="surveyVizPanel" />
    </div>
  </div>
</template>

<script setup>
// Import dependencies
import { ref, onMounted } from 'vue';
import axios from 'axios';

import 'survey-analytics/survey.analytics.min.css';
import { Model } from 'survey-core';
import { VisualizationPanel } from 'survey-analytics';
import AlertContent from '../../../components/global/AlertContent.vue';
import SpinnerLoader from '../../../components/global/SpinnerLoader.vue';

// Import language settings
import 'survey-core/i18n/french';
import { getCurrentLanguage, Drupal } from '../../gofast/utils/utils';

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

const surveyJson = ref({});
const data = ref();
const isLoading = ref(true);

const vizPanelOptions = {
  allowHideQuestions: false,
};

const savedState = window.localStorage.getItem('surveyJsDashboardState');

function getDashboardSubmissions() {
  isLoading.value = true;
  surveyJson.value = props.webform;

  const survey = new Model(surveyJson.value);
  const vizPanel = new VisualizationPanel(
    survey.getAllQuestions(),
    data.value,
    vizPanelOptions,
  );
  if (savedState) {
    vizPanel.state = JSON.parse(savedState);
  }

  vizPanel.onStateChanged.add((_, state) => {
    window.localStorage.setItem(
      'surveyJsDashboardState',
      JSON.stringify(state),
    );
  });

  vizPanel.locale = getCurrentLanguage();
  vizPanel.render('surveyVizPanel');
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
    getDashboardSubmissions();
    // }
  } catch (error) {
    // Handle error
  } finally {
    isLoading.value = false;
  }
}

onMounted(() => {
  getWebformSubmissions(props.nid);
});
</script>
