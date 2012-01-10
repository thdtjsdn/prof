var path      = require('path');
var protocol  = require('./socket/protocol');

exports.handler = handler;

function handler(config) {
  var snapshots = prepareSnapshots(config.snapshots.split(','));

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

function prepareSnapshots(snapshots) {
  var ret = [];
  var uid = 1;

  snapshots.forEach(function(s) {
    var p = path.normalize(s);

    if (path.existsSync(p)) {
      var title = path.basename(p, path.extname(p));

      ret.push({ location: p, uid: uid++, title: title });
    }
  });

  return ret;
}
