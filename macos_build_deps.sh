#!/bin/sh
DEPS_DIR=/tmp/usdview-native/deps
mkdir -p $DEPS_DIR/src
pushd $DEPS_DIR/src

#--- CMake ---
echo 'Fetching CMake'
curl -o cmake-3.8.0.tar.gz -L -C - https://cmake.org/files/v3.8/cmake-3.8.0.tar.gz
tar zxf cmake-3.8.0.tar.gz
pushd cmake-3.8.0
./configure --prefix=$DEPS_DIR
make -j8
make install
popd #cmake-3.8.0

#--- Add deps to the path ---
# make build_usd.py able to find Cmake
export PATH=$PATH:$DEPS_DIR/bin

#--- USD ---
echo 'Fetching USD'
curl -o usd-18.09.zip -L -C - https://github.com/PixarAnimationStudios/USD/archive/v18.09.zip
unzip -uq usd-18.09.zip
pushd USD-18.09/build_scripts
python build_usd.py --no-python --no-openimageio --build-monolithic $DEPS_DIR
popd #usd

popd #src
