#!/bin/sh

# https://instagram-engineering.com/let-your-code-type-hint-itself-introducing-open-source-monkeytype-a855c7284881
rm -f monkeytype.sqlite3
monkeytype run *.py scripts/*.py
for module in $(monkeytype list-modules) ; do
  monkeytype apply $module
done
