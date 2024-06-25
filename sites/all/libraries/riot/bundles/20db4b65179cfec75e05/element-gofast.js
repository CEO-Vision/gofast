if (!window.elementGofastInterval) {

  // add a backdrop to prevent all user interactions while the jitsi widget is loading
  const addBackdrop = function() {
    // backdrop element
    const backdrop = document.createElement('div');
    backdrop.style.position = 'fixed';
    backdrop.style.inset = '0';
    backdrop.style.width = '100%';
    backdrop.style.height = '100%';
    backdrop.style.backgroundColor = 'rgba(0,0,0,0.5)';
    backdrop.style.zIndex = '100000'; // ensure it's on top of everything
    backdrop.id = 'backdrop'; // for easy removal
    backdrop.onclick = function(e) {
      e.stopPropagation(); // prevent clicks from reaching below
    };
    // spinner element
    const spinner = document.createElement('div');
    spinner.className = 'mx_Spinner';
    spinner.style.position = 'absolute';
    spinner.style.top = '50%';
    spinner.style.left = '50%';
    spinner.style.width = '50px';
    spinner.style.height = '50px';
    // spinner icon
    const spinnerIcon = document.createElement('div');
    spinnerIcon.className = 'mx_Spinner_icon';
    // insert into DOM
    spinner.appendChild(spinnerIcon);
    backdrop.appendChild(spinner);
    document.body.appendChild(backdrop);
  }

  // remove the backdrop
  const removeBackdrop = function() {
    const backdrop = document.getElementById('backdrop');
    if (backdrop) {
      backdrop.parentNode.removeChild(backdrop);
    }
  }

  // trigger a regular click event on a call button
  // we don't remove entirely our callback in case the widget is destroyed while the room is open
  const proceedToClick = function(callButton) {
    callButton.removeEventListener('click', callButtonCallback);
    callButton.click();
    callButton.addEventListener('click', callButtonCallback);
  }

  // force load jitsi widget and once it's loaded trigger back the original click event
  const forceLoadJitsiWidget = function(callButton) {
    // this can take a bit of time so we prevent all user interactions in the meantime to avoid unpredictable outcomes
    addBackdrop(); 
    const roomSummaryButton = document.querySelector(".mx_RightPanel_roomSummaryButton");
    // 1. if the pin button is not in the DOM, this means the room card holding it is not open: open it
    if (!document.querySelector(".mx_RoomSummaryCard_app_pinToggle")) {
      roomSummaryButton.click();
    }
    // 2. if there is no pin button _at all_, this means we have to click on the call button _twice_ to create one
    if (!document.querySelector(".mx_RoomSummaryCard_app_pinToggle")) {
      proceedToClick(callButton);
      proceedToClick(callButton);
    }
    // 3. pin widget
    document.querySelector(".mx_RoomSummaryCard_app_pinToggle")?.click();

    // 4. close room options
    roomSummaryButton.click();

    // finally we wait for the widget to appear before removing the backdrop and triggering back the normal behavior
    const waitForWidgetInterval = setInterval(function() {
      const jitsiIframeReady = callButton.classList.contains("jitsi-gofast-processed");
      if (!jitsiIframeReady) {
        return;
      }
      clearInterval(waitForWidgetInterval)
      removeBackdrop();
      proceedToClick(callButton);
  }, 250);
  }

  // click event to load jitsi widget if it's missing
  const callButtonCallback = function (e) {
    e.preventDefault();
    e.stopPropagation();
    e.stopImmediatePropagation();
    const callButton = e.currentTarget;

    // if jitsi iframe is already loaded, everything below becomes pointless, so we return early
    const jitsiIframe = document.querySelector(".mx_AppTileBody iframe");
    if (jitsiIframe) {
      proceedToClick(callButton);
      return;
    }
    // parts of element's state is available in the global scope, so we use it to get the members count to know if this room uses jitsi for calls
    const viewedRoomId = matrixChat.state.currentRoomId;
    const members =
      mxMatrixClientPeg.matrixClient._store.rooms[
        viewedRoomId
      ].currentState.getMembers();
    let activeMembersCount = 0;
    for (const member of members) {
      if (member.membership == "join") {
        activeMembersCount++;
      }
    }
    const hasEnoughActiveMembersToHaveJitsi = activeMembersCount > 2;
    // one-to-one room: don't trigger anything
    if (!hasEnoughActiveMembersToHaveJitsi) {
      proceedToClick(callButton);
      return;
    }
    // tab is not visible hence it's not active, so we're in a multitab session
    // we return early to avoid creating multiple widgets
    if (document.hidden) {
      proceedToClick(callButton);
      return;
    }
    // at this point, we need to force load the jitsi widget iframe, to make informations such as the room conference id available
    // 1. check if widget is pinned
    const widgetsButton = document.querySelector(".mx_LegacyRoomHeader_appsButton");
    if (widgetsButton) {
      // 2. if widget is already pinned: load widget iframe
      callButton.click();
    } else {
      // 3. if widget is NOT already pinned: force-pin widget, which will also trigger an iframe load
      forceLoadJitsiWidget(callButton);
    }
  };

  //  attach click event to load jitsi widget if it's missing
  window.elementGofastInterval = setInterval(() => {
    const videoCallButton = document.querySelector(
      ".mx_LegacyRoomHeader_videoCallButton:not(.gofast-processed)"
    );
    if (!videoCallButton) {
      return;
    }

    videoCallButton.classList.add("gofast-processed");
    videoCallButton.addEventListener("click", callButtonCallback);
    // attach to audio button as well
    const voiceCallButton = document.querySelector(".mx_LegacyRoomHeader_voiceCallButton");
    voiceCallButton.addEventListener("click", callButtonCallback);
  }, 250);
}
