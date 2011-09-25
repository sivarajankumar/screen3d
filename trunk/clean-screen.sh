#!/bin/sh

$SBS_ROOT/sbs.sh clean Screen/Utils
$SBS_ROOT/sbs.sh clean Screen/Math
$SBS_ROOT/sbs.sh clean Screen/Memory -b
$SBS_ROOT/sbs.sh clean Screen/Fields
$SBS_ROOT/sbs.sh clean Screen/XML
$SBS_ROOT/sbs.sh clean Screen/Main -i sbs-linux.xml -b
$SBS_ROOT/sbs.sh clean Screen/OpenGL -i sbs-linux.xml
$SBS_ROOT/sbs.sh clean Demo/SFML

