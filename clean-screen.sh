#!/bin/sh

$SBS_ROOT/sbs.sh Screen/Utils clean -e linux -e screen-linux -e thoratou-linux -d
$SBS_ROOT/sbs.sh Screen/Math clean -e linux -e screen-linux -e thoratou-linux -d
$SBS_ROOT/sbs.sh Screen/Memory clean -e linux -e screen-linux -e thoratou-linux -d -b
$SBS_ROOT/sbs.sh Screen/Fields clean -e linux -e screen-linux -e thoratou-linux -d
$SBS_ROOT/sbs.sh Screen/XML clean -e linux -e screen-linux -e thoratou-linux -d
$SBS_ROOT/sbs.sh Screen/Main clean -i sbs-linux.xml -e linux -e screen-linux -e thoratou-linux -d -b
$SBS_ROOT/sbs.sh Screen/OpenGL clean -i sbs-linux.xml -e linux -e screen-linux -e thoratou-linux -d
$SBS_ROOT/sbs.sh Demo/SFML clean -e linux -e screen-linux -e thoratou-linux -d

