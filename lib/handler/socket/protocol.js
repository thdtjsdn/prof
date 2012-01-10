var fs = require('fs');

exports['Debugger.causesRecompilation'] = resultFalse;
exports['Debugger.supportsNativeBreakpoints'] = resultFalse;
exports['Profiler.causesRecompilation'] = resultFalse;
exports['Profiler.getProfile'] = getProfile;
exports['Profiler.getProfileHeaders'] = getProfileHeaders;
exports['Profiler.hasHeapProfiler'] = resultTrue;
exports['Profiler.isSampling'] = resultFalse;
exports['Profiler.takeHeapSnapshot'] = resultFalse;

function getProfile(msg) {
  var that = this;
  var s = this.snapshots.find(msg.params.uid);

  fs.createReadStream(s.location, { encoding: 'utf8' })
    .on('error', function(err) {
      throw err;
    })
    .on('data', function(chunk) {
      var event = {
        method: 'Profiler.addHeapSnapshotChunk',
        params: {
          uid: s.uid,
          chunk: chunk
        }
      };

      that.send(JSON.stringify(event));
    })
    .on('end', function() {
      var event = {
        method: 'Profiler.finishHeapSnapshot',
        params: {
          uid: s.uid
        }
      };

      that.send(JSON.stringify(event));
    });
}

function getProfileHeaders(msg) {
  var headers = this.snapshots.map(function(s) {
    return { title: s.title, uid: s.uid, typeId: 'HEAP' };
  });

  msg.result = {
    headers: headers
  }

  this.send(JSON.stringify(msg));
}

function resultFalse(msg) {
  msg.result = { result: false };

  this.send(JSON.stringify(msg));
}

function resultTrue(msg) {
  msg.result = { result: true };

  this.send(JSON.stringify(msg));
}
