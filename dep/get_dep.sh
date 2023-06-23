#!/bin/bash
set -e

###########
########### Software versions
###########
GMP_VERSION=6.2.1
BOOST_VERSION=1.82.0
CGAL_VERSION=5.5.2

###########
########### Installation environment
###########
export TOPLEVEL=$PWD
export DEP_DIR=$TOPLEVEL
export BUILD_DIR=$DEP_DIR/pkg
export PARCOMP=$(nproc)

mkdir -p $BUILD_DIR

###########
########### GMP
###########
GMP_DIR=$DEP_DIR/gmp-$GMP_VERSION

cd $BUILD_DIR
wget https://gmplib.org/download/gmp/gmp-$GMP_VERSION.tar.xz
tar xpf gmp-$GMP_VERSION.tar.xz
mkdir gmp-${GMP_VERSION}_build
cd gmp-${GMP_VERSION}_build
$BUILD_DIR/gmp-$GMP_VERSION/configure --prefix=$GMP_DIR
make -j
make install

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
SETUP_SCRIPT=env_dep.sh

cd $DEP_DIR
rm -f $SETUP_SCRIPT

echo "export BOOST_DIR='$BOOST_DIR'" >> $SETUP_SCRIPT
echo "export CGAL_DIR='$CGAL_DIR'" >> $SETUP_SCRIPT
