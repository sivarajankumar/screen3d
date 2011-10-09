#!/bin/sh

$SBS_ROOT/sbs.sh build Screen/Utils -d
$SBS_ROOT/sbs.sh build Screen/Math -d
$SBS_ROOT/sbs.sh build Screen/Memory -b -d
#$SBS_ROOT/sbs.sh build Screen/Fields -d
#$SBS_ROOT/sbs.sh build Screen/XML -d
$SBS_ROOT/sbs.sh build Screen/Main -b -d
$SBS_ROOT/sbs.sh build Screen/OpenGL -i sbs-linux.xml -d
$SBS_ROOT/sbs.sh build Screen/Image/IL -d
$SBS_ROOT/sbs.sh build Demo/SFML -d
