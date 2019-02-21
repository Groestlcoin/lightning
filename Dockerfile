FROM debian:stretch-slim as builder

RUN apt-get update && apt-get install -y \
  autoconf automake build-essential git libtool libgmp-dev \
  libsqlite3-dev python python3 net-tools zlib1g-dev wget

WORKDIR /opt

ENV GROESTLCOIN_VERSION 2.17.2
ENV GROESTLCOIN_TARBALL groestlcoin-${GROESTLCOIN_VERSION}-x86_64-linux-gnu.tar.gz
ENV GROESTLCOIN_URL https://github.com/Groestlcoin/groestlcoin/releases/download/v$GROESTLCOIN_VERSION/$GROESTLCOIN_TARBALL
ENV GROESTLCOIN_ASC_URL https://github.com/Groestlcoin/groestlcoin/releases/download/v$GROESTLCOIN_VERSION/SHA256SUMS.asc
ENV GROESTLCOIN_PGP_KEY 287AE4CA1187C68C08B49CB2D11BD4F33F1DB499

RUN mkdir /opt/groestlcoin && cd /opt/groestlcoin \
    && wget -qO $GROESTLCOIN_TARBALL "$GROESTLCOIN_URL" \
    && gpg --batch --keyserver keyserver.ubuntu.com --recv-keys "$GROESTLCOIN_PGP_KEY" \
    && wget -qO groestlcoin.asc "$GROESTLCOIN_ASC_URL" \
    && gpg --verify groestlcoin.asc \
  # && grep $GROESTLCOIN_TARBALL groestlcoin.asc | tee SHA256SUMS.asc \
  # && sha256sum -c SHA256SUMS.asc \
    && BD=groestlcoin-$GROESTLCOIN_VERSION/bin \
    && tar -xzvf $GROESTLCOIN_TARBALL $BD/groestlcoin-cli --strip-components=1 \
    && rm $GROESTLCOIN_TARBALL

ENV LIGHTNINGD_VERSION=master

WORKDIR /opt/lightningd
COPY . /tmp/lightning
RUN git clone --recursive /tmp/lightning . && \
    git checkout $(git --work-tree=/tmp/lightning --git-dir=/tmp/lightning/.git rev-parse HEAD)

ARG DEVELOPER=0
RUN ./configure && make -j3 DEVELOPER=${DEVELOPER} && cp lightningd/lightning* cli/lightning-cli /usr/bin/

FROM debian:stretch-slim

RUN apt-get update && apt-get install -y \
	autoconf automake build-essential git libtool libgmp-dev \
	libsqlite3-dev python python3 net-tools zlib1g-dev jq bc

ENV LIGHTNINGD_DATA=/root/.lightning
ENV LIGHTNINGD_RPC_PORT=9835

RUN mkdir $LIGHTNINGD_DATA && \
    touch $LIGHTNINGD_DATA/config

VOLUME [ "/root/.lightning" ]

COPY --from=builder /opt/lightningd/cli/lightning-cli /usr/bin
COPY --from=builder /opt/lightningd/lightningd/lightning* /usr/bin/
COPY --from=builder /opt/groestlcoin /usr/bin
COPY tools/docker-entrypoint.sh entrypoint.sh

EXPOSE 9735 9835
ENTRYPOINT  [ "./entrypoint.sh" ]
