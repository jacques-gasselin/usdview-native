> Note: This repo is currently a work in progress, when something stable is ready, we'll take down this note.

# usdview-native
Workalike for usdview for those who want to avoid Qt and Python

[![Build Status](https://travis-ci.com/jacques-gasselin/usdview-native.svg?branch=master)](https://travis-ci.com/jacques-gasselin/usdview-native)

Developer Setup
=======================

macOS
-----

> Note: The library dependencies are build for High Sierra in the macos/deps folder already. You do not need to run the script if you want to run the application, only if you intend to change the USD version or the OS.

Run the developer setup script (configure git, etc)
```bash
$ .buildScripts/dev-setup
```

Build the local dependencies (USD, Boost, etc)
```bash
$ .buildScripts/build-mac-deps
```
