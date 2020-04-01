#!/usr/bin/env bash


#-------------------------------------------------------
# https://github.com/jfalcou/spy's script/embed.py
#
# Issues
# - strips out comments /* */ - even if they are small parts of line, e.g.
#         bool report(std::string /*received*/, std::string /*approved*/) const override
# - does not include comment indicating name of include file that was pulled in
# - it tried pulling in <string> and similar - had to make this edit:
#-r_pp_include = re.compile('^\s*#\s*include\s+["|<](.*)["|>]$')
#+r_pp_include = re.compile('^\s*#\s*include\s+["](.*)["]$')
#
#-------------------------------------------------------

#python3 /Users/clare/Documents/develop/SingleHeaderTools/spy/script/embed.py \
python3 ./scripts/embed.py \
  ../ApprovalTests/ApprovalTests.hpp \
  -I .. -I ../ApprovalTests/ > ../ApprovalTests/expanded.hpp
compare \
  /Users/clare/Documents/develop/ApprovalTests/ApprovalTests.cpp/build/releases/ApprovalTests.v.8.5.0.hpp \
  ../ApprovalTests/expanded.hpp
