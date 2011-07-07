#!/bin/sh

$SBS_HOME/sbs.sh clean Screen/Utils
$SBS_HOME/sbs.sh clean Screen/Math
$SBS_HOME/sbs.sh clean Screen/Memory -b
$SBS_HOME/sbs.sh clean Screen/Fields
$SBS_HOME/sbs.sh clean Screen/XML
$SBS_HOME/sbs.sh clean Screen/Main -i sbs-linux.xml -b
$SBS_HOME/sbs.sh clean Screen/OpenGL -i sbs-linux.xml
$SBS_HOME/sbs.sh clean Demo/SFML

