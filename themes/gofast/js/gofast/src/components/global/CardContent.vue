<template>
  <div class="card card-flush shadow-sm h-100 overflow-hidden">
    <!-- Card Header -->
    <div
      v-if="!noHeader"
      class="card-header d-flex justify-content-between align-items-center"
    >
      <h3 class="card-title">
        {{ title }}
      </h3>
      <div class="card-toolbar">
        <button
          v-if="actionLabel"
          type="button"
          class="btn btn-sm btn-light"
          @click="handleAction"
        >
          {{ actionLabel }}
        </button>
      </div>
    </div>

    <!-- Card Body -->
    <div class="card-body h-100 pb-2 px-1 overflow-hidden">
      <slot name="body">
        {{ body }}
      </slot>
    </div>

    <!-- Card Footer -->
    <div v-if="footer" class="card-footer">
      <slot name="footer">
        {{ footer }}
      </slot>
    </div>
  </div>
</template>

<script setup>
import { defineProps, defineEmits } from 'vue';

// Define the props using defineProps
defineProps({
  title: {
    type: String,
    required: true,
  },
  body: {
    type: String,
    default: '',
  },
  footer: {
    type: String,
    default: '',
  },
  actionLabel: {
    type: String,
    default: '',
  },
  noHeader: {
    type: Boolean,
    default: false,
  },
});

// Define emitted events using defineEmits
const emit = defineEmits(['action-click']);

// Method to handle button click action
const handleAction = () => {
  emit('action-click');
};
</script>
