<template>
  <!--begin::Alert-->
  <div
    class="alert alert-dismissible bg-light-warning d-flex flex-center flex-column py-10 px-10 px-lg-20 mb-10"
  >
    <!--begin::Icon-->
    <span class="fa-thin fa-lock-keyhole fs-4x text-warning mb-5" />
    <!--end::Icon-->

    <!--begin::Wrapper-->
    <div class="text-center">
      <!--begin::Title-->
      <h1 class="fw-bold mb-5">
        {{ title }}
      </h1>
      <!--end::Title-->

      <!--begin::Separator-->
      <div class="separator separator-dashed border-warning opacity-25 mb-5" />
      <!--end::Separator-->

      <!--begin::Content-->
      <div class="mb-9 text-gray-900">
        {{ message }}
      </div>
      <!--end::Content-->
    </div>
    <!--end::Wrapper-->
  </div>
  <!--end::Alert-->
</template>

<script setup>
defineProps({
  title: {
    type: String,
    required: true,
    default: '',
  },
  message: {
    type: String,
    required: true,
  },
});
</script>

<style>
.alert.alert-custom {
  display: flex;
  align-items: stretch;
  padding: 1.5rem 2rem;
}
.alert.alert-custom .alert-icon {
  display: flex;
  align-items: center;
  padding: 0 1.25rem 0 0;
}
.alert.alert-custom .alert-icon i {
  font-size: 2.4rem;
}
.alert.alert-custom .alert-icon.alert-icon-top {
  align-items: flex-start;
  align-content: stretch;
}
.alert.alert-custom .alert-text {
  align-self: center;
  flex-grow: 1;
}
.alert.alert-custom .alert-close {
  padding: 0 0 0 1rem;
  display: flex;
  align-items: center;
  justify-content: flex-end;
  line-height: 0;
}
.alert.alert-custom .alert-close .close {
  text-shadow: none !important;
  cursor: pointer;
  line-height: 0;
}
.alert.alert-custom .alert-close i {
  transition:
    color 0.15s ease,
    background-color 0.15s ease,
    border-color 0.15s ease,
    box-shadow 0.15s ease;
  font-size: 1rem;
}
.alert.alert-custom .alert-close i.ki {
  font-size: 0.75rem;
}
.alert.alert-custom .alert-close:focus i,
.alert.alert-custom .alert-close:hover i {
  transition:
    color 0.15s ease,
    background-color 0.15s ease,
    border-color 0.15s ease,
    box-shadow 0.15s ease;
}
.alert.alert-custom.alert-outline-2x {
  border-width: 2px;
}
.alert.alert-custom.alert-white {
  background-color: #ffffff;
  border-color: #ffffff;
}
.alert.alert-custom.alert-white .alert-icon i {
  color: #3f4254;
}
.alert.alert-custom.alert-white .alert-text {
  color: #3f4254;
}
.alert.alert-custom.alert-white .alert-close i {
  color: #3f4254;
}
.alert.alert-custom.alert-default {
  background-color: #f3f6f9;
  border-color: #f3f6f9;
}
.alert.alert-custom.alert-shadow {
  box-shadow: 0px 0px 30px 0px rgba(82, 63, 105, 0.05);
}
.alert.alert-custom.alert-primary {
  background-color: #3699ff;
  border-color: #3699ff;
}
.alert.alert-custom.alert-primary .alert-icon i {
  opacity: 0.8;
  color: #ffffff;
}
.alert.alert-custom.alert-primary .alert-text {
  color: #ffffff;
}
.alert.alert-custom.alert-primary .alert-close i {
  color: #ffffff;
}
.alert.alert-custom.alert-primary .alert-close:focus,
.alert.alert-custom.alert-primary .alert-close:hover {
  opacity: 1;
  color: #ffffff;
}
.alert.alert-custom.alert-light-primary {
  background-color: #e1f0ff;
  border-color: transparent;
}
.alert.alert-custom.alert-light-primary .alert-icon i {
  color: #3699ff;
}
.alert.alert-custom.alert-light-primary .alert-text {
  color: #3699ff;
}
.alert.alert-custom.alert-light-primary .alert-close i {
  color: #3699ff;
}
.alert.alert-custom.alert-light-primary .alert-close:focus,
.alert.alert-custom.alert-light-primary .alert-close:hover {
  color: #187de4;
}
.alert.alert-custom.alert-light-primary.alert-notice {
  border: 0;
  border-left: 4px solid #3699ff;
  border-top-left-radius: 0;
  border-bottom-left-radius: 0;
}
.alert.alert-custom.alert-outline-primary {
  background-color: transparent;
  border-color: #3699ff;
}
.alert.alert-custom.alert-outline-primary .alert-icon i {
  color: #3699ff;
}
.alert.alert-custom.alert-outline-primary .alert-text {
  color: #3699ff;
}
.alert.alert-custom.alert-outline-primary .alert-close i {
  opacity: 0.8;
  color: #3699ff;
}
.alert.alert-custom.alert-outline-primary .alert-close:focus i,
.alert.alert-custom.alert-outline-primary .alert-close:hover i {
  opacity: 1;
}
.alert.alert-custom.alert-secondary {
  background-color: #e4e6ef;
  border-color: #e4e6ef;
}
.alert.alert-custom.alert-secondary .alert-icon i {
  opacity: 0.8;
  color: #3f4254;
}
.alert.alert-custom.alert-secondary .alert-text {
  color: #3f4254;
}
.alert.alert-custom.alert-secondary .alert-close i {
  color: #3f4254;
}
.alert.alert-custom.alert-secondary .alert-close:focus,
.alert.alert-custom.alert-secondary .alert-close:hover {
  opacity: 1;
  color: #3f4254;
}
.alert.alert-custom.alert-light-secondary {
  background-color: #ebedf3;
  border-color: transparent;
}
.alert.alert-custom.alert-light-secondary .alert-icon i {
  color: #e4e6ef;
}
.alert.alert-custom.alert-light-secondary .alert-text {
  color: #e4e6ef;
}
.alert.alert-custom.alert-light-secondary .alert-close i {
  color: #e4e6ef;
}
.alert.alert-custom.alert-light-secondary .alert-close:focus,
.alert.alert-custom.alert-light-secondary .alert-close:hover {
  color: #d7dae7;
}
.alert.alert-custom.alert-light-secondary.alert-notice {
  border: 0;
  border-left: 4px solid #e4e6ef;
  border-top-left-radius: 0;
  border-bottom-left-radius: 0;
}
.alert.alert-custom.alert-outline-secondary {
  background-color: transparent;
  border-color: #e4e6ef;
}
.alert.alert-custom.alert-outline-secondary .alert-icon i {
  color: #3f4254;
}
.alert.alert-custom.alert-outline-secondary .alert-text {
  color: #3f4254;
}
.alert.alert-custom.alert-outline-secondary .alert-close i {
  opacity: 0.8;
  color: #3f4254;
}
.alert.alert-custom.alert-outline-secondary .alert-close:focus i,
.alert.alert-custom.alert-outline-secondary .alert-close:hover i {
  opacity: 1;
}
.alert.alert-custom.alert-success {
  background-color: #1bc5bd;
  border-color: #1bc5bd;
}
.alert.alert-custom.alert-success .alert-icon i {
  opacity: 0.8;
  color: #ffffff;
}
.alert.alert-custom.alert-success .alert-text {
  color: #ffffff;
}
.alert.alert-custom.alert-success .alert-close i {
  color: #ffffff;
}
.alert.alert-custom.alert-success .alert-close:focus,
.alert.alert-custom.alert-success .alert-close:hover {
  opacity: 1;
  color: #ffffff;
}
.alert.alert-custom.alert-light-success {
  background-color: #c9f7f5;
  border-color: transparent;
}
.alert.alert-custom.alert-light-success .alert-icon i {
  color: #1bc5bd;
}
.alert.alert-custom.alert-light-success .alert-text {
  color: #1bc5bd;
}
.alert.alert-custom.alert-light-success .alert-close i {
  color: #1bc5bd;
}
.alert.alert-custom.alert-light-success .alert-close:focus,
.alert.alert-custom.alert-light-success .alert-close:hover {
  color: #0bb7af;
}
.alert.alert-custom.alert-light-success.alert-notice {
  border: 0;
  border-left: 4px solid #1bc5bd;
  border-top-left-radius: 0;
  border-bottom-left-radius: 0;
}
.alert.alert-custom.alert-outline-success {
  background-color: transparent;
  border-color: #1bc5bd;
}
.alert.alert-custom.alert-outline-success .alert-icon i {
  color: #1bc5bd;
}
.alert.alert-custom.alert-outline-success .alert-text {
  color: #1bc5bd;
}
.alert.alert-custom.alert-outline-success .alert-close i {
  opacity: 0.8;
  color: #1bc5bd;
}
.alert.alert-custom.alert-outline-success .alert-close:focus i,
.alert.alert-custom.alert-outline-success .alert-close:hover i {
  opacity: 1;
}
.alert.alert-custom.alert-info {
  background-color: #3699ff;
  border-color: #3699ff;
}
.alert.alert-custom.alert-info .alert-icon i {
  opacity: 0.8;
  color: #ffffff;
}
.alert.alert-custom.alert-info .alert-text {
  color: #ffffff;
}
.alert.alert-custom.alert-info .alert-close i {
  color: #ffffff;
}
.alert.alert-custom.alert-info .alert-close:focus,
.alert.alert-custom.alert-info .alert-close:hover {
  opacity: 1;
  color: #ffffff;
}
.alert.alert-custom.alert-light-info {
  background-color: #e1f0ff;
  border-color: transparent;
}
.alert.alert-custom.alert-light-info .alert-icon i {
  color: #3699ff;
}
.alert.alert-custom.alert-light-info .alert-text {
  color: #3699ff;
}
.alert.alert-custom.alert-light-info .alert-close i {
  color: #3699ff;
}
.alert.alert-custom.alert-light-info .alert-close:focus,
.alert.alert-custom.alert-light-info .alert-close:hover {
  color: #187de4;
}
.alert.alert-custom.alert-light-info.alert-notice {
  border: 0;
  border-left: 4px solid #3699ff;
  border-top-left-radius: 0;
  border-bottom-left-radius: 0;
}
.alert.alert-custom.alert-outline-info {
  background-color: transparent;
  border-color: #3699ff;
}
.alert.alert-custom.alert-outline-info .alert-icon i {
  color: #3699ff;
}
.alert.alert-custom.alert-outline-info .alert-text {
  color: #3699ff;
}
.alert.alert-custom.alert-outline-info .alert-close i {
  opacity: 0.8;
  color: #3699ff;
}
.alert.alert-custom.alert-outline-info .alert-close:focus i,
.alert.alert-custom.alert-outline-info .alert-close:hover i {
  opacity: 1;
}
.alert.alert-custom.alert-warning {
  background-color: #ffa800;
  border-color: #ffa800;
}
.alert.alert-custom.alert-warning .alert-icon i {
  opacity: 0.8;
  color: #ffffff;
}
.alert.alert-custom.alert-warning .alert-text {
  color: #ffffff;
}
.alert.alert-custom.alert-warning .alert-close i {
  color: #ffffff;
}
.alert.alert-custom.alert-warning .alert-close:focus,
.alert.alert-custom.alert-warning .alert-close:hover {
  opacity: 1;
  color: #ffffff;
}
.alert.alert-custom.alert-light-warning {
  background-color: #fff4de;
  border-color: transparent;
}
.alert.alert-custom.alert-light-warning .alert-icon i {
  color: #ffa800;
}
.alert.alert-custom.alert-light-warning .alert-text {
  color: #ffa800;
}
.alert.alert-custom.alert-light-warning .alert-close i {
  color: #ffa800;
}
.alert.alert-custom.alert-light-warning .alert-close:focus,
.alert.alert-custom.alert-light-warning .alert-close:hover {
  color: #ee9d01;
}
.alert.alert-custom.alert-light-warning.alert-notice {
  border: 0;
  border-left: 4px solid #ffa800;
  border-top-left-radius: 0;
  border-bottom-left-radius: 0;
}
.alert.alert-custom.alert-outline-warning {
  background-color: transparent;
  border-color: #ffa800;
}
.alert.alert-custom.alert-outline-warning .alert-icon i {
  color: #ffa800;
}
.alert.alert-custom.alert-outline-warning .alert-text {
  color: #ffa800;
}
.alert.alert-custom.alert-outline-warning .alert-close i {
  opacity: 0.8;
  color: #ffa800;
}
.alert.alert-custom.alert-outline-warning .alert-close:focus i,
.alert.alert-custom.alert-outline-warning .alert-close:hover i {
  opacity: 1;
}
.alert.alert-custom.alert-danger {
  background-color: #f64e60;
  border-color: #f64e60;
}
.alert.alert-custom.alert-danger .alert-icon i {
  opacity: 0.8;
  color: #ffffff;
}
.alert.alert-custom.alert-danger .alert-text {
  color: #ffffff;
}
.alert.alert-custom.alert-danger .alert-close i {
  color: #ffffff;
}
.alert.alert-custom.alert-danger .alert-close:focus,
.alert.alert-custom.alert-danger .alert-close:hover {
  opacity: 1;
  color: #ffffff;
}
.alert.alert-custom.alert-light-danger {
  background-color: #ffe2e5;
  border-color: transparent;
}
.alert.alert-custom.alert-light-danger .alert-icon i {
  color: #f64e60;
}
.alert.alert-custom.alert-light-danger .alert-text {
  color: #f64e60;
}
.alert.alert-custom.alert-light-danger .alert-close i {
  color: #f64e60;
}
.alert.alert-custom.alert-light-danger .alert-close:focus,
.alert.alert-custom.alert-light-danger .alert-close:hover {
  color: #ee2d41;
}
.alert.alert-custom.alert-light-danger.alert-notice {
  border: 0;
  border-left: 4px solid #f64e60;
  border-top-left-radius: 0;
  border-bottom-left-radius: 0;
}
.alert.alert-custom.alert-outline-danger {
  background-color: transparent;
  border-color: #f64e60;
}
.alert.alert-custom.alert-outline-danger .alert-icon i {
  color: #f64e60;
}
.alert.alert-custom.alert-outline-danger .alert-text {
  color: #f64e60;
}
.alert.alert-custom.alert-outline-danger .alert-close i {
  opacity: 0.8;
  color: #f64e60;
}
.alert.alert-custom.alert-outline-danger .alert-close:focus i,
.alert.alert-custom.alert-outline-danger .alert-close:hover i {
  opacity: 1;
}
.alert.alert-custom.alert-light {
  background-color: #f3f6f9;
  border-color: #f3f6f9;
}
.alert.alert-custom.alert-light .alert-icon i {
  opacity: 0.8;
  color: #7e8299;
}
.alert.alert-custom.alert-light .alert-text {
  color: #7e8299;
}
.alert.alert-custom.alert-light .alert-close i {
  color: #7e8299;
}
.alert.alert-custom.alert-light .alert-close:focus,
.alert.alert-custom.alert-light .alert-close:hover {
  opacity: 1;
  color: #7e8299;
}
.alert.alert-custom.alert-light-light {
  background-color: #f3f6f9;
  border-color: transparent;
}
.alert.alert-custom.alert-light-light .alert-icon i {
  color: #f3f6f9;
}
.alert.alert-custom.alert-light-light .alert-text {
  color: #f3f6f9;
}
.alert.alert-custom.alert-light-light .alert-close i {
  color: #f3f6f9;
}
.alert.alert-custom.alert-light-light .alert-close:focus,
.alert.alert-custom.alert-light-light .alert-close:hover {
  color: #e4e6ef;
}
.alert.alert-custom.alert-light-light.alert-notice {
  border: 0;
  border-left: 4px solid #f3f6f9;
  border-top-left-radius: 0;
  border-bottom-left-radius: 0;
}
.alert.alert-custom.alert-outline-light {
  background-color: transparent;
  border-color: #f3f6f9;
}
.alert.alert-custom.alert-outline-light .alert-icon i {
  color: #3f4254;
}
.alert.alert-custom.alert-outline-light .alert-text {
  color: #3f4254;
}
.alert.alert-custom.alert-outline-light .alert-close i {
  opacity: 0.8;
  color: #3f4254;
}
.alert.alert-custom.alert-outline-light .alert-close:focus i,
.alert.alert-custom.alert-outline-light .alert-close:hover i {
  opacity: 1;
}
.alert.alert-custom.alert-dark {
  background-color: #181c32;
  border-color: #181c32;
}
.alert.alert-custom.alert-dark .alert-icon i {
  opacity: 0.8;
  color: #ffffff;
}
.alert.alert-custom.alert-dark .alert-text {
  color: #ffffff;
}
.alert.alert-custom.alert-dark .alert-close i {
  color: #ffffff;
}
.alert.alert-custom.alert-dark .alert-close:focus,
.alert.alert-custom.alert-dark .alert-close:hover {
  opacity: 1;
  color: #ffffff;
}
.alert.alert-custom.alert-light-dark {
  background-color: #d1d3e0;
  border-color: transparent;
}
.alert.alert-custom.alert-light-dark .alert-icon i {
  color: #181c32;
}
.alert.alert-custom.alert-light-dark .alert-text {
  color: #181c32;
}
.alert.alert-custom.alert-light-dark .alert-close i {
  color: #181c32;
}
.alert.alert-custom.alert-light-dark .alert-close:focus,
.alert.alert-custom.alert-light-dark .alert-close:hover {
  color: #131628;
}
.alert.alert-custom.alert-light-dark.alert-notice {
  border: 0;
  border-left: 4px solid #181c32;
  border-top-left-radius: 0;
  border-bottom-left-radius: 0;
}
.alert.alert-custom.alert-outline-dark {
  background-color: transparent;
  border-color: #181c32;
}
.alert.alert-custom.alert-outline-dark .alert-icon i {
  color: #181c32;
}
.alert.alert-custom.alert-outline-dark .alert-text {
  color: #181c32;
}
.alert.alert-custom.alert-outline-dark .alert-close i {
  opacity: 0.8;
  color: #181c32;
}
.alert.alert-custom.alert-outline-dark .alert-close:focus i,
.alert.alert-custom.alert-outline-dark .alert-close:hover i {
  opacity: 1;
}
.alert.alert-custom.alert-white {
  background-color: #ffffff;
  border-color: #ffffff;
}
.alert.alert-custom.alert-white .alert-icon i {
  opacity: 0.8;
  color: #3f4254;
}
.alert.alert-custom.alert-white .alert-text {
  color: #3f4254;
}
.alert.alert-custom.alert-white .alert-close i {
  color: #3f4254;
}
.alert.alert-custom.alert-white .alert-close:focus,
.alert.alert-custom.alert-white .alert-close:hover {
  opacity: 1;
  color: #3f4254;
}
.alert.alert-custom.alert-light-white {
  background-color: #ffffff;
  border-color: transparent;
}
.alert.alert-custom.alert-light-white .alert-icon i {
  color: #ffffff;
}
.alert.alert-custom.alert-light-white .alert-text {
  color: #ffffff;
}
.alert.alert-custom.alert-light-white .alert-close i {
  color: #ffffff;
}
.alert.alert-custom.alert-light-white .alert-close:focus,
.alert.alert-custom.alert-light-white .alert-close:hover {
  color: #f3f6f9;
}
.alert.alert-custom.alert-light-white.alert-notice {
  border: 0;
  border-left: 4px solid #ffffff;
  border-top-left-radius: 0;
  border-bottom-left-radius: 0;
}
.alert.alert-custom.alert-outline-white {
  background-color: transparent;
  border-color: #ffffff;
}
.alert.alert-custom.alert-outline-white .alert-icon i {
  color: #ffffff;
}
.alert.alert-custom.alert-outline-white .alert-text {
  color: #ffffff;
}
.alert.alert-custom.alert-outline-white .alert-close i {
  opacity: 0.8;
  color: #ffffff;
}
.alert.alert-custom.alert-outline-white .alert-close:focus i,
.alert.alert-custom.alert-outline-white .alert-close:hover i {
  opacity: 1;
}
</style>
