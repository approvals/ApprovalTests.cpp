#!/bin/sh

python3 -m mypy \
  --follow-imports=skip \
  --ignore-missing-imports \
  *.py \
  scripts/*.py \
  tests/*.py
