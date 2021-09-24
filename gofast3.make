; Drush makefile - GoFast-3.x drupal installation
; -> generated from GoFast-2.x sources (2014)
; -> used for Gofast3.x installation script

core = 7.x

api = 2
projects[drupal][version] = "7.38"

; Modules
projects[views_bulk_operations][version] = "3.3"

projects[advanced_forum][version] = "2.6"

projects[apachesolr][version] = "1.8"

projects[apachesolr_og][version] = "1.0"

projects[apachesolr_user][version] = "1.x-dev"

projects[autocomplete_deluxe][version] = "2.1"

projects[backup_migrate][version] = "2.8"

projects[ctools][version] = "1.7"

projects[bundle_copy][version] = "1.1"

projects[calendar][version] = "3.5"

projects[chosen][version] = "2.0-beta4"

projects[ckeditor][version] = "1.16"

projects[ckeditor_link][version] = "2.3"

projects[cmis][version] = "1.6"

projects[facetapi][version] = "1.5"

projects[date][version] = "2.9"

projects[devel][version] = "1.5"

projects[drupalchat][version] = "1.5"

projects[elysia_cron][version] = "2.1"

projects[entity][version] = "1.6"

projects[entityreference][version] = "1.1"

projects[statehandler][version] = "1.0-alpha1"

projects[features_extra][version] = "1.0-beta1"

projects[features][version] = "2.0"
projects[features][patches][] = "http://dev2.ceo-vision.com/sites/default/files/sources-3.x/patch/features-catch_field_exceptions.patch"

projects[field_group][version] = "1.4"

projects[fivestar][version] = "2.1"

projects[flag][version] = "3.6"

projects[floating_block][version] = "1.3"

projects[form_builder][version] = "1.10"

projects[history_js][version] = "1.0"

projects[i18n][version] = "1.13"

projects[job_scheduler][version] = "2.0-alpha3"

projects[jquery_update][version] = "2.7"

projects[ldap][version] = "2.0-beta8"

projects[libraries][version] = "2.2"

projects[mailsystem][version] = "2.34"

projects[messaging][version] = "1.0-alpha2"

projects[mimemail][version] = "1.0-beta3"

projects[notifications][version] = "1.0-alpha2"

projects[og][version] = "2.7"

projects[og_subgroups][version] = "2.0-alpha1"

projects[og_vocab][version] = "1.2"

projects[options_element][version] = "1.12"

projects[pathauto][version] = "1.2"

projects[phpmailer][version] = "3.x-dev"

projects[privatemsg][version] = "2.x-dev"

projects[print][version] = "1.3"

projects[quickedit][version] = "1.4"

projects[radioactivity][version] = "2.10"

projects[recently_read][version] = "3.1"

projects[session_api][version] = "1.0-rc1"

projects[strongarm][version] = "2.0"

projects[tableofcontents][version] = "2.x-dev"

projects[term_reference_tree][version] = "1.10"

projects[token][version] = "1.6"

projects[translation_helpers][version] = "1.0"

projects[user_relationships][version] = "1.0-alpha5"

projects[userpoints][version] = "1.1"

projects[userpoints_nc][version] = "1.0"

projects[uuid][version] = "1.0-alpha6"

projects[uuid_features][version] = "1.0-alpha4"

projects[variable][version] = "2.5"

projects[views][version] = "3.11"

projects[views_tree][version] = "2.0"

projects[votingapi][version] = "2.12"

projects[webform][version] = "3.24"

;;;;;;;;;;; Themes ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

projects[bootstrap][version] = "3.0"

projects[bootstrap-business][version] = "1.0"

projects[fusion][version] = "2.0-beta2"

projects[tweme][version] = "1.2-alpha1"

; GoFast Theme (bootstrap subtheme)
projects[bootstrap-gofast][download][type] = "get"
projects[bootstrap-gofast][download][url] = "http://dev2.ceo-vision.com/sites/default/files/sources-3.x/3.0/gofast_theme_3.0.tar.gz"
projects[bootstrap-gofast][type] = "theme"
projects[bootstrap-gofast][overwrite] = TRUE

;;;;;;;;;;; GoFast ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; GoFast Modules
projects[gofast][type] = "module"
projects[gofast][download][type] = "get"
projects[gofast][download][version] = "7.x-2.0"
projects[gofast][download][url] = "http://dev2.ceo-vision.com/sites/default/files/sources-3.x/3.0/gofast_modules_3.0.tar.gz"
projects[gofast][overwrite] = TRUE

