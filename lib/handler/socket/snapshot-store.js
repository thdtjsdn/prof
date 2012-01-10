var path = require('path');

exports.createStore   = createStore;
exports.SnapshotStore = SnapshotStore;

function SnapshotStore() {
  this._snapshots = [];
  this._uid = 1;
}

SnapshotStore.prototype.add = function(location) {
  var p = path.normalize(location);

  if (path.existsSync(p)) {
    var title = path.basename(p, path.extname(p));

    this._snapshots.push({ location: p, uid: this._uid++, title: title });
  }
};

SnapshotStore.prototype.find = function(uid) {
  return this._snapshots.filter(function(s) { return s.uid === uid; }).pop()
};

SnapshotStore.prototype.map = function(cb) {
  return this._snapshots.map(cb);
}

function createStore(config) {
  return new SnapshotStore(config);
};
