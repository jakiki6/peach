#!/bin/bash

export TARGET=x86_64-elf

cd $(dirname "$(readlink -f "$0")")

mkdir build
cd build

wget https://ftp.gnu.org/gnu/gcc/gcc-10.2.0/gcc-10.2.0.tar.xz && tar fx gcc-10.2.0.tar.xz
wget https://ftp.gnu.org/gnu/binutils/binutils-2.36.tar.xz && tar fx binutils-2.36.tar.xz
wget https://ftp.gnu.org/gnu/mpfr/mpfr-4.1.0.tar.xz && tar fx mpfr-4.1.0.tar.xz
wget https://ftp.gnu.org/gnu/gmp/gmp-6.2.1.tar.xz && tar fx gmp-6.2.1.tar.xz
wget https://ftp.gnu.org/gnu/mpc/mpc-1.2.1.tar.gz && tar fx mpc-1.2.1.tar.gz

cd gcc-10.2.0
ln -s ../mpfr-4.1.0 mpfr
ln -s ../gmp-6.2.1 gmp
ln -s ../mpc-1.2.1 mpc
cd ..

mkdir ../cross
export PREFIX=$(pwd)/../cross
export PATH=$PEFIX/bin:$PATH

mkdir build-binutils
cd build-binutils
../binutils-2.36/configure --prefix=$PREFIX --target=$TARGET --disable-multilib
make -j $(nproc)
make install
cd ..

mkdir build-gcc
cd build-gcc
../gcc-10.2.0/configure --prefix=$PREFIX --target=$TARGET --enable-languages=c,c++ --disable-multilib
make -j $(nproc) all-gcc
make install-gcc
make -j $(nproc) all-target-libgcc
make install-target-libgcc
cd ..


cd ../../thirdparty/echfs
make
cp echfs-utils $PREFIX/bin/

cd ..
cd limine
make
cp limine-install $PREFIX/bin/
