#!/bin/sh
set -efux

install_requirements() {
  pacman --noconfirm -R catgets || true
  pacman --noconfirm -R libcatgets || true
  pacman --noconfirm -R mingw-w64-x86_64-db || true
  pacman --noconfirm -R mingw-w64-x86_64-boost || true
  pacman --noconfirm -Syu
  pacman --noconfirm -S --needed base-devel mingw-w64-x86_64-toolchain git
  pacman --noconfirm -S --needed mingw-w64-x86_64-qt5-static mingw-w64-x86_64-miniupnpc mingw-w64-x86_64-qrencode mingw-w64-x86_64-jasper

  wget http://repo.msys2.org/mingw/x86_64/mingw-w64-x86_64-boost-1.57.0-3-any.pkg.tar.xz
  pacman --needed --noconfirm -U mingw-w64-x86_64-boost-1.57.0-3-any.pkg.tar.xz

  pacman --noconfirm -Sc
  rm -f mingw-w64-x86_64-boost-1.57.0-3-any.pkg.tar.xz
}

build_secp256k1() {
  [ -d secp256k1 ] || { 
    git clone https://github.com/bitcoin-core/secp256k1 --depth 1 -b master
    cd secp256k1
    ./autogen.sh > /dev/null
    ./configure --prefix=/usr/local --enable-module-recovery > /dev/null
    make -j$(nproc)
    make install > /dev/null
	cd ..
  }
}

build_db() {
  [ -d db-4.8.30 ] || {
	wget http://download.oracle.com/berkeley-db/db-4.8.30.tar.gz
	tar -xzf db-4.8.30.tar.gz
	cd db-4.8.30/build_unix/
    ../dist/configure --prefix=/usr/local --enable-cxx --enable-mingw --disable-replication > /dev/null
	make -j$(nproc)
	make install > /dev/null
	cd ../..
	rm db-4.8.30.tar.gz
  }
}

build_ferrumcoin() {
  [ -d ferrum ] ||  {
    git clone https://github.com/Ferrumcrypto/ferrum --depth 1 -b master
    cd ferrum/
	rm -Rf src/secp256k1
	git clone https://github.com/bitcoin-core/secp256k1 --depth 1 -b master src/secp256k1
	cd ..
  }

  cd ferrum/
  make -j$(nproc) -C src/leveldb/ libleveldb.a libmemenv.a
  /mingw64/qt5-static/bin/qmake
  make -j$(nproc) -f Makefile.Release
  strip -s release/ferrumcoin-qt.exe
  cp release/ferrumcoin-qt.exe ../..
}

main() {
  install_requirements
  mkdir -p src && cd src
  build_secp256k1
  build_db
  build_ferrumcoin
  pacman --noconfirm -R mingw-w64-x86_64-boost
}

main "$@"
