#!/bin/bash
set -eufC -o pipefail
shopt -s inherit_errexit extglob dotglob failglob globstar nullglob shift_verbose

# https://www.9bis.net/kitty/#!pages/HowToCompile.md
sudo docker run --rm -it \
	-v $(pwd)/builds:/builds \
	-v $(pwd)/src:/src \
	cyd01/cross-gcc "/src/inside-docker.sh"
sudo chown "$LOGNAME:" builds/kitty-decryptpassword.exe
