// elements supposed to trigger the room in an iframe
const voiceCallButton = window.parent.document.querySelector(
  ".mx_LegacyRoomHeader_voiceCallButton"
);
const videoCallButton = window.parent.document.querySelector(
  ".mx_LegacyRoomHeader_videoCallButton"
);

// utility to build the jitsi meet src from the widget src
const getIframeSrc = () => {
  const providedSrc =
    "https://" +
    decodeURIComponent(location.hash.replace("#conferenceDomain=", ""));
  const providedParams = new URLSearchParams(providedSrc);
  // get all needed informations
  const conferenceId = providedParams.get("conferenceId");
  const language = providedParams.get("language");
  const roomName = encodeURIComponent(providedParams.get("roomName"));
  const userDisplayName = encodeURIComponent(providedParams.get("displayName"));
  const userEmail = encodeURIComponent(
    providedParams.get("userId").replace("@", "").replace(":", "@")
  );
  // rebuild the iframe src
  let targetUrl = providedSrc.split("&")[0]; // at this point we have {{COMM_DOMAIN}}/jitsi-meet
  targetUrl += "/" + conferenceId; // finish building the iframe URL
  targetUrl += "?lang=" + language; // build iframe query params
  // build iframe hash (including injected configuration)
  let targetHash =
    "#jitsi_meet_external_api_id=0&config.subject=%22{{ROOM_NAME}}%22&config.startAudioOnly=false&config.startWithAudioMuted=false&config.startWithVideoMuted=false&config.apiLogLevels=%5B%22warn%22%2C%22error%22%5D&interfaceConfig.SHOW_JITSI_WATERMARK=false&interfaceConfig.SHOW_WATERMARK_FOR_GUESTS=false&interfaceConfig.MAIN_TOOLBAR_BUTTONS=%5B%5D&interfaceConfig.VIDEO_LAYOUT_FIT=%22height%22&devices.audioInput=undefined&devices.videoInput=undefined&userInfo.displayName=%22{{USER_DISPLAY_NAME}}%22&userInfo.email=%22{{USER_EMAIL}}%22&appData.localStorageContent=null"
      .replace("{{ROOM_NAME}}", roomName)
      .replace("{{USER_DISPLAY_NAME}}", userDisplayName)
      .replace("{{USER_EMAIL}}", userEmail);
  targetUrl += targetHash;
  return targetUrl;
};

// callback to open jitsi meet in a new tab
const buttonCallback = (e) => {
  e.stopPropagation();
  e.stopImmediatePropagation();
  const iframeSrc = getIframeSrc();
  const link = window.parent.parent.document.createElement("a");
  link.href = iframeSrc;
  link.target = "_blank";
  link.click();
  link.remove();
};

// attach callback to relevant buttons
for (const element of [voiceCallButton, videoCallButton]) {
  if (!element) {
    continue;
  }
  element.style.cursor = "pointer"; // avoid showing a not-allowed cursor
  element.addEventListener("mouseover", (e) => e.stopImmediatePropagation()); // disable misleading tooltip
  element.addEventListener("click", buttonCallback);
  element.classList.add("jitsi-gofast-processed");
}
