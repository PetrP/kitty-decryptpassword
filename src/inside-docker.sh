#!/bin/bash
set -eufC -o pipefail
shopt -s inherit_errexit extglob dotglob failglob globstar nullglob shift_verbose

git clone --depth 1 --branch v0.76.0.11 https://github.com/cyd01/KiTTY
cd KiTTY/0.76_My_PuTTY/windows

cat /src/MAKEFILE.append >> MAKEFILE.MINGW
cp /src/main.c kitty-decryptpassword-main.c

rm -f /builds/kitty-decryptpassword.exe
make -f MAKEFILE.MINGW kitty-decryptpassword
mv kitty-decryptpassword.exe /builds/kitty-decryptpassword.exe
