#!/bin/sh
set -efux

install_requirements() {
  pacman --noconfirm -R catgets || true
  pacman --noconfirm -R libcatgets || true
  pacman --noconfirm -Syu
  pacman --noconfirm -S --needed base-devel mingw-w64-x86_64-toolchain git
  pacman --noconfirm -S --needed mingw-w64-x86_64-qt5-static mingw-w64-x86_64-db mingw-w64-x86_64-miniupnpc mingw-w64-x86_64-qrencode mingw-w64-x86_64-jasper

  wget http://repo.msys2.org/mingw/x86_64/mingw-w64-x86_64-boost-1.57.0-3-any.pkg.tar.xz
  pacman --needed --noconfirm -U mingw-w64-x86_64-boost-1.57.0-3-any.pkg.tar.xz

  pacman --noconfirm -Sc
  rm -f mingw-w64-x86_64-boost-1.57.0-3-any.pkg.tar.xz
}

build_secp256k1() {
  [ -d secp256k1 ] || git clone https://github.com/bitcoin-core/secp256k1 --depth 1 -b master
  cd secp256k1
  ./autogen.sh
  ./configure --prefix=/usr/local --enable-module-recovery
  make -j5
  make install
}

patch_bashcoin() {
patch -Np1 <<'EOF'
From 04bdae7d00b1175aca261934ef329523556281ca Mon Sep 17 00:00:00 2001
From: Sergey Nazaryev <sergey@nazaryev.ru>
Date: Wed, 31 Jan 2018 15:25:17 +0300
Subject: [PATCH] =?UTF-8?q?=D0=98=D1=81=D0=BF=D1=80=D0=B0=D0=B2=D0=BB?=
 =?UTF-8?q?=D0=B5=D0=BD=D0=B8=D1=8F=20=D0=B4=D0=BB=D1=8F=20=D1=81=D0=B1?=
 =?UTF-8?q?=D0=BE=D1=80=D0=BA=D0=B8=20=D0=B2=20msys2?=
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit

---
 Bashcoin.pro                      | 6 +++---
 src/leveldb/build_detect_platform | 2 +-
 src/qt/bitcoin.qrc                | 1 +
 3 files changed, 5 insertions(+), 4 deletions(-)

diff --git a/src/qt/bitcoin.qrc b/src/qt/bitcoin.qrc
index 60ccca1..6037198 100644
--- a/src/qt/bitcoin.qrc
+++ b/src/qt/bitcoin.qrc
@@ -80,5 +80,6 @@
     </qresource>
     <qresource prefix="/translations">
         <file alias="en">locale/bitcoin_en.qm</file>
+        <file alias="ru">locale/bitcoin_ru.qm</file>
     </qresource>
 </RCC>
diff --git a/Bashcoin.pro b/Bashcoin.pro
index fa75b38..4c7672b 100644
--- a/Bashcoin.pro
+++ b/Bashcoin.pro
@@ -29,7 +29,7 @@ greaterThan(QT_MAJOR_VERSION, 4) {
 # workaround for boost 1.58
 DEFINES += BOOST_VARIANT_USE_RELAXED_GET_BY_DEFAULT

-BOOST_LIB_SUFFIX=-mgw49-mt-s-1_55
+BOOST_LIB_SUFFIX=-mt
 BOOST_INCLUDE_PATH=C:/deps/boost_1_55_0
 BOOST_LIB_PATH=C:/deps/boost_1_55_0/stage/lib

@@ -81,7 +81,7 @@ QMAKE_CXXFLAGS *= -D_FORTIFY_SOURCE=2
 # for extra security on Windows: enable ASLR and DEP via GCC linker flags
 win32:QMAKE_LFLAGS *= -Wl,--dynamicbase -Wl,--nxcompat
 # on Windows: enable GCC large address aware linker flag
-win32:QMAKE_LFLAGS *= -Wl,--large-address-aware -static
+win32:QMAKE_LFLAGS *= -static
 # i686-w64-mingw32
 win32:QMAKE_LFLAGS *= -static-libgcc -static-libstdc++

@@ -517,6 +517,7 @@

 isEmpty(BDB_LIB_SUFFIX) {
     macx:BDB_LIB_SUFFIX = -4.8
+    win32:BDB_LIB_SUFFIX = -6.0
 }

 isEmpty(BDB_INCLUDE_PATH) {
@@ -618,7 +618,7 @@ windows:LIBS += -lws2_32 -lshlwapi -lmswsock -lole32 -loleau                                               t32 -luuid -lgdi32 -
     LIBS += -lgmp
 } else {
     INCLUDEPATH += $$SECP256K1_INCLUDE_PATH
-    LIBS += $$join(SECP256K1_LIB_PATH,,-L,) -lsecp256k1
+    LIBS += $$join(SECP256K1_LIB_PATH,,-L,) -lsecp256k1 -lgmp
 }
 LIBS += -lboost_system$$BOOST_LIB_SUFFIX -lboost_filesystem$$BOOST_LIB_SUFFIX -                                               lboost_program_options$$BOOST_LIB_SUFFIX -lboost_thread$$BOOST_THREAD_LIB_SUFFIX
 windows:LIBS += -lboost_chrono$$BOOST_LIB_SUFFIX
diff --git a/src/leveldb/build_detect_platform b/src/leveldb/build_detect_platfo                                               rm
index 85b1ce0..725cb2b 100644
--- a/src/leveldb/build_detect_platform
+++ b/src/leveldb/build_detect_platform
@@ -147,7 +147,7 @@ case "$TARGET_OS" in
         PLATFORM_SHARED_CFLAGS=
         PLATFORM_SHARED_VERSIONED=
         ;;
-    OS_WINDOWS_CROSSCOMPILE | NATIVE_WINDOWS)
+    OS_WINDOWS_CROSSCOMPILE | NATIVE_WINDOWS | MINGW64_NT-6.1 | MINGW32_NT-6.1 | MINGW32_NT-10.0 | MINGW64_NT-10.0)
         PLATFORM=OS_WINDOWS
         COMMON_FLAGS="-fno-builtin-memcmp -D_REENTRANT -DOS_WINDOWS -DLEVELDB_P                                               LATFORM_WINDOWS -DWINVER=0x0500 -D__USE_MINGW_ANSI_STDIO=1"
         PLATFORM_SOURCES="util/env_win.cc"
--
2.10.1
EOF
}

build_bashcoin() {
  [ -d mmm ] ||  {
    git clone https://github.com/top422/mmm --depth 1 -b master
    cd mmm && patch_bashcoin || true
  }

  make -j5 -C src/leveldb/ libleveldb.a libmemenv.a > /dev/null
  /mingw64/qt5-static/bin/qmake
  make -j5 -f Makefile.Release > /dev/null
  strip -s release/bashcoin-qt.exe
  cp release/bashcoin-qt.exe ../..
}

main() {
  install_requirements

  mkdir -p src && cd src

  (build_secp256k1)

  export CPATH=$PWD/secp256k1/include
  export LIBRARY_PATH=/usr/local/lib
  build_bashcoin
  pacman --noconfirm -R mingw-w64-x86_64-boost
}

main "$@"
