#!/usr/bin/env bash
set -e

export PKG_CONFIG_PATH=$HOME/.loca/lib/pkgconfig
export LD_LIBRARY_PATH=$HOME/.loca/lib

meson setup builddir --wipe
meson compile -C builddir
./builddir/fingering
