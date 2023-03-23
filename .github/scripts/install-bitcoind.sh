#!/bin/sh

set -e

DIRNAME="groestlcoin-${GROESTLCOIN_VERSION}"
FILENAME="${DIRNAME}-x86_64-linux-gnu.tar.gz"

cd /tmp/
wget "https://github.com/Groestlcoin/groestlcoin/releases/download/v${GROESTLCOIN_VERSION}/${FILENAME}"
tar -xf "${FILENAME}"
sudo mv "${DIRNAME}"/bin/* "/usr/local/bin"


rm -rf "${FILENAME}" "${DIRNAME}"
