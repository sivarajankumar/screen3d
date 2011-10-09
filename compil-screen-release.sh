#!/bin/sh

$SBS_ROOT/sbs.sh build Screen/Utils
$SBS_ROOT/sbs.sh build Screen/Math
$SBS_ROOT/sbs.sh build Screen/Memory -b
#$SBS_ROOT/sbs.sh build Screen/Fields
#$SBS_ROOT/sbs.sh build Screen/XML
$SBS_ROOT/sbs.sh build Screen/Main -b
$SBS_ROOT/sbs.sh build Screen/OpenGL -i sbs-linux.xml
$SBS_ROOT/sbs.sh build Screen/Image/IL
$SBS_ROOT/sbs.sh build Demo/SFML
