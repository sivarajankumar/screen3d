#!/bin/sh

$SBS_HOME/sbs.sh build Screen/Utils -d
$SBS_HOME/sbs.sh build Screen/Math -d
$SBS_HOME/sbs.sh build Screen/Memory -b -d
#$SBS_HOME/sbs.sh build Screen/Fields -d
#$SBS_HOME/sbs.sh build Screen/XML -d
$SBS_HOME/sbs.sh build Screen/Main -b -d
$SBS_HOME/sbs.sh build Screen/OpenGL -i sbs-linux.xml -d
$SBS_HOME/sbs.sh build Demo/SFML -d
