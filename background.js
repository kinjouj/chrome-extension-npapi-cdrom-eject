(function(undefined) {
  chrome.browserAction.onClicked.addListener(function() {
    var plugin = document.getElementById("plugin");
    plugin.eject();
  });
})();
