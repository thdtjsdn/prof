# NodeProfiling

Profile, debug, optimize and understand node applications. With the help of native bindings to the [v8-profiler](http://code.google.com/p/v8/wiki/V8Profiler) you're able to take snapshosts of the heap, profile CPU usage and debug your code with breakpoints while running.

The debugger is there to inspect taken snapshots visually, or interact with your remote processes in a convenient way. It's built upon the [WebInspector](http://trac.webkit.org/wiki/WebInspector) front-end that is shipped with most [WebKit](http://www.webkit.org/) variants.

This project is mainly inspired by three modules:

[node-inspector](https://github.com/dannycoates/node-inspector)
[v8-profiler](https://github.com/dannycoates/v8-profiler)
[node-heap-dump](https://github.com/davepacheco/node-heap-dump)

## API

### Profiler

### Debugger

## Development

### Setup

To build the [node addon](http://nodejs.org/docs/latest/api/addons.html) and install dependencies run:

    make

### Testing

Tests are written with [Vows](http://vowsjs.org/) and are limited to the node code. To run all tests:

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

1. [Fork](http://help.github.com/forking/) NodeProfiling
2. Create a topic branch `git checkout -b my_branch`
3. Push to your branch `git push origin my_branch`
4. Create a [Pull Request](http://help.github.com/pull-requests/) from your branch

**git-flow**

1. [Fork](http://help.github.com/forking/) NodeProfiling
2. Create a feature `git flow feature start my-feature`
3. Publish your featue `git flow feature publish my-feature`
4. Create a [Pull Request](http://help.github.com/pull-requests/) from your branch

## Meta

* Code: `git clone git@github.com:goldjunge/node-profiling.git`
* Home: https://github.com/goldjunge/node-profiling
* Docs: https://github.com/goldjunge/node-profiling
* Bugs: https://github.com/goldjunge/node-profiling/issues

This project uses [Semantic Versioning](http://semver.org) & [git flow](http://nvie.com/posts/a-successful-git-branching-model/) with the help of [git-flow](https://github.com/nvie/gitflow)
