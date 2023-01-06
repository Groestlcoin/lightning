#! /bin/sh
# Simple script to bootstrap a running mainnet node.

set -e

# If lightning-cli not in their path, assume it's in subdir.
# shellcheck disable=SC2039
if type lightning-cli >/dev/null 2>&1; then
    LCLI=lightning-cli
elif [ -x cli/lightning-cli ]; then
    LCLI=cli/lightning-cli
else
    echo "Cannot find lightning-cli!" >&2
    exit 1
fi

if ! $LCLI "$@" -H getinfo | grep 'network=groestlcoin'; then
    echo "lightningd not running, or not on mainnet?" >&2
    exit 1
fi

# Pick two random peers from this list, and connect to them.
# IPV4: 0391c8d0e27fe61ed8cb8784aeae5848bd8b193ea5720dea32ca2694a326fe41f9@104.236.133.196
# IPV4: 03046e1650b0e67925d260f4888f809598af6cef58fbfc6446fbd4fddf1828ca3d@104.236.130.222

PEERS=$(grep '^# IPV4:' "$0" | sort -R | tail -n 3 | cut -d' ' -f3-)

for p in $PEERS; do
    echo "Trying to connect to random peer $p..."
    $LCLI "$@" connect "$p" || true
done
