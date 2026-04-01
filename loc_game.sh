#!/usr/bin/env sh

cloc src/game -json | jq ".SUM.code"
