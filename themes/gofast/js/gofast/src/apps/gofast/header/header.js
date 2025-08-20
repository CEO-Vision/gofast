import { createApp } from 'vue/dist/vue.esm-bundler.js';
import Image from '../../../components/global/Image.vue';
import Profile from './Profile.vue';

export function accountHeader() {
  const app = createApp(Profile);
  app.component('Image', Image);
  app.mount('#app-profile');
}
