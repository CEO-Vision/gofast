<template>
  <div class="h-100">
    <!-- Navigation Tabs -->
    <div ref="navTabs" class="w-100 px-2">
      <div class="d-grid">
        <ul
          class="nav nav-tabs nav-fill w-100 mb-0 justify-content-end flex-nowrap"
        >
          <!-- Loop through tabs array to render each tab -->
          <li
            v-for="tab in tabs"
            :key="tab.id"
            class="nav-item"
            role="tab"
            :aria-selected="activeTab === tab.id"
            :aria-controls="tab.id"
          >
            <a
              :class="[
                'nav-link px-2 d-flex justify-content-center',
                { active: activeTab === tab.id },
                { 'd-none': tab.disabled },
              ]"
              href="#"
              @click.prevent="activateTab(tab.id)"
            >
              <span class="nav-icon w-20px me-1">
                <span :class="tab.icon" aria-hidden="true" />
              </span>
              <span class="nav-text">
                {{ tab.title }}
              </span>
              <!-- Display tab title -->
            </a>
          </li>
        </ul>
      </div>
    </div>

    <!-- Tab Content Area -->
    <div
      id="myTabContent"
      ref="tabContent"
      class="tab-content overflow-auto pt-4"
      style="height: calc(100% - 50px)"
    >
      <!-- Loop through tabs array to render each tab's content -->
      <div
        v-for="tab in tabs"
        :id="tab.id"
        :key="tab.id"
        :class="[
          'tab-pane fade h-100',
          { 'show active': activeTab === tab.id },
        ]"
      >
        <div class="h-100">
          <slot :name="tab.id" />
          <!-- Render the slot content associated with each tab -->
        </div>
      </div>
    </div>
  </div>
</template>

<script setup>
import { watch, toRefs } from 'vue';

const props = defineProps({
  tabs: {
    type: Array,
    required: true,
  },
  loadingTabs: {
    type: Array,
    required: true,
  },
  activeTab: {
    type: String,
    required: true,
  },
});

const { tabs, activeTab } = toRefs(props);

const emit = defineEmits(['tab-change']);

// Modifier le watch pour utiliser la prop activeTab correctement
watch(
  tabs,
  (newTabs) => {
    // Si l'onglet actif n'existe pas dans les nouveaux onglets, sélectionner le premier
    if (!newTabs.find((tab) => tab.id === props.activeTab)) {
      emit('tab-change', newTabs[0]?.id || null);
    }
  },
  { deep: true },
);

watch(
  () => props.activeTab,
  (newActiveTab) => {
    tabs.value.forEach((tab) => {
      tab.active = tab.id === newActiveTab;
    });
  },
);

function activateTab(tabId) {
  emit('tab-change', tabId);
}
</script>
