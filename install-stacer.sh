#!/bin/bash

SELF_CALLDIR="$(pwd)"
SELF_BUILDIR="$SELF_CALLDIR/staged"

rm -R -f ./staged
mkdir -p "$SELF_BUILDIR"
cd "$SELF_BUILDIR"

git clone --recursive --depth=1 https://github.com/emaballarin/Stacer.git

cd Stacer

./build-aux/build-sddp.sh

mkdir build
cd build

cmake .. -DCMAKE_BUILD_TYPE="Release"
make -j8

sudo make install
sudo make install

cd "$SELF_CALLDIR"
rm -R -f ./staged
