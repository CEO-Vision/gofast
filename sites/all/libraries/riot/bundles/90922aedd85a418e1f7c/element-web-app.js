(window.webpackJsonp=window.webpackJsonp||[]).push([[11],{1579:function(e,n,o){"use strict";o.r(n),o.d(n,"loadApp",(function(){return C}));var t=o(82),a=o.n(t),i=o(104),r=o(120),s=o(84),l=o(274),c=o(244),d=o(288),u=o(92),g=o(1),w=o(22),f=o(153);window.React=a.a;let h=null;function p(e){const n=Object(w.b)(e);return{screen:n.location.substring(1),params:n.params}}function m(e){decodeURIComponent(window.location.hash)!==h&&function(e){if(!window.matrixChat)return;g.a.log("Routing URL ",e.href);const n=p(e);window.matrixChat.showScreen(n.screen,n.params)}(window.location)}function _(e,n=!1){g.a.log("newscreen "+e);const o="#/"+e;h=o,e.startsWith("room/")&&window.location.hash.includes("/$")===o.includes("/$")&&window.location.hash.startsWith(o)&&(n=!0),n?window.location.replace(o):window.location.assign(o)}function v(e){let n;n="vector:"===window.location.protocol?"https://app.element.io/#/register":window.location.protocol+"//"+window.location.host+window.location.pathname+"#/register";const o=Object.keys(e);for(let t=0;t<o.length;++t){n+=0===t?"?":"&";const a=o[t];n+=a+"="+encodeURIComponent(e[a])}return n}function b(){const e=new URL(window.location.href);e.searchParams.delete("loginToken"),g.a.log(`Redirecting to ${e.href} to drop loginToken from queryparams`),window.history.replaceState(null,"",e.href)}async function C(e){window.addEventListener("hashchange",m);const n=r.a.get(),o=Object(w.a)(window.location),t=window.location.protocol+"//"+window.location.host+window.location.pathname;g.a.log("Vector starting at "+t),n.startUpdater();const h=await async function(){let e;try{g.a.log("Verifying homeserver configuration");const n=u.a.get();let o=n.default_server_config;const t=n.default_server_name,a=n.default_hs_url,i=n.default_is_url,r=[o,t,a].filter(e=>!!e);if(r.length>1)throw Object(s.h)(Object(s.b)("Invalid configuration: can only specify one of default_server_config, default_server_name, or default_hs_url."));if(r.length<1)throw Object(s.h)(Object(s.b)("Invalid configuration: no default server specified."));a&&(g.a.log("Config uses a default_hs_url - constructing a default_server_config using this information"),g.a.warn("DEPRECATED CONFIG OPTION: In the future, default_hs_url will not be accepted. Please use default_server_config instead."),o={"m.homeserver":{base_url:a}},i&&(o["m.identity_server"]={base_url:i}));let d=null;o&&(g.a.log("Config uses a default_server_config - validating object"),d=await c.a.fromDiscoveryConfig(o)),t&&(g.a.log("Config uses a default_server_name - doing .well-known lookup"),g.a.warn("DEPRECATED CONFIG OPTION: In the future, default_server_name will not be accepted. Please use default_server_config instead."),d=await c.a.findClientConfig(t)),e=l.a.buildValidatedConfigFromDiscovery(t,d,!0)}catch(n){const{hsUrl:o,isUrl:t,userId:a}=await d.c();if(!o||!a)throw n;g.a.error(n),g.a.warn("A session was found - suppressing config error and using the session's homeserver"),g.a.log("Using pre-existing hsUrl and isUrl: ",{hsUrl:o,isUrl:t}),e=await l.a.validateServerConfigWithStaticUrls(o,t,!0)}return e.isDefault=!0,g.a.log("Using homeserver config:",e),g.a.log("Updating SdkConfig with validated discovery information"),u.a.add({validated_server_config:e}),u.a.get()}(),[C]=await d.b(),U=!!C,y=!!o.loginToken,O=Object(u.b)(h);let D=!0===O.immediate;const k="#/welcome"===window.location.hash||"#"===window.location.hash;if(!D&&O.on_welcome_page&&k&&(D=!0),!U&&!y&&D){g.a.log("Bypassing app load to redirect to SSO");const e=Object(f.createClient)({baseUrl:h.validated_server_config.hsUrl,idBaseUrl:h.validated_server_config.isUrl});return void r.a.get().startSingleSignOn(e,"sso","/"+p(window.location).screen)}const I=i.getComponent("structures.MatrixChat");return a.a.createElement(I,{onNewScreen:_,makeRegistrationUrl:v,config:h,realQueryParams:o,startingFragmentQueryParams:e,enableGuest:!h.disable_guests,onTokenLoginCompleted:b,initialScreenAfterLogin:p(window.location),defaultDeviceDisplayName:n.getDefaultDeviceDisplayName()})}g.a.log("Application is running in production mode"),window.matrixLogger=g.a}}]);
//# sourceMappingURL=element-web-app.js.map