# Prof [![Build Status](https://secure.travis-ci.org/goldjunge/prof.png)](http://travis-ci.org/goldjunge/prof)

Profile, debug, optimize and understand node applications. With the help of native bindings to the [v8-profiler](http://code.google.com/p/v8/wiki/V8Profiler) you're able to take snapshosts of the heap, profile CPU usage and debug your code with breakpoints while running.

The debugger is there to inspect taken snapshots visually, or interact with your remote processes in a convenient way. It's built upon the [WebInspector](http://trac.webkit.org/wiki/WebInspector) front-end that is shipped with most [WebKit](http://www.webkit.org/) variants.

This project is mainly inspired by three modules:

* [node-inspector](https://github.com/dannycoates/node-inspector)
* [v8-profiler](https://github.com/dannycoates/v8-profiler)
* [node-heap-dump](https://github.com/davepacheco/node-heap-dump)

## API

### Profiler

Heap profiling is exposed via the `heap` object and enables you to take snapshots and manage the snapshosts. The `heap` exposes the interface implemented in the v8 [HeapProfiler](https://github.com/v8/v8/blob/master/src/heap-profiler.cc).

Structure of a snapshot:

``` javascript
{
  uid: <NUMBER>, // internally generated id
  root: <NODE>,
  title: <STRING>, // empty if not passed as argument to takeSnapshot()
  type: <STRING>, // "Full" is the default and only option
  nodes: <STRING>, // amount of nodes
  delete: [Function: delete],
  getNode: [Function: getNode],
  getNodeById: [Function: getNodeById],
  serialize: [Function: serialize]
}
```

Take a snapshot of the current process:

``` javascript
var heap = require('profiler').heap;

var snapshot = heap.takeSnapshot('a-meaningful-name');

```

Serialize a snapshot as JSON into a file:

``` javascript
snapshot.serialize('/tmp/snapshot.json');
```

Delete one snapshot:

``` javascript
snapshot.delete();
```

Delete all snapshots:

``` javascript
heap.deleteAllSnapshots();
```

Get the current `count` of snapshots:

``` javascript
heap.snapshotCount();
```

Get/Find a snapshot:

``` javascript
// get by index
heap.getSnapshot(0);

// find by UID
heap.findSnapshot(1);
```

A snapshot consists of many nodes, starting with the `root` node which is exposed as top-level property. The structure of a node:

``` javascript
{
  id: <NUMBER>, // internal ID
  ptr: <NUMBER>, // pointer address
  type: <STRING>, // type of the node like: 'Object', 'String', 'Array'...
  dominatorNode: <NODE>, // This is the node that participates in every path from the snapshot root to the current node
  name: '', // Depending on node's type this can be the name of the constructor (for objects), the name of the function (for closures), string value, or an empty string (for compiled code)
  approximateRetainedSize: <NUMBER>, // imprecise guess on the retainedsize of the node
  retainersCount: <NUMBER>, // Retainer nodes count of the node
  childrenCount: <NUMBER>, // count of children
  size: <NUMBER>, // node's own size in bytes
  getChild: [Function: getChild], // Retrieves a child by index
  getRetainer: [Function: getRetainer], // Returns a retainer by index
  getRetainedSize: [Function: getRetainedSize] // That is, self + sizes of the objects that are reachable only from this object. In other words, the size of memory that will be reclaimed having this node collected. This call returns an accurate number of approximateRetainedSize
}
```

Get a node by it's ID:

``` javascript
snapshot.getChild(1); // will return the root element
```
### Debugger

To start the interactive debugger call:

    debugger

Per default the debugger will start on [http://localhost:1337/debug](http://localhost:1337/debug).

Overwrite the default port and host with:

    debugger --host=0.0.0.0 --port=9000

You can preload heap snapshots for inspection with a comma-separated list:

    debugger --snapshots=snapshot1.json,snapshot2.json

## Caveats

Binding functions like `getSnapshot()` which take a variable `index` or `id` causing a segmentation fault when called with an invalid reference.

This module is early alpha. Many of the documented interfaces aren't even implemented yet as this README.md is developed with principle of [RDD](http://tom.preston-werner.com/2010/08/23/readme-driven-development.html).

## Development

### Setup

To build the [node addon](http://nodejs.org/docs/latest/api/addons.html) and install dependencies run:

    make

### Testing

Tests are written with [Vows](http://vowsjs.org/) and are limited to the node code. CI is covered by [travis-ci](http://about.travis-ci.org/) and the current status is visible [here](http://travis-ci.org/goldjunge/prof).

To run all tests:

    make test

### Branching

This repository is organized and maintained with the help of [gitflow](https://github.com/nvie/gitflow). Developers are encouraged to use it when working with this repository.

We use the following naming convention for branches:

* `develop` (during development)
* `master` (will be or has been released)
* `feature/<name>` (feature branches)
* ` ` (empty version prefix)

During development, you should work in feature branches instead of committing to `master` directly. Tell gitflow that you want to start working on a feature and it will do the work for you (like creating a branch prefixed with `feature/`):

    git flow feature start <FEATURE_NAME>

The work in a feature branch should be kept close to the original problem. Tell gitflow that a feature is finished and it will merge it into `master` and push it to the upstream repository:

    git flow feature finish <FEATURE_NAME>

Even before a feature is finished, you might want to make your branch available to other developers. You can do that by publishing it, which will push it to the upstream repository:

    git flow feature publish <FEATURE_NAME>

To track a feature that is located in the upstream repository and not yet present locally, invoke the following command:

    git flow feature track <FEATURE_NAME>

Changes that should go into production should come from the up-to-date master branch. Enter the "release to production" phase by running:

    git flow release start <VERSION_NUMBER>

In this phase, only meta information should be touched, like bumping the version and update the history. Finish the release phase with:

    git flow release finish <VERSION_NUMBER>

### Versioning

This project is versioned with the help of the [Semantic Versioning Specification](http://semver.org/) using `0.0.0` as the initial version. Please make sure you have read the guidelines before increasing a version number either for a release or a hotfix.

## Contributing

**normal**

1. [Fork](http://help.github.com/forking/) Prof
2. Create a topic branch `git checkout -b my_branch`
3. Push to your branch `git push origin my_branch`
4. Create a [Pull Request](http://help.github.com/pull-requests/) from your branch

**git-flow**

1. [Fork](http://help.github.com/forking/) Prof
2. Create a feature `git flow feature start my-feature`
3. Publish your featue `git flow feature publish my-feature`
4. Create a [Pull Request](http://help.github.com/pull-requests/) from your branch

## Meta

* Code: `git clone git@github.com:goldjunge/prof.git`
* Home: https://github.com/goldjunge/prof
* Docs: https://github.com/goldjunge/prof
* Bugs: https://github.com/goldjunge/prof/issues

This project uses [Semantic Versioning](http://semver.org) & [git flow](http://nvie.com/posts/a-successful-git-branching-model/) with the help of [git-flow](https://github.com/nvie/gitflow)

## Todos

* implement remote repl for snapshot interaction
* implement snapshot header handling
* implement remote connection to node process in debug mode
* implement cpu profiling
* implement interactive console
* implement breakpoints
* generate docs (man?)
* generate site
