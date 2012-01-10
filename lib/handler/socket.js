var path      = require('path');
var protocol  = require('./socket/protocol');
var store     = require('./socket/snapshot-store');

exports.handler = handler;

function handler(config) {
  var snapshots = store.createStore();
  
  config.snapshots.split(',').forEach(function(s) {
    snapshots.add(s);
  });

  return function(sock) {
    sock.snapshots = snapshots;

    sock.on('message', function(msg) {
      msg = JSON.parse(msg);

      if (protocol.hasOwnProperty(msg.method)) {
        protocol[msg.method].call(sock, msg);
      }
    });
  }
}
