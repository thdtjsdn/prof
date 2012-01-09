var fs    = require('fs');
var path  = require('path');

exports.handler = handler;

var snapshots;

function handler(config) {
  snapshots = prepareSnapshots(config.snapshots.split(','));

  return function(sock) {
    sock.on('message', function(msg) {
      msg = JSON.parse(msg);

      if (protocol.hasOwnProperty(msg.method)) {
        protocol[msg.method].call(sock, msg);
      }
    });
  }
}

function prepareSnapshots(snapshots) {
  var uid = 1;

  return snapshots.map(function(d) {
    var location = path.normalize(d);
    var title = path.basename(d, path.extname(d));

    return { location: location, uid: uid++, title: d };
  });
}

var protocol = {};
protocol['Debugger.causesRecompilation'] = resultFalse;
protocol['Debugger.supportsNativeBreakpoints'] = resultFalse;
protocol['Profiler.causesRecompilation'] = resultFalse;
protocol['Profiler.getProfile'] = function(msg) {
  var chunk = {
    method: 'Profiler.addHeapSnapshotChunk',
    params: {
      uid: 1,
      chunk: fs.readFileSync('./snapshot.json', 'utf8')
    }
  };
  var finish = {
    method: 'Profiler.finishHeapSnapshot',
    params: {
      uid: 1
    }
  };

  this.send(JSON.stringify(chunk));
  this.send(JSON.stringify(finish));
};
protocol['Profiler.getProfileHeaders'] = function(msg) {
  var headers = snapshots.map(function(s) {
    return { title: s.title, uid: s.uid, typeId: 'HEAP' };
  });

  msg.result = {
    headers: headers
  }

  this.send(JSON.stringify(msg));
};
protocol['Profiler.hasHeapProfiler'] = resultTrue;
protocol['Profiler.isSampling'] = resultFalse;
protocol['Profiler.takeHeapSnapshot'] = function(msg) {
  var header = {
    method: 'Profiler.addProfileHeader',
    params: {
      header: {
        title: '2',
        uid: 2,
        typeId: 'HEAP'
      }
    }
  };
  var progress = {
    method: 'Profiler.reportHeapSnapshotProgress',
    params: {
      done: 0,
      total: 10
    }
  };

  var inter = setInterval(function() {
    progress.params.done += 1;

    this.send(JSON.stringify(progress));

    if (progress.params.done === progress.params.total) {
      clearInterval(inter);
      this.send(JSON.stringify(header));
    }
  }, 100);

};

function resultFalse(msg) {
  msg.result = { result: false };

  this.send(JSON.stringify(msg));
}

function resultTrue(msg) {
  msg.result = { result: true };

  this.send(JSON.stringify(msg));
}
