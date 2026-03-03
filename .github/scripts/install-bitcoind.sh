#!/bin/sh
# If an argument is specified, that dir is checked before downloading,
# and updated after successful install.

set -e

export GROESTLCOIN_VERSION=27.0

DIRNAME="groestlcoin-${GROESTLCOIN_VERSION}"
FILENAME="${DIRNAME}-x86_64-linux-gnu.tar.gz"

cd /tmp/

# Since we inadvertently broke `elementsd` support in the past we only
# want to download and enable the daemon that is actually going to be
# used when running in CI. Otherwise we could end up accidentally
# testing against `groestlcoind` but still believe that we ran against
# `elementsd`.
if [ "$TEST_NETWORK" = "liquid-regtest" ]; then
    if [ -f "$1/${EFILENAME}" ]; then
	cp "$1/${EFILENAME}" .
    else
	wget "https://github.com/Groestlcoin/groestlcoin/releases/download/v${GROESTLCOIN_VERSION}/${FILENAME}"
    fi
    tar -xf "${EFILENAME}"
    [ "$1" = "" ] || cp "${EFILENAME}" "$1"/
    sudo mv "${EDIRNAME}"/bin/* "/usr/local/bin"
    rm -rf "${EFILENAME}" "${EDIRNAME}"
else
    if [ -f "$1/${FILENAME}" ]; then
	cp "$1/${FILENAME}" .
    else
	wget "https://github.com/Groestlcoin/groestlcoin/releases/download/v${GROESTLCOIN_VERSION}/${FILENAME}"
    fi
    tar -xf "${FILENAME}"
    [ "$1" = "" ] || cp "${FILENAME}" "$1"/
    sudo mv "${DIRNAME}"/bin/* "/usr/local/bin"
    rm -rf "${FILENAME}" "${DIRNAME}"
fi
