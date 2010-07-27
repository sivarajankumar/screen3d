#!/bin/sh

$SBS_ROOT/sbs.sh Screen/Utils generate -e linux -e screen-linux -e thoratou-linux -d
$SBS_ROOT/sbs.sh Screen/Math generate -e linux -e screen-linux -e thoratou-linux -d
$SBS_ROOT/sbs.sh Screen/Memory generate -e linux -e screen-linux -e thoratou-linux -d -b
$SBS_ROOT/sbs.sh Screen/Fields generate -e linux -e screen-linux -e thoratou-linux -d
$SBS_ROOT/sbs.sh Screen/XML generate -e linux -e screen-linux -e thoratou-linux -d
$SBS_ROOT/sbs.sh Screen/Main generate -i sbs-linux.xml -e linux -e screen-linux -e thoratou-linux -d -b
$SBS_ROOT/sbs.sh Screen/OpenGL generate -i sbs-linux.xml -e linux -e screen-linux -e thoratou-linux -d
$SBS_ROOT/sbs.sh Demo/SFML generate -e linux -e screen-linux -e thoratou-linux -d

cd Screen/Utils
make -j 4 all
cd ../..

cd Screen/Math
make -j 4 all
cd ../..

cd Screen/Memory
make -j 4 all
cd ../..

cd Screen/Memory/test
make -j 4 all
cd ../../..

cd Screen/Fields
make -j 4 all
cd ../..

cd Screen/XML
make -j 4 all
cd ../..

cd Screen/Main
make -j 4 all
cd ../..

cd Screen/Main/test
make -j 4 all
cd ../../..

cd Screen/OpenGL
make -j 4 all
cd ../..

cd Demo/SFML
make -j 4 all
cd ../..

ln -s ~/.sbs/Screen/OpenGL/0.1.0/lib/Linux/Debug/libScreenOpenGL.so ~/.sbs/Screen/Main/0.1.0/lib/Linux/Debug/ScreenOpenGL.so 
