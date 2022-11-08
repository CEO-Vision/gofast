<div class="aside aside-left aside-fixed d-flex flex-column flex-row-auto" id="kt_aside">
  <!--begin::Brand-->
  <div class="brand flex-column-auto" id="kt_brand">
      <!--begin::Logo-->
      <a href="index.html" class="brand-logo">
          <img alt="Logo" src="assets/media/logos/logo-1.svg" class="h-30px" />
      </a>
      <!--end::Logo-->
      <!--begin::Toggle-->
      <button class="brand-toggle btn btn-sm px-0" id="kt_aside_toggle">
          <span class="svg-icon svg-icon svg-icon-xl">
              <!--begin::Svg Icon | path:assets/media/svg/icons/Text/Toggle-Right.svg-->
              <svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" width="24px" height="24px" viewBox="0 0 24 24" version="1.1">
                  <g stroke="none" stroke-width="1" fill="none" fill-rule="evenodd">
                      <rect x="0" y="0" width="24" height="24" />
                      <path fill-rule="evenodd" clip-rule="evenodd" d="M22 11.5C22 12.3284 21.3284 13 20.5 13H3.5C2.6716 13 2 12.3284 2 11.5C2 10.6716 2.6716 10 3.5 10H20.5C21.3284 10 22 10.6716 22 11.5Z" fill="black" />
                      <path opacity="0.5" fill-rule="evenodd" clip-rule="evenodd" d="M14.5 20C15.3284 20 16 19.3284 16 18.5C16 17.6716 15.3284 17 14.5 17H3.5C2.6716 17 2 17.6716 2 18.5C2 19.3284 2.6716 20 3.5 20H14.5ZM8.5 6C9.3284 6 10 5.32843 10 4.5C10 3.67157 9.3284 3 8.5 3H3.5C2.6716 3 2 3.67157 2 4.5C2 5.32843 2.6716 6 3.5 6H8.5Z" fill="black" />
                  </g>
              </svg>
              <!--end::Svg Icon-->
          </span>
      </button>
      <!--end::Toolbar-->
  </div>
  <!--end::Brand-->
  <!--begin::Aside Menu-->
  <div class="aside-menu-wrapper flex-column-fluid" id="kt_aside_menu_wrapper">
      <!--begin::Menu Container-->
      <div id="kt_aside_menu" class="aside-menu my-4" data-menu-vertical="1" data-menu-scroll="1" data-menu-dropdown-timeout="500">
          <!--begin::Menu Nav-->
          <?php echo theme('gofast_menu_aside_menu', ['menus' => $menus]);?>
          <!--end::Menu Nav-->
      </div>
      <!--end::Menu Container-->
  </div>
  <!--end::Aside Menu-->
</div>