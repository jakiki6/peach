#!/bin/bash

export PATH=$(dirname "$(readlink -f "$0")")/cross/bin:$PATH
echo $(dirname "$(readlink -f "$0")")/cross/bin
