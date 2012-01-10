WebInspector.loaded = function() {
  var socket = io.connect('http://' + window.location.host + '/');

  socket.on('error', console.error);
  socket.on('message', function(msg) {
    InspectorBackend.dispatch(msg);
  });
  socket.on('connect', function() {
    InspectorFrontendHost.sendMessageToBackend = WebInspector.socket.send.bind(WebInspector.socket);

    WebInspector.doLoadedDone();
  });

  WebInspector.socket = socket;

  InspectorBackend.loadFromJSONIfNeeded();
};

InspectorFrontendHost.hiddenPanels = function() {
  return 'elements,resources,timeline,network,audits,scripts,console';
};
