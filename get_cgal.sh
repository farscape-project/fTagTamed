#!/bin/bash
set -e

###########
########### Software versions
###########
BOOST_VERSION=1.82.0
CGAL_VERSION=5.5.2

###########
########### Installation environment
###########
export TOPLEVEL=$PWD
export DEP_DIR=$TOPLEVEL/dep
export BUILD_DIR=$DEP_DIR/pkg
export PARCOMP=$(nproc)

mkdir -p $BUILD_DIR

###########
########### Boost
###########
BOOST_DIR=$DEP_DIR/boost-$BOOST_VERSION

BOOST_VSTR=$(sed 's/\./\_/g' <<< $BOOST_VERSION)

cd $BUILD_DIR
wget https://boostorg.jfrog.io/artifactory/main/release/$BOOST_VERSION/source/boost_$BOOST_VSTR.tar.gz
tar xpzf boost_$BOOST_VSTR.tar.gz
mv boost_$BOOST_VSTR $BOOST_DIR

###########
########### CGAL
###########
CGAL_DIR=$DEP_DIR/cgal-$CGAL_VERSION

cd $BUILD_DIR
wget https://github.com/CGAL/cgal/releases/download/v$CGAL_VERSION/CGAL-$CGAL_VERSION.tar.xz
tar xpf CGAL-$CGAL_VERSION.tar.xz
mv CGAL-$CGAL_VERSION $CGAL_DIR

###########
########### Setup script
###########
SETUP_SCRIPT=env_cgal.sh

cd $DEP_DIR
rm -f $SETUP_SCRIPT

echo "export BOOST_DIR='$BOOST_DIR'" >> $SETUP_SCRIPT
echo "export CGAL_DIR='$CGAL_DIR'" >> $SETUP_SCRIPT
