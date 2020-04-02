#!/usr/bin/env bash

#-------------------------------------------------------
# Runs our copy of https://github.com/jfalcou/spy's script/embed.py
# Writes output to the console
# Issues
# - maybe remove all lines with begin-snippet and end-snippet from the source code
#-------------------------------------------------------

python3 ./scripts/embed.py \
  ../ApprovalTests/ApprovalTests.hpp \
  -I .. -I ../ApprovalTests/
