> Note: This repo is currently a work in progress, when something stable is ready, we'll take down this note.

# usdview-native
Workalike for usdview for those who want to avoid Qt and Python

[![Build Status](https://travis-ci.com/jacques-gasselin/usdview-native.svg?branch=master)](https://travis-ci.com/jacques-gasselin/usdview-native)

Developer Setup
=======================

macOS
-----

Run the developer setup script (configure git, etc)
```bash
$ .buildScripts/dev-setup
```

Build the local dependencies (USD, Boost, etc)
```bash
$ .buildScripts/build-mac-deps
```

Build the application
```bash
$ .buildScripts/build
```
