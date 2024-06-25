
/**
 * @file
 *
 * Gofast long poll system.
 *
 */

(function ($, tab, Gofast, Drupal) {
  Gofast.Poll = {
    status: 0, // 1 = initialized, does not mean a poll request is actually running.

    url: null,
    elementId: null,
    timeout: null,
    interval: null,
    delay: null,
    time: null,
    run: function (event, data) {
      if (!Gofast.Poll.status) {
        Gofast.Poll.init(url, elementId, timeout, interval);
      }

      var $poll = $('#' + Gofast.Poll.elementId),
              ajax = Drupal.ajax[Gofast.Poll.elementId],
              pollContext = Gofast.Poll.getContext();

      // No run if no matching context.
      if (!ajax || !Object.keys(pollContext).length) {
        return;
      }

      // Server must be aware of the page's current context to track changes
      // during polling.
      pollContext.__context = Gofast.get('context');
      ajax.submit.context = pollContext;

      // Update settings.
      if (data && data.time >= 0) {
        Gofast.Poll.time = data.time;
        Gofast.Poll.delay = 0;
      }

      // Ensure ajax object holds updated time.
      ajax.options.data.time = Gofast.Poll.time;

      // Delay polling if needed.
      return window.setTimeout(function () {
        // Trigger polling only if the current tab is active.
        if (tab && tab.now()) {
          $poll.trigger('polling');       
        }
      }, Gofast.Poll.delay * 1000, $poll);
    },
    init: function (url, elementId, timeout, interval) {
      Gofast.Poll.url = url || Gofast.get('pollUrl');
      Gofast.Poll.elementId = elementId || Gofast.get('pollElementId');
      Gofast.Poll.timeout = timeout || Gofast.get('pollRequestTimeout');
      Gofast.Poll.interval = interval || Gofast.get('pollInterval');

      Gofast.Poll.delay = Gofast.Poll.interval;
      Gofast.Poll.time = 0;

      var base = Gofast.Poll.elementId,
              $el = $('#' + base),
              el_settings;

      if (Drupal.ajax[base] || !$el.length) {
        Gofast.Poll.status = 1;
        return;
      }

      el_settings = {
        url: Gofast.Poll.url,
        event: 'polling',
        keypress: false,
        selector: '#' + base,
        effect: 'none',
        speed: 'none',
        method: '',
        progress: {
          type: 'throbber',
          message: 'polling...'
        },
        submit: {
          js: true,
          time: Gofast.Poll.time,
        }
      };

      Drupal.ajax[base] = new Drupal.ajax(base, $el.get(0), el_settings);

      // Override the polling ajax object.
      Gofast.apply(Drupal.ajax[base].options, {
        complete: function (xhr, status) {
          // Error handling to prevent falsy alert when requests are
          // interrupted (e.g. by a redirect).
          Drupal.ajax[base].ajaxing = false;
          if (status === 'error' || status === 'parsererror') {
            window.console && window.console.error(Drupal.ajaxError(xhr, Drupal.ajax[base].url));
          }
          if (xhr.status == 200 && status.includes("error")) {
            Gofast.toast(Drupal.t("An error occurred while refreshing the content of the page. Please refresh the page.", {}, {context: "gofast"}), "warning");
          }
          Drupal.attachBehaviors();
          // Remove poll xhr from the pool.

          //check session to WF component ( if any )
          if(typeof Drupal.gofast_workflows != "undefined"){
                Drupal.gofast_workflows.ceo_vision_js_check_login();
            }

          delete Gofast.xhrPool.pollingRequest;
        },
        // Add the xhr object to the pool.
        beforeSend: function (xmlhttprequest, options) {
          Drupal.ajax[base].ajaxing = true;

          Gofast.xhrPool = Gofast.xhrPool || {}; // ou $.xhrPool ?
          Gofast.xhrPool.pollingRequest = xmlhttprequest;

          return Drupal.ajax[base].beforeSend(xmlhttprequest, options);
        }
      });

      Gofast.Poll.status = 1;
    },
    /**
     * Update poll settings / init poll objects if no status.
     */
    update: function (time, url, elementId, timeout, interval) {
      if (!Gofast.Poll.status) {
        Gofast.Poll.init(url, elementId, timeout, interval);
        return;
      }

      Gofast.Poll.url = url || Gofast.get('pollUrl');
      Gofast.Poll.elementId = elementId || Gofast.get('pollElementId');
      Gofast.Poll.timeout = timeout || Gofast.get('pollRequestTimeout');
      Gofast.Poll.interval = interval || Gofast.get('pollInterval');

      Gofast.Poll.delay = Gofast.Poll.interval;
      Gofast.Poll.time = time || 0;

      // Context is updated by reference in the poll ajax object.
    },
    abort: function () {
      if (Gofast.xhrPool && Gofast.xhrPool.pollingRequest) {
        Gofast.xhrPool.pollingRequest.abort();
      }
    },
    /**
     * Returns poll contexts matching the current context.
     */
    getContext: function () {
      var polls = Gofast.get('polls'),
              context = {},
              sel;

      if (Gofast.get('dev_mode')) {
        //console.log(polls, context);
      }

      for (var key in polls) {
        if (!Gofast.contextMatch(polls[key].context))
          continue;
        sel = polls[key].selector;
        if (!sel || Gofast.selectorValidate(sel) && $(sel).length) {
          context[polls[key]['pollID']] = true;
        }
      }

      return context;
    }
  };


  /**
   * Poll behavior.
   */
  $(document).ready(function () {
    if (!Gofast.Poll.status && !Gofast.ajaxingNav) {
      // Init default once to make sure both the polling ajax object and the
      // DOM object are created before the first poll run.
      Gofast.Poll.init();
    }

    $('#' + Gofast.Poll.elementId).once('poll', function () {
      var $poll = $(this);

      //
      Gofast.Poll.run();
      $poll.on('pollEnd', Gofast.Poll.run);
   
      // Polling may interrupt itself when the tab goes idle. In this case we
      // need to trigger the event when the tab wakes up.
      tab.on('wakeup', function () {
        var base = Gofast.Poll.elementId;
        if (base && Drupal.ajax[base] && Drupal.ajax[base].ajaxing === false) {
          $poll.trigger('polling');
        }
    });
    });

    $(this).on('ajax-navigate', function () {
      // When navigating in ajax, cancel the current polling request if any.
      Gofast.Poll.abort();
    });

    $(this).on('ajax-nav-success', function () {
      Gofast.Poll.update();
      Gofast.Poll.run();
    });

  });

})(jQuery, ifvisible, Gofast, Drupal);
