#!/usr/bin/env bash
set -e

meson setup builddir --wipe
meson compile -C builddir
./builddir/fingering
