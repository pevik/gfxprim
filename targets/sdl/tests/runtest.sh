#!/bin/bash
#
# Run dynamically linked test.
#

PROG="$1"
shift

echo "LD_LIBRARY_PATH=..:../../.. ./$PROG $@"
LD_LIBRARY_PATH=..:../../.. ./$PROG $@