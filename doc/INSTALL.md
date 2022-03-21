Install
=======

1. [Library Requirements](#library-requirements)
2. [Ubuntu](#to-build-on-ubuntu)
3. [Fedora](#to-build-on-fedora)
4. [FreeBSD](#to-build-on-freebsd)
5. [OpenBSD](#to-build-on-openbsd)
6. [NixOS](#to-build-on-nixos)
7. [macOS](#to-build-on-macos)
8. [Android](#to-cross-compile-for-android)
9. [Raspberry Pi](#to-cross-compile-for-raspberry-pi)
10. [Armbian](#to-compile-for-armbian)
11. [Alpine](#to-compile-for-alpine)
12. [Additional steps](#additional-steps)

Library Requirements
--------------------

You will need several development libraries:
* libsqlite3: for database support.
* libgmp: for secp256k1
* zlib: for compression routines.

For actually doing development and running the tests, you will also need:
* pip3: to install python-bitcoinlib
* valgrind: for extra debugging checks

You will also need a version of groestlcoind with segregated witness and `estimatesmartfee` with `ECONOMICAL` mode support, such as the 2.16.0 or above.

To Build on Ubuntu
---------------------

OS version: Ubuntu 15.10 or above

Get dependencies:

    sudo apt-get update
    sudo apt-get install -y \
      autoconf automake build-essential git libtool libgmp-dev libsqlite3-dev \
      python3 python3-pip net-tools zlib1g-dev libsodium-dev gettext
    pip3 install --upgrade pip
    pip3 install --user poetry
    poetry install

If you don't have Groestlcoin installed locally you'll need to install that
as well. It's now available via [snapd](https://snapcraft.io/groestlcoin-core).

    sudo apt-get install snapd
    sudo snap install groestlcoin-core
    # Snap does some weird things with binary names; you'll
    # want to add a link to them so everything works as expected
    sudo ln -s /snap/groestlcoin-core/current/bin/groestlcoin{d,-cli} /usr/local/bin/

Clone lightning:

    git clone https://github.com/groestlcoin/lightning.git
    cd lightning

For development or running tests, get additional dependencies:

    sudo apt-get install -y valgrind libpq-dev shellcheck cppcheck \
      libsecp256k1-dev jq

Build lightning:

    ./configure
    make
    sudo make install

Running lightning:

    groestlcoind &
    ./lightningd/lightningd &
    ./cli/lightning-cli help

**Note**: You may need to include `testnet=1` in `groestlcoin.conf`

To Build on Fedora
---------------------

OS version: Fedora 27 or above

Get dependencies:
```
$ sudo dnf update -y && \
        sudo dnf groupinstall -y \
                'C Development Tools and Libraries' \
                'Development Tools' && \
        sudo dnf install -y \
                clang \
                gettext \
                git \
                gmp-devel \
                libsq3-devel \
                python3-devel \
                python3-pip \
                python3-setuptools \
                net-tools \
                valgrind \
                wget \
                zlib-devel \
				libsodium-devel && \
        sudo dnf clean all
```

Make sure you have [groestlcoind](https://github.com/groestlcoin/groestlcoin) available to run

Clone lightning:
```
$ git clone https://github.com/groestlcoin/lightning.git
$ cd lightning
```

Build and install lightning:
```
$lightning> ./configure
$lightning> make
$lightning> sudo make install
```

Running lightning (mainnet):
```
$ groetlcoind &
$ lightningd --network=groestlcoin
```

Running lightning on testnet:
```
$ groestlcoind -testnet &
$ lightningd --network=testnet
```

To Build on macOS
---------------------

Assuming you have Xcode and Homebrew installed. Install dependencies:

    $ brew install autoconf automake libtool python3 gmp gnu-sed gettext libsodium
    $ ln -s /usr/local/Cellar/gettext/0.20.1/bin/xgettext /usr/local/opt
    $ export PATH="/usr/local/opt:$PATH"

If you need SQLite (or get a SQLite mismatch build error):

    $ brew install sqlite
    $ export LDFLAGS="-L/usr/local/opt/sqlite/lib"
    $ export CPPFLAGS="-I/usr/local/opt/sqlite/include"

Some library paths are different when using `homebrew` with M1 macs, therefore the following two variables need to be set for M1 machines

    $ export CPATH=/opt/homebrew/include
    $ export LIBRARY_PATH=/opt/homebrew/lib

If you need Python 3.x for mako (or get a mako build error):

    $ brew install pyenv
    $ echo -e 'if command -v pyenv 1>/dev/null 2>&1; then\n  eval "$(pyenv init -)"\nfi' >> ~/.bash_profile
    $ source ~/.bash_profile
    $ pyenv install 3.7.4
    $ pip install --upgrade pip

If you don't have groestlcoind installed locally you'll need to install that
as well:

    $ brew install \
    boost miniupnpc openssl pkg-config protobuf qt libevent
    $ brew tap zeroc-ice/tap
    $ brew install zeroc-ice/tap/berkeley-db@5.3
    $ git clone https://github.com/groestlcoin/groestlcoin
    $ cd groestlcoin
    $ ./autogen.sh
    $ ./configure LDFLAGS=-L/usr/local/opt/berkeley-db@5.3/lib CPPFLAGS=-I/usr/local/opt/berkeley-db@5.3/include
    $ make & make install

Clone lightning:

    $ git clone https://github.com/groestlcoin/lightning.git
    $ cd lightning

Configure Python 3.x & get mako:

    $ pyenv local 3.7.4
    $ pip install mako

Build lightning:

    $ pip install -r requirements.txt
    $ ./configure
    $ make

Running lightning:

**Note**: Edit your `~/Library/Application\ Support/Groestlcoin/groestlcoin.conf`
to include `rpcuser=<foo>` and `rpcpassword=<bar>` first, you may also
need to include `testnet=1`

    groestlcoind &
    ./lightningd/lightningd &
    ./cli/lightning-cli help

To cross-compile for Android
--------------------

Make a standalone toolchain as per
https://developer.android.com/ndk/guides/standalone_toolchain.html.
For c-lightning you must target an API level of 24 or higher.

Depending on your toolchain location and target arch, source env variables
such as:

    export PATH=$PATH:/path/to/android/toolchain/bin
    # Change next line depending on target device arch
    target_host=arm-linux-androideabi
    export AR=$target_host-ar
    export AS=$target_host-clang
    export CC=$target_host-clang
    export CXX=$target_host-clang++
    export LD=$target_host-ld
    export STRIP=$target_host-strip

Two makefile targets should not be cross-compiled so we specify a native CC:

    make CC=clang clean ccan/tools/configurator/configurator
    make clean -C ccan/ccan/cdump/tools \
      && make CC=clang -C ccan/ccan/cdump/tools

Install the `qemu-user` package.
This will allow you to properly configure
the build for the target device environment.
Build with:

    BUILD=x86_64 MAKE_HOST=arm-linux-androideabi \
      make PIE=1 DEVELOPER=0 \
      CONFIGURATOR_CC="arm-linux-androideabi-clang -static"

To cross-compile for Raspberry Pi
--------------------

Obtain the [official Raspberry Pi toolchains](https://github.com/raspberrypi/tools).
This document assumes compilation will occur towards the Raspberry Pi 3
(arm-linux-gnueabihf as of Mar. 2018).

Depending on your toolchain location and target arch, source env variables
will need to be set. They can be set from the command line as such:

    export PATH=$PATH:/path/to/arm-linux-gnueabihf/bin
    # Change next line depending on specific Raspberry Pi device
    target_host=arm-linux-gnueabihf
    export AR=$target_host-ar
    export AS=$target_host-as
    export CC=$target_host-gcc
    export CXX=$target_host-g++
    export LD=$target_host-ld
    export STRIP=$target_host-strip

Install the `qemu-user` package. This will allow you to properly configure the
build for the target device environment.
Config the arm elf interpreter prefix:

    export QEMU_LD_PREFIX=/path/to/raspberry/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/arm-linux-gnueabihf/sysroot/

Obtain and install cross-compiled versions of sqlite3, gmp and zlib:

Download and build zlib:

    wget https://zlib.net/zlib-1.2.11.tar.gz
    tar xvf zlib-1.2.11.tar.gz
    cd zlib-1.2.11
    ./configure --prefix=$QEMU_LD_PREFIX
    make
    make install

Download and build sqlite3:

    wget https://www.sqlite.org/2018/sqlite-src-3260000.zip
    unzip sqlite-src-3260000.zip
    cd sqlite-src-3260000
    ./configure --enable-static --disable-readline --disable-threadsafe --disable-load-extension --host=$target_host --prefix=$QEMU_LD_PREFIX
    make
    make install

Download and build gmp:

    wget https://gmplib.org/download/gmp/gmp-6.1.2.tar.xz
    tar xvf gmp-6.1.2.tar.xz
    cd gmp-6.1.2
    ./configure --disable-assembly --host=$target_host --prefix=$QEMU_LD_PREFIX
    make
    make install

Then, build c-lightning with the following commands:

    ./configure
    make

To compile for Armbian
--------------------
For all the other Pi devices out there, consider using [Armbian](https://www.armbian.com).

You can compile in `customize-image.sh` using the instructions for Ubuntu.

A working example that compiles both groestlcoind and c-lightning for Armbian can
be found [here](https://github.com/groestlcoin/armbian-groestlcoin-core).

To compile for Alpine
---------------------
Get dependencies:
```
apk update
apk add ca-certificates alpine-sdk autoconf automake git libtool \
  gmp-dev sqlite-dev python python3 py3-mako net-tools zlib-dev libsodium gettext
```
Clone lightning:
```
git clone https://github.com/ElementsProject/lightning.git
cd lightning
git submodule update --init --recursive
```
Build and install:
```
./configure
make
make install
```
Clean up:
```
cd .. && rm -rf lightning
apk del ca-certificates alpine-sdk autoconf automake git libtool \
  gmp-dev sqlite python3 py3-mako net-tools zlib-dev libsodium gettext
```

Additional steps
--------------------
Go to [README](https://github.com/groestlcoin/lightning/blob/master/README.md) for more information how to create an address, add funds, connect to a node, etc.
