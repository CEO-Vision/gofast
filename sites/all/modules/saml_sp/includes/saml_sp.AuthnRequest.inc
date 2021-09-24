<?php
use OneLogin\Saml2\AuthnRequest;
use \OneLogin\Saml2\Settings;

class saml_sp_AuthnRequest extends AuthnRequest {

  /**
   * Constructs the AuthnRequest object.
   *
   * @param OneLogin\Saml2\Settings $settings Settings
   */
  public function __construct(Settings $settings, $forceAuthn = false, $isPassive = false, $setNameIdPolicy = true) {
    parent::__construct($settings, $forceAuthn, $isPassive, $setNameIdPolicy);

    if (variable_get('saml_sp__debug', FALSE)) {
      watchdog('saml_sp', 'samlp:AuthnRequest =><br/><pre>@request</pre>', array('@request' => $this->getXML()), WATCHDOG_DEBUG);
      if (function_exists('dpm')) {
        dpm($this->getXML(), 'samlp:AuthnRequest');
      }
    }
  }
}
