<template>
  <div
    class="cursor-pointer symbol symbol-35px symbol-md-40px"
    data-kt-menu-trigger="{default: 'click', lg: 'hover'}"
    data-kt-menu-attach="parent"
    data-kt-menu-placement="bottom-end"
  >
    <div class="symbol symbol-50px me-5">
      <Image :src="profile.picture.src" :alt="profile.picture.alt" />
    </div>
  </div>
  <div
    class="menu menu-sub menu-sub-dropdown menu-column menu-rounded menu-gray-800 menu-state-bg menu-state-color fw-semibold py-4 fs-6 w-275px"
    data-kt-menu="true"
  >
    <div class="menu-item px-3">
      <div class="menu-content d-flex align-items-center px-3">
        <div class="d-flex flex-column">
          <div class="fw-bold d-flex align-items-center fs-5">
            {{ profile.firstname }} {{ profile.lastname }}
          </div>
          <a href="#" class="fw-semibold text-muted text-hover-primary fs-7">
            {{ profile.email }}
          </a>
        </div>
      </div>
    </div>
    <div class="separator my-2" />
    <div class="menu-item px-5">
      <a href="/user/logout" class="menu-link px-5"> Deconnexion </a>
    </div>
  </div>
</template>

<script>
import { ref, onMounted } from 'vue';

export default {
  setup() {
    const profile = ref({
      picture: {
        src: '',
        alt: 'Chargement',
      },
      firstname: '',
      lastname: '',
      email: '',
    });

    onMounted(async () => {
      try {
        // TODO : Async
        profile.value.picture.src = '/themes/gofast/images/user.png';
        profile.value.picture.alt = 'User Picture';
        profile.value.firstname = 'Jérôme';
        profile.value.lastname = 'LEMAN--GARIN';
        profile.value.email = 'jerome.leman@ceo-vision.com';
      } catch (error) {
        console.error('Error loading profile data', error);
      }
    });

    return { profile };
  },
};
</script>
