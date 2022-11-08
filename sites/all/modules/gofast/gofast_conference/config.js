// Gofast : This is a backup of config.js on the server srv03.ceo-vision.com
/* jshint maxlen:false */

var config = { // eslint-disable-line no-unused-vars
//    configLocation: './config.json', // see ./modules/HttpConfigFetch.js
    hosts: {
        domain: 'srv03.ceo-vision.com',
        //anonymousdomain: 'srv03.ceo-vision.com',
        //authdomain: 'jitsi-meet.example.com',  // defaults to <domain>
        muc: 'conference.srv03.ceo-vision.com', // FIXME: use XEP-0030
        //jirecon: 'jirecon.jitsi-meet.example.com',
        //call_control: 'callcontrol.jitsi-meet.example.com',
        focus: 'focus.srv03.ceo-vision.com', // defaults to 'focus.jitsi-meet.example.com'
    },
//  getroomnode: function (path) { return 'someprefixpossiblybasedonpath'; },
    useStunTurn: true, // use XEP-0215 to fetch STUN and TURN server
//  useIPv6: true, // ipv6 support. use at your own risk
    useNicks: false,
    bosh: '/http-bind', // FIXME: use xep-0156 for that
	//externalConnectUrl: 'https://gofast3.ceo-vision.com/gofast_conference/xmpp/login',
    clientNode: 'http://jitsi.org/jitsimeet', // The name of client node advertised in XEP-0115 'c' stanza
	etherpad_base: 'https://srv03.ceo-vision.com:9001/p/etherpad',
    //focusUserJid: 'focus@auth.jitsi-meet.example.com', // The real JID of focus participant - can be overridden here
    //defaultSipNumber: '', // Default SIP number
    //desktopSharing: 'ext',
    // Desktop sharing method. Can be set to 'ext', 'webrtc' or false to disable.
    //desktopSharingChromeMethod: 'ext',
    // The ID of the jidesha extension for Chrome.
    //desktopSharingChromeExtId: 'diibjkoicjeejcmhdnailmkgecihlobk',
    // The media sources to use when using screen sharing with the Chrome
    // extension.
    //desktopSharingChromeSources: ['screen', 'window'],
    // Required version of Chrome extension
    //desktopSharingChromeMinExtVersion: '0.1',
    
    // The ID of the jidesha extension for Firefox. If null, we assume that no
    // extension is required.
    //desktopSharingFirefoxExtId: null,
    // Whether desktop sharing should be disabled on Firefox.
    //desktopSharingFirefoxDisabled: false,
    // The maximum version of Firefox which requires a jidesha extension.
    // Example: if set to 41, we will require the extension for Firefox versions
    // up to and including 41. On Firefox 42 and higher, we will run without the
    // extension.
    // If set to -1, an extension will be required for all versions of Firefox.
    //desktopSharingFirefoxMaxVersionExtRequired: -1,
    // The URL to the Firefox extension for desktop sharing.
    //desktopSharingFirefoxExtensionURL: null,


    desktopSharing: 'ext', // Desktop sharing method. Can be set to 'ext', 'webrtc' or false to disable.
    chromeExtensionId: 'nondidocaboaehacbpbcofofmongdiio', // Id of desktop streamer Chrome extension
    desktopSharingSources: ['screen', 'window'],
    minChromeExtVersion: '0.1.3', // Required version of Chrome extension
    desktopSharingFirefoxExtId: null,
    desktopSharingFirefoxDisabled: false,
    desktopSharingFirefoxMaxVersionExtRequired: 0,
    desktopSharingFirefoxExtensionURL: null,
    //useRoomAsSharedDocumentName: false,

    enableRtpStats: false, // Enables RTP stats processing


    // Disables ICE/UDP by filtering out local and remote UDP candidates in signalling.
    webrtcIceUdpDisable: false,
    // Disables ICE/TCP by filtering out local and remote TCP candidates in signalling.
    webrtcIceTcpDisable: false,

    openSctp: true, // Toggle to enable/disable SCTP channels
    disableStats: false,
    disableAudioLevels: false,
    channelLastN: -1, // The default value of the channel attribute last-n.
    adaptiveLastN: false,
    //disableAdaptiveSimulcast: false,
    enableRecording: true,
	enableLipSync: true,
    enableWelcomePage: true,
    //enableClosePage: false, // enabling the close page will ignore the welcome
                              // page redirection when call is hangup
    stereo: true,
    isBrand: false,
    //disableSimulcast: false,
	useRtcpMux: true,
    //startBitrate: "800",
    logStats: false, // Enable logging of PeerConnection stats via the focus
    requireDisplayName: true, // Forces the participants that doesn't have display name to enter it when they enter the room.
//    startAudioMuted: 10, // every participant after the Nth will start audio muted
//    startVideoMuted: 10, // every participant after the Nth will start video muted
//    defaultLanguage: "en",
// To enable sending statistics to callstats.io you should provide Applicaiton ID and Secret.
//    callStatsID: "", // Application ID for callstats.io API
//    callStatsSecret: "", // Secret for callstats.io API
    /*noticeMessage: 'Service update is scheduled for 16th March 2015. ' +
    'During that time service will not be available. ' +
    'Apologise for inconvenience.',*/
    disableThirdPartyRequests: false,
    minHDHeight: 540,
    // If true - all users without token will be considered guests and all users
    // with token will be considered non-guests. Only guests will be allowed to
    // edit their profile.
    enableUserRolesBasedOnToken: false
};
