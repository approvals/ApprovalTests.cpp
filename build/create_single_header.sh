#!/usr/bin/env bash


#-------------------------------------------------------
# https://github.com/jfalcou/spy's script/embed.py
#
# Issues
# - does not include comment indicating name of include file that was pulled in
#
#-------------------------------------------------------

#python3 /Users/clare/Documents/develop/SingleHeaderTools/spy/script/embed.py \
python3 ./scripts/embed.py \
  ../ApprovalTests/ApprovalTests.hpp \
  -I .. -I ../ApprovalTests/ > ../ApprovalTests/expanded.hpp
compare \
  /Users/clare/Documents/develop/ApprovalTests/ApprovalTests.cpp/build/releases/ApprovalTests.v.8.5.0.hpp \
  ../ApprovalTests/expanded.hpp
