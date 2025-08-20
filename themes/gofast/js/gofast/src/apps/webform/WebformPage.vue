<script setup>
import { ref, defineAsyncComponent, onMounted } from 'vue';
import axios from 'axios';
import Card from '../../components/global/CardContent.vue';
import Tabs from '../../components/global/NavTabs.vue';
import Spinner from '../../components/global/SpinnerLoader.vue';

// Define the async components for each tab
const ManageWebform = defineAsyncComponent({
  loader: () => import('./partials/ManageWebform.vue'),
  loadingComponent: Spinner,
  delay: 0, // No delay before displaying the loading
  timeout: 3000, // Timeout after 3s
});

const FillWebform = defineAsyncComponent({
  loader: () => import('./partials/FillWebform.vue'),
  loadingComponent: Spinner,
  delay: 0, // No delay before displaying the loading
  timeout: 3000, // Timeout after 3s
});

const DashboardWebform = defineAsyncComponent({
  loader: () => import('./partials/ResultsWebform.vue'),
  loadingComponent: Spinner,
});

const TableWebform = defineAsyncComponent({
  loader: () => import('./partials/TableWebform.vue'),
  loadingComponent: Spinner,
});

// Get the nid from data-nid attr
const nid = document.querySelector('#webform').getAttribute('data-nid');
// Get the link hash from data-hash attr
const hash = document.querySelector('#webform').getAttribute('data-hash');

const submissions = ref([]);

const cardTitle = ref('Webform Title to Replace');

const fillTab = {
  title: Drupal.t('Fill out'),
  icon: 'fas fa-lg fa-file-signature',
  id: 'fill_webform',
  active: true,
  loaded: false,
  disabled: true,
  component: FillWebform,
};
const editTab = {
  title: Drupal.t('Edit'),
  icon: 'fas fa-lg fa-edit',
  id: 'manage_webform',
  active: false,
  loaded: false,
  disabled: true,
  component: ManageWebform,
};
const dashboardTab = {
  title: Drupal.t('Dashboard'),
  icon: 'fas fa-lg fa-chart-line-up',
  id: 'results_webform',
  active: false,
  loaded: false,
  disabled: true,
  component: DashboardWebform,
};
const resultsTab = {
  title: Drupal.t('Results'),
  icon: 'fas fa-lg fa-table',
  id: 'table_webform',
  active: false,
  loaded: false,
  disabled: true,
  component: TableWebform,
};

const tabs = ref([fillTab, editTab, dashboardTab, resultsTab]);

const loadingTabs = ref([]);

// Webform data
const webformData = ref({});
const webformTheme = ref({});
const webformStatus = ref('');
const webformStatusMessage = ref('');

// Add a ref for the active tab
const activeTab = ref('fill_webform');

const handleActionClick = () => {};

const handleTabChange = (tabId) => {
  activeTab.value = tabId;
  // Change active tab
  tabs.value.forEach((tab) => {
    tab.active = tab.id === tabId;
    // Mark the tab as loaded only when it is activated,
    // and only for the dashboard and results tabs.
    if (
      tab.id === tabId &&
      (tab.id === dashboardTab.id || tab.id === resultsTab.id)
    ) {
      tab.loaded = true;
    }
  });
};

async function getWebformStatus() {
  try {
    const response = await axios.get(`/api/webform/status?nid=${nid}`, {
      headers: {
        'Cache-Control': 'no-cache',
      },
    });
    webformStatus.value = response.data.status;
    webformStatusMessage.value = response.data.description;
  } catch (error) {
    // Handle error
  }
}

const loadWebform = async () => {
  try {
    const response = await axios.get(
      `/drupal/api/webform/webform?nid=${nid}&_format=json&hash=${hash}`,
      {
        headers: {
          'Cache-Control': 'no-cache',
        },
      },
    );
    if (response.data.node_access === 'delete') {
      tabs.value.forEach((tab) => {
        tab.disabled = false;
      });
    } else if (response.data.node_access === 'update') {
      fillTab.disabled = false;
      fillTab.loaded = true; // Mark the "Fill out" tab as loaded
      editTab.disabled = false;
      editTab.loaded = true; // Mark the "Edit" tab as loaded
    }
    if (
      response.request.responseURL ===
      `${window.location.origin}/drupal/system/403`
    ) {
      window.location = '/drupal/system/403';
    }
    webformData.value = response.data.surveyElements;
    if (response.data.surveyTheme) {
      webformTheme.value = response.data.surveyTheme;
    }
  } catch (error) {
    // Handle error
  }
};

const handleSubmissionsUpdate = (newSubmissions) => {
  submissions.value = newSubmissions;
};

const switchToEditTabIfClosed = () => {
  if (webformStatus.value === 'closed') {
    const editTabId = 'manage_webform';
    // Update the active tab
    activeTab.value = editTabId;
    handleTabChange(editTabId); // Use the existing function to maintain consistency
  }
};

onMounted(async () => {
  try {
    // Wait for both API calls to complete
    await Promise.all([getWebformStatus(), loadWebform()]);

    // Check the status and change the tab if necessary
    if (webformStatus.value === 'closed') {
      switchToEditTabIfClosed();
    }
  } catch (error) {
    console.error('Error during initial loading:', error);
  }
});
</script>

<template>
  <Card
  :title="cardTitle"
  :action-label="actionLabel"
  no-header
  @action-click="handleActionClick"
  >
    <template #body>
      <div>
        <Tabs
          :tabs="tabs"
          :loading-tabs="loadingTabs"
          :active-tab="activeTab"
          @tab-change="handleTabChange"
        >
          <template v-for="tab in tabs" #[tab.id]>
            <Spinner
              v-if="!webformData || Object.keys(webformData).length === 0"
              :key="`spinner-${tab.id}`"
            />
            <component
              :is="tab.component"
              v-else-if="
                tab.loaded ||
                (tab.id !== dashboardTab.id && tab.id !== resultsTab.id)
              "
              :key="`component-${tab.id}`"
              :nid="nid"
              :webform="webformData"
              :webform-theme="webformTheme"
              :webform-status="webformStatus"
              :webform-status-message="webformStatusMessage"
              :submissions="submissions"
              @update:submissions="handleSubmissionsUpdate"
            />
          </template>
        </Tabs>
      </div>
    </template>
  </Card>
</template>
