> Note: This repo is currently a work in progress, when something stable is ready, we'll take down this note.

# usdview-native
Workalike for usdview for those who want to avoid Qt and Python

[![Build Status](https://travis-ci.com/jacques-gasselin/usdview-native.svg?branch=master)](https://travis-ci.com/jacques-gasselin/usdview-native)

Installing Dependencies
=======================

macOS
-----

> Note: The library dependencies are build for High Sierra in the macos/deps folder already. You do not need to run the script if you want to run the application, only if you intend to change the USD version or the OS.

Run the dependecies build script in the root folder

*sh macos_build_deps.sh*

It will download Cmake and USD and build them in the macos/deps location
that does not affect the wider system.
