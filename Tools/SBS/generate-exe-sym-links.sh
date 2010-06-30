#!/bin/sh

mkdir -p ${4}
cd ${4}
ln -s ${3}/${1} ${1}.${2}
ln -s ${1}.${2} ${1}
cd -

