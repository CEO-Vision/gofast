<template>
  <div :id="'accordionExample' + accordionId" class="accordion">
    <div class="accordion-item">
      <h2 :id="'heading-' + accordionId" class="accordion-header">
        <button
          class="accordion-button"
          type="button"
          :data-bs-toggle="'collapse'"
          :data-bs-target="'#collapse-' + accordionId"
          :aria-expanded="true"
          :aria-controls="'collapse-' + accordionId"
        >
          {{ title }}
        </button>
      </h2>
      <div
        :id="'collapse-' + accordionId"
        class="accordion-collapse collapse show"
        :aria-labelledby="'heading-' + accordionId"
        :data-bs-parent="accordionId"
      >
        <div class="accordion-body">
          <!-- Slot for custom content -->
          <slot name="body">
            {{ content }}
          </slot>
        </div>
      </div>
    </div>
  </div>
</template>

<script setup>
// Define the component props using `defineProps`
const props = defineProps({
  title: {
    type: String,
    default: 'Accordion Item #1',
  },
  content: {
    type: String,
    default: "This is the first item's accordion body.",
  },
  accordionId: {
    type: Number,
    required: true,
  },
});

// Destructure the props for easier usage in the template
const { title, content, accordionId } = props;
</script>
