> Note: This repo is currently a work in progress, when something stable is ready, we'll take down this note.

# usdview-native
Workalike for usdview for those who want to avoid Qt and Python

[![Build Status](https://travis-ci.com/jacques-gasselin/usdview-native.svg?branch=master)](https://travis-ci.com/jacques-gasselin/usdview-native)

Developer Setup
=======================

macOS
-----

#### Install Local Dependencies
You will need to install a few dependencies via your preferred method (brew, macports, source)

| Name            | Version | 
| :-------------- | :------ |
| clang-format    |  7.0.0  |
| swiftformat     |  0.35.3 |
| swiftlint       |  0.27.0 |
| cmake           |  3.10.0 |


<details>
<summary>Brew Example</summary>
<p>

```bash
$ brew install clang-format
$ brew install swiftformat
$ brew install swiftlint
$ brew install cmake
```

</p>
</details>

<details>
<summary>Source Example</summary>
<p>
```bash
#--- CMake ---
$ curl -o cmake-3.10.0.tar.gz -L -C - https://cmake.org/files/v3.10/cmake-3.10.0.tar.gz
$ tar zxf cmake-3.10.0.tar.gz
$ pushd cmake-3.10.0
$ ./configure --prefix=$DEPS_DIR
$ make -j8
$ make install
$ popd
```
</p>
</details>

#### Setup Developer Environment
You will need to run a script which sets of various
git hooks. These run before commits to ensure code is 
linted, formatted and runs any other lightweight checks
before the code gets to the CI stage.

```bash
$ .buildScripts/dev-setup
```

#### Build Embedded C Libraries
You will need to run a script which build [USD](https://github.com/PixarAnimationStudios/USD)
and its necessary dependencies. This should be a one time cost, only needing to be updated 
when we change USD versions (once or twice per year, max).

```bash
$ .buildScripts/build-mac-deps
```

#### Build Application
You will need to build the application itself, this can be done either through XCode or via
the command line (which just invokes xcodebuild).

```bash
$ .buildScripts/build
```
