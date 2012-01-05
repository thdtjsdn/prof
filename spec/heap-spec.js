var vows    = require('vows');
var assert  = require('assert');
var heap    = require('../lib/heap');

var suite   = vows.describe('HEAP');

suite.addBatch({
  'Snapshot taken': {
    topic: function() {
      return heap.takeSnapshot('test');
    },
    'exposes *nodes*': function(snapshot) {
      assert.isNumber(snapshot.nodes);
    },
    'exposes *root*': function(snapshot) {
      assert.isObject(snapshot.root);
    },
    'exposes *title*': function(snapshot) {
      assert.equal(snapshot.title, 'test');
    },
    'exposes *type*': function(snapshot) {
      assert.equal(snapshot.type, 'Full');
    },
    'exposes *uid*': function(snapshot) {
      assert.equal(snapshot.uid, 1);
    },
    'increases *count*': function() {
      assert.equal(heap.snapshotCount(), 1);
    },
    teardown: function(snapshot) {
      snapshot.delete();

      assert.equal(heap.snapshotCount(), 0);
    }
  }
});

suite.addBatch({
  'With Snapshot': {
    topic: function() {
      return heap.takeSnapshot('with');
    },
    'exposes *count*': function(snapshot) {
      assert.equal(heap.snapshotCount(), 1);
    },
    'retrieves snapshot via *index*': function(snapshot) {
      assert.equal(heap.getSnapshot(0)['title'], snapshot['title']);
    },
    'finds snapshot via *uid*': function(snapshot) {
      assert.equal(heap.findSnapshot(snapshot['uid'])['title'], snapshot['title']);
    },
    'deletes all *snapshots*': function(snapshot) {
      heap.deleteAllSnapshots();

      assert.equal(heap.snapshotCount(), 0);
    }
  }
});

suite.export(module);

// var snapshot  = profiler.takeSnapshot('test');
// 
// assert.equal(1, profiler.snapshotCount(), 'Shows correct amount of snapshots.');
// assert.equal(profiler.findSnapshot(snapshot['uid'])['title'], snapshot['title'], 'Finds snapshot and retrieves it')
// assert.equal(profiler.getSnapshot(1)['title'], snapshot['title'], 'Retrieves snapshots');
// 
// profiler.deleteAllSnapshots();
// assert.equal(0, profiler.snapshotCount(), 'Deletes all snapshots');
