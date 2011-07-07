#!/bin/sh

$SBS_HOME/sbs.sh build Screen/Utils
$SBS_HOME/sbs.sh build Screen/Math
$SBS_HOME/sbs.sh build Screen/Memory -b
#$SBS_HOME/sbs.sh build Screen/Fields
#$SBS_HOME/sbs.sh build Screen/XML
$SBS_HOME/sbs.sh build Screen/Main -b
$SBS_HOME/sbs.sh build Screen/OpenGL -i sbs-linux.xml
$SBS_HOME/sbs.sh build Demo/SFML
