#!/bin/bash
set -e
export DEBIAN_FRONTEND=noninteractive
export GROESTLCOIN_VERSION=24.0.1
export RUST_VERSION=stable
sudo useradd -ms /bin/bash tester
sudo apt-get update -qq

sudo apt-get -qq install --no-install-recommends --allow-unauthenticated -yy \
     autoconf \
     automake \
     binfmt-support \
     build-essential \
     clang \
     cppcheck \
     docbook-xml \
     eatmydata \
     gcc-aarch64-linux-gnu \
     gcc-arm-linux-gnueabihf \
     gcc-arm-none-eabi \
     gettext \
     git \
     libc6-dev-arm64-cross \
     libc6-dev-armhf-cross \
     libgmp-dev \
     libpq-dev \
     libprotobuf-c-dev \
     libsqlite3-dev \
     libtool \
     libxml2-utils \
     locales \
     net-tools \
     postgresql \
     python-pkg-resources \
     python3 \
     python3-dev \
     python3-pip \
     python3-setuptools \
     qemu \
     qemu-system-arm \
     qemu-user-static \
     shellcheck \
     software-properties-common \
     sudo \
     tcl \
     unzip \
     valgrind \
     wget \
     xsltproc \
     zlib1g-dev

echo "tester ALL=(root) NOPASSWD:ALL" | sudo tee /etc/sudoers.d/tester
sudo chmod 0440 /etc/sudoers.d/tester

(
    cd /tmp/ || exit 1
    wget https://github.com/Groestlcoin/groestlcoin/releases/download/v$GROESTLCOIN_VERSION/groestlcoin-24.0.1-x86_64-linux-gnu.tar.gz
    tar -xvzf groestlcoin-$GROESTLCOIN_VERSION-x86_64-linux-gnu.tar.gz
    sudo mv groestlcoin-$GROESTLCOIN_VERSION/bin/* /usr/local/bin
    rm -rf \
       groestlcoin-$GROESTLCOIN_VERSION-x86_64-linux-gnu.tar.gz \
       groestlcoin-$GROESTLCOIN_VERSION
)

curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- \
     -y --default-toolchain ${RUST_VERSION}

# We also need a relatively recent protobuf-compiler, at least 3.12.0,
# in order to support the experimental `optional` flag.
PROTOC_VERSION=3.15.8
PB_REL="https://github.com/protocolbuffers/protobuf/releases"
curl -LO $PB_REL/download/v${PROTOC_VERSION}/protoc-${PROTOC_VERSION}-linux-x86_64.zip
sudo unzip protoc-3.15.8-linux-x86_64.zip -d /usr/local/
sudo chmod a+x /usr/local/bin/protoc
export PROTOC=/usr/local/bin/protoc
export PATH=$PATH:/usr/local/bin
env
ls -lha /usr/local/bin