;;;;;;;;;;; Libraries ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; itHit
libraries[ajax_file_browser][download][type] = "get"
libraries[ajax_file_browser][download][url] = "http://www.ceo-vision.com/sites/ceo-vision.com/files/download/install/ITHitAJAXFileBrowserSource.tar.gz"
libraries[ajax_file_browser][directory_name] = "ajax_file_browser"
libraries[ajax_file_browser][type] = "library"
libraries[ajax_file_browser][overwrite] = TRUE

; Backbone.js
libraries[backbone][download][type] = "get"
libraries[backbone][download][url] = "http://backbonejs.org/backbone-min.js"
libraries[backbone][directory_name] = "backbone"
libraries[backbone][type] = "library"
libraries[backbone][overwrite] = TRUE

; Balupton-history.js
libraries[balupton-history.js][download][type] = "get"
libraries[balupton-history.js][download][url] = "https://github.com/browserstate/history.js/archive/1.8.0b2.tar.gz"
libraries[balupton-history.js][directory_name] = "balupton-history.js"
libraries[balupton-history.js][type] = "library"
libraries[balupton-history.js][overwrite] = TRUE

; Bootstrap-datetimepicker.js
libraries[balupton-history.js][download][type] = "get"
libraries[balupton-history.js][download][url] = "https://github.com/smalot/bootstrap-datetimepicker/archive/2.3.5.tar.gz"
libraries[balupton-history.js][directory_name] = "bootstrap-datetimepicker"
libraries[balupton-history.js][type] = "library"
libraries[balupton-history.js][overwrite] = TRUE

; Chosen.js
;libraries[chosen][download][type] = "get"
;libraries[chosen][download][url] = "https://github.com/harvesthq/chosen/archive/1.4.2.tar.gz"
;libraries[chosen][directory_name] = "chosen"
;libraries[chosen][type] = "library"
;libraries[chosen][overwrite] = TRUE

; CKEditor 4.4.7
libraries[ckeditor][download][type] = "get"
libraries[ckeditor][download][url] = "http://dev2.ceo-vision.com/sites/default/files/sources-3.x/3.0/ckeditor_custom_build_gofast3.0.tar.gz"
libraries[ckeditor][destination] = "libraries"
libraries[ckeditor][overwrite] = TRUE

; PDF.js
libraries[pdf][download][type] = "get"
libraries[pdf][download][url] = "https://github.com/mozilla/pdf.js/archive/v1.1.469.tar.gz"
libraries[pdf][directory_name] = "pdf"
libraries[pdf][type] = "library"
libraries[pdf][overwrite] = TRUE

; PHPMailer
libraries[phpmailer][download][type] = "get"
libraries[phpmailer][download][url] = "https://github.com/PHPMailer/PHPMailer/archive/v5.2.14.tar.gz"
libraries[phpmailer][destination] = "libraries"
libraries[phpmailer][directory_name] = "phpmailer"
libraries[phpmailer][overwrite] = TRUE

; Select2.js
;libraries[chosen][download][type] = "get"
;libraries[chosen][download][url] = "https://github.com/select2/select2/archive/3.5.4.tar.gz"
;libraries[chosen][directory_name] = "chosen"
;libraries[chosen][type] = "library"
;libraries[chosen][overwrite] = TRUE

; Underscore.js
libraries[underscore][download][type] = "get"
libraries[underscore][download][url] = "http://underscorejs.org/underscore-min.js"
libraries[underscore][directory_name] = "underscore"
libraries[underscore][type] = "library"
libraries[underscore][overwrite] = TRUE

; X-editable.js
;libraries[chosen][download][type] = "get"
;libraries[chosen][download][url] = "https://github.com/vitalets/x-editable/archive/1.5.1.tar.gz"
;libraries[chosen][directory_name] = "chosen"
;libraries[chosen][type] = "library"
;libraries[chosen][overwrite] = TRUE

; zTree
libraries[ztree][download][type] = "get"
libraries[ztree][download][url] = "https://github.com/zTree/zTree_v3/archive/v3.5.18.tar.gz"
libraries[ztree][directory_name] = "ztree"
libraries[ztree][type] = "library"
libraries[ztree][overwrite] = TRUE
