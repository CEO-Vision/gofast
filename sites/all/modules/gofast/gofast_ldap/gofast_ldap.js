
/**
 * @file
 *  Handles Gofast LDAP front-end functionalities
 */

(function ($, Gofast, Drupal) {

  Drupal.settings.gofast = Drupal.settings.gofast || {};
  Gofast.ldap = Gofast.ldap || {};

  /**
   * Fixes LDAP Admin form #states, header 'select all' checkbox is not handled
   * by the system.
   */
  Drupal.behaviors.gofastLDAPAdminFixState = {
    attach: function (context, settings) {
      $('#gofast-ldap-admin-entries .select-all input[type="checkbox"]', context).once('states', function () {
        $(this).on('change', function () {
          var checked = this.checked;
          $('#edit-submit-import').prop('disabled', function (i, v) {
            return !checked;
          });
        });
      });
    }
  };

  /**
   * Refresh the count of selected LDAP entries when user updates the selection.
   */
  Drupal.behaviors.gofastLDAPAdminCountSelected = {
    attach: function (context, settings) {
      var $results = $('#gofast-ldap-admin-entries #edit-results', context);
      $results.find('input[type="checkbox"]').once('selection', function () {
        $(this).on('change', function () {
          // 'form-item' class used to exclude 'select-all' elements.
          var count = $results.find('.form-item input[type="checkbox"]:checked').length;
          $('.ldap-selected').html(Drupal.formatPlural(count, '@count entry selected.', '@count entries selected.'));
        });
      });
    }
  };

  /**
   * Binds a submit handler to the admin form so that options can be submitted
   * in a second step.
   */
  Drupal.behaviors.gofastLDAPAdminSubmit = {
    attach: function (context, settings) {
      $('#gofast-ldap-admin-entries', context).once('submit', function () {
        var $form = $(this);

        $form.submit(function (e) {
          var $btn = $(document.activeElement),
                  is_submit = $btn.length && $form.has($btn) && $btn.is('button[type="submit"], input[type="submit"]');

          if (!is_submit || $btn.val() !== Drupal.t('Import Selection', {}, {'context' : 'gofast:gofast_ldap'})) {
            return;
          }

          // Get import options from DOM, we don't use the original wrapper to
          // prevents unwanted bindings.
          var $opt = $('.gofast-ldap-admin-import-options', $form).clone(),
                  $wrapper = $('<div class="import-options">');

          // Preserve roles ids.
          $('[id^="edit-roles-"], [for^="edit-roles-"]', $opt).each(function () {
            var id = $(this).prop('id'), key = id && 'id' || 'for';
            $(this).prop(key, $(this).prop(key) + '--cloned');
          });

          $wrapper.html($opt.html());
          Gofast.modal($wrapper[0].outerHTML, Drupal.t('Import options', {}, {'context' : 'gofast:gofast_ldap'}));

          // Apply behavior to the cloned element.
          var $roles = $('.form-item-roles input[type=checkbox]', $('#modal-content'));
          if('undefined' !== typeof($roles)){
            $roles.once('single-role', function () {
              $(this).on('change', function () {
                if ($(this).hasClass("role_contributor")) {
                  $roles.not(this).not(':disabled').prop('checked', false);
                }
                if ($(this).hasClass("role_administrator") || $(this).hasClass("role_business_adm")) {
                  $('.role_contributor').prop('checked', false);
                }
              });
            });
          }

          $('.import-options button').click(function () {
            var op = $(this).attr('op');
            op === 'cancel' && Gofast.closeModal();

            if (op === 'save') {
              // Apply selected values into the original form elements.
              $('.import-options').find('input, select').each(function () {
                var id = $(this).attr('id').replace('--cloned', '');
                if (this.type === 'checkbox')
                  $('#' + id, $form).prop('checked', this.checked);
                else
                  $('#' + id, $form).val($(this).val());
              });

              Gofast.closeModal();

              // Finally submit the form, it will trigger the handler again but
              // without running preventDefault(). We do not run $form.submit()
              // to avoid unning the default submit callback (server side) that
              // is the 'search' op.
              $btn.click();
            }
          });

          e.preventDefault();
        });
      });
    }
  };

  /**
   * Maintains state of the password field according to the actual value of the
   * SASL authentication field (user account register/edit forms).
   */
  Drupal.behaviors.gofastLDAPAccountPasswordState = {
    attach: function (context, settings) {
      var $account = $('#user-register-form', context);
      var $account = $('#user-register-form, #user_profile_form'),
        $pass = $('input[type="password"]', $account),
        $select_pass = $('select[name="select_pass"]', $account),
        $sasl = $('input[name="sasl_auth[und]"]', $account);
        $welcome_checkbox = $('input[name="notify"]', $account);
      if (window.location.pathname.indexOf('/admin/people/create') !== -1){
        var create = true;
      }else{
        var create = false;
      }
      // User create form
      if(create){
        if($sasl.prop('checked') == true){
          $pass.prop('disabled', true) && $select_pass.closest('.form-item-select-pass').hide(300) && $pass.closest('.edit-pass-wrapper').hide(300);
        }else if($select_pass.val() == 0){
          $pass.prop('disabled', true) && $pass.closest('.edit-pass-wrapper').hide(300);
        }
        $select_pass.on('change', function(){
          if ($(this).val() == 0) $welcome_checkbox.prop("checked", true);
        }
        );
        $sasl.once('states', function () {
          $(this).on('change', function () {
            $pass.prop('disabled', this.checked);
            if($select_pass.length == 0){
                if(this.checked == 0){
                  $pass.closest('.edit-pass-wrapper').toggle(300);
                }else{
                  $pass.closest('.edit-pass-wrapper').hide(300);
                }
            }else{
              if($select_pass.val() == 1){
                  $pass.closest('.edit-pass-wrapper').toggle(300);
                }else{
                  $pass.closest('.edit-pass-wrapper').hide(300);
              }
              $select_pass.closest('.form-item-select-pass').toggle(300);
            }
          });
        });
        $select_pass.once('states', function(){
          $(this).on('change', function(){
              if($select_pass.val() == 0){
                $pass.prop('disabled', true);
                $pass.closest('.edit-pass-wrapper').hide(300);
              }else{
                $pass.prop('disabled', false);
                $pass.closest('.edit-pass-wrapper').toggle(300);
              }
          });
        });
      }else{ //User edit form
        var isAdmin = $('input.role_administrator').length == 1;
        // Form is different if current user is admin
        if(isAdmin){
          if($sasl.prop('checked') == true){
            $pass.closest('.edit-pass-wrapper').hide(300);
          }
          $sasl.once('states', function () {
            $(this).on('change', function () {
              $pass.prop('disabled', this.checked);
              if(this.checked == 0){
                $pass.closest('.edit-pass-wrapper').toggle(300);
              }else{
                $pass.closest('.edit-pass-wrapper').hide(300);
              }
            });
          });
        }else{
          return;
        }
      }
    }
  };

  Drupal.BootstrapPassword = function(element) {
    var self = this;
    var $element = $(element);
    this.settings = Drupal.settings.password;  
    var min_password_length = Drupal.settings.min_password_length;
    Drupal.settings.password.addPunctuation = Drupal.t('Add special character', {}, {context : 'gofast:ldap'});
    Drupal.settings.password.hasWeaknesses = Drupal.t('Please fulfill the following conditions:', {}, {context : 'gofast:ldap'});
    Drupal.settings.password.tooShort = Drupal.t('Make it at least !number characters', {'!number' : min_password_length}, {context : 'gofast:ldap'});
    this.$wrapper = $element.parent().parent();
    //this.$row = $('<div class="row">').prependTo(this.$wrapper);

    // The password object.
    this.password = {
      $input: $element.addClass('col-md-4'),
      $label: $element.parent().find('label'),
      $wrapper: $element.parent().addClass('has-feedback')
    };

    // Gofast Custom
    debugger;
    var $containerFluid = $('<div ></div>');
    var $passwordRow = $('<div class="d-flex"></div>').appendTo($containerFluid);
    var $labelColumn = $('<div class="col-md-2"></div>');
    var $helpBlockText = $('<div class="gofast_help_block"></div>');
    $helpBlockText.appendTo(this.$wrapper);
    this.password.$input.detach().appendTo($passwordRow);
    $labelColumn.appendTo($passwordRow);

    $containerFluid.appendTo(this.password.$wrapper);
    // Strength meter.
    this.strength = {
      $label: $('<div class="label rounded w-50 m-1" aria-live="assertive"></div>').appendTo($labelColumn),
      $progress: $('<div class="progress"><div class="progress-bar" role="progressbar" aria-valuenow="0" aria-valuemin="0" aria-valuemax="100"></div></div>').appendTo($labelColumn)
    };
    this.strength.$bar = this.strength.$progress.find('.progress-bar');
    this.password.$icon = $('<span class="glyphicon form-control-feedback"></span>').appendTo(this.strength.$progress);
    // The confirmation object.
    this.confirm = {
      $input: this.$wrapper.find('input.password-confirm')
    };
    this.confirm.$wrapper = this.confirm.$input.parent().addClass('has-feedback').appendTo(this.$wrapper);
    this.confirm.$icon = $('<span class="glyphicon form-control-feedback"></span>');

    // Bind events.
    this.password.$input.on('keyup focus blur', function () {
      self.validateStrength();
    });
    this.confirm.$input.on('keyup blur', function () {
      self.validateMatch();
    });
    $('.form-type-password-confirm .help-block').detach().appendTo($helpBlockText);
    // Add password help at the of row.
    this.$helpBlock = $('<div class="help-block password-help" style="color:#a94442"></div>').appendTo(this.$wrapper);

    return this;
  };

/**
   * Helper method to switch classes on elements based on status.
   *
   * @param {jQuery} $element
   *   The jQuery element to modify.
   * @param {string} type
   *   The name of the class to switch to. Can be one of: "danger", "info",
   *   "success" or "warning".
   * @param {string} prefix
   *   The prefix to use. Typically this would be something like "label" or
   *   "progress-bar".
   */
  Drupal.BootstrapPassword.prototype.switchClass = function ($element, type, prefix) {
    prefix = prefix + '-' || '';
    var types = prefix === 'has-' ? ['error', 'warning', 'success'] : ['danger', 'info', 'success', 'warning'];
    if (type) {
      type = types.splice($.inArray(type, types), 1).shift();
      $element.addClass(prefix + type);
    }
    $element.removeClass(prefix + types.join(' ' + prefix));
  };

  /**
   * Validates the strength of a password.
   */
  Drupal.BootstrapPassword.prototype.validateStrength = function () {
    var result = Drupal.gofastEvaluatePasswordStrength(this.password.$input.val(), Drupal.settings.password);

    // Ensure visibility.
    this.$helpBlock.show();
    this.strength.$label.show();
    this.strength.$bar.show();

    // Update the suggestions for how to improve the password.
    this.$helpBlock.html(result.message);

    // Only show the description box if there is a weakness in the password.
    this.$helpBlock[result.strength === 100 ? 'hide' : 'show']();

    // Update the strength indication text.
    this.strength.$label.html(result.indicatorText);

    // Adjust the length of the strength indicator.
    this.strength.$bar.attr('aria-valuenow', result.strength);
    this.strength.$bar.css('width', result.strength + '%');

    // Change the classes (color) of the strength meter based on result level.
    switch (result.indicatorText) {
      case this.settings.weak:
        this.switchClass(this.password.$wrapper, 'error', 'has');
        this.switchClass(this.strength.$label, 'danger', 'label');
        this.switchClass(this.strength.$bar, 'danger', 'progress-bar');
        this.password.$icon.addClass('glyphicon-remove').removeClass('glyphicon-warning-sign glyphicon-ok');
        break;

      case this.settings.fair:
      case this.settings.good:
        this.switchClass(this.password.$wrapper, 'warning', 'has');
        this.switchClass(this.strength.$label, 'warning', 'label');
        this.switchClass(this.strength.$bar, 'warning', 'progress-bar');
        this.password.$icon.addClass('glyphicon-warning-sign').removeClass('glyphicon-remove glyphicon-ok');
        break;

      case this.settings.strong:
        this.switchClass(this.password.$wrapper, 'success', 'has');
        this.switchClass(this.strength.$label, 'success', 'label');
        this.switchClass(this.strength.$bar, 'success', 'progress-bar');
        this.password.$icon.addClass('glyphicon-ok').removeClass('glyphicon-warning-sign glyphicon-remove');
        break;
    }
    this.validateMatch();
  };

  /**
   * Validates both original and confirmation passwords to ensure they match.
   */
  Drupal.BootstrapPassword.prototype.validateMatch = function () {
    var password = this.password.$input.val();
    var strength = Drupal.gofastEvaluatePasswordStrength(password, Drupal.settings.password).strength;

    // Passwords match.
    if (password && password === this.confirm.$input.val() && strength == 100) {
      $('#submit_create_user').removeAttr( "title");
      this.switchClass(this.password.$wrapper, 'success', 'has');
      this.switchClass(this.confirm.$wrapper, 'success', 'has');
      this.$helpBlock.hide();
      this.strength.$label.hide();
      this.strength.$bar.hide();
      this.password.$icon.addClass('glyphicon-ok').removeClass('glyphicon-warning-sign glyphicon-remove');
      this.confirm.$icon.addClass('glyphicon-ok').removeClass('glyphicon-remove');
    }
    // Passwords do not match.
    else if (password) {
      $('#submit_create_user').prop('title',Drupal.t('Password does not meet the conditions',{},{ context : 'gofast:ldap'}));
      this.switchClass(this.confirm.$wrapper, 'error', 'has');
      this.confirm.$icon.addClass('glyphicon-remove').removeClass('glyphicon-ok');
    }
    // No password.
    else {
      $('#submit_create_user').removeAttr( "title");
      this.confirm.$icon.removeClass('glyphicon-ok glyphicon-remove');
      this.confirm.$input.val('');
      this.switchClass(this.confirm.$wrapper, '', 'has');
    }
  };

    /**
     * Evaluate the strength of a user's password.
     *
     * Returns the estimated strength and the relevant output message.
     */
    Drupal.gofastEvaluatePasswordStrength = function (password, translate) {
      password = $.trim(password);

      var weaknesses = 0, strength = 100, msg = [];

      var hasLowercase = /[a-z]+/.test(password);
      var hasUppercase = /[A-Z]+/.test(password);
      var hasNumbers = /[0-9]+/.test(password);
      var hasPunctuation = /[^a-zA-Z0-9]+/.test(password);

      // If there is a username edit box on the page, compare password to that, otherwise
      // use value from the database.
      var usernameBox = $('input.username');
      var username = (usernameBox.length > 0) ? usernameBox.val() : translate.username;

      // Lose 5 points for every character less than 8, plus a 30 point penalty.
      var min_password_length = Drupal.settings.min_password_length;     
      if (password.length < min_password_length) {
        msg.push(translate.tooShort);
        strength -= ((min_password_length - password.length) * 5) + 30;
      }

      // Count weaknesses.
      if (!hasLowercase) {
        msg.push(translate.addLowerCase);
        weaknesses++;
      }
      if (!hasUppercase) {
        msg.push(translate.addUpperCase);
        weaknesses++;
      }
      if (!hasNumbers) {
        msg.push(translate.addNumbers);
        weaknesses++;
      }
      if (!hasPunctuation) {
        msg.push(translate.addPunctuation);
        weaknesses++;
      }

      // Apply penalty for each weakness (balanced against length penalty).
      switch (weaknesses) {
        case 1:
          strength -= 12.5;
          break;

        case 2:
          strength -= 25;
          break;

        case 3:
          strength -= 40;
          break;

        case 4:
          strength -= 40;
          break;
      }

      // Check if password is the same as the username.
      if (password !== '' && password.toLowerCase() === username.toLowerCase()) {
        msg.push(translate.sameAsUsername);
        // Passwords the same as username are always very weak.
        strength = 5;
      }

      // Based on the strength, work out what text should be shown by the password strength meter.
      if (strength < 60) {
        indicatorText = translate.weak;
      } else if (strength < 70) {
        indicatorText = translate.fair;
      } else if (strength < 90) {
        indicatorText = translate.good;
      } else if (strength <= 100) {
        indicatorText = translate.strong;
      }

      // Assemble the final message.
      msg = translate.hasWeaknesses + '<ul><li>' + msg.join('</li><li>') + '</li></ul>';
      return { strength: strength, message: msg, indicatorText: indicatorText };

    };

})(jQuery, Gofast, Drupal);
