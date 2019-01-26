#!/bin/sh

# to run this in cygwin (after installing dos2unix):
#   cat build_hpp.sh | dos2unix | bash

LAST_VERSION="v.3.0.0"
VERSION="v.3.1.0"

cd ../ApprovalTests
java -jar ../build/SingleHpp.v.0.0.2.jar ../build/releases/ApprovalTests.$VERSION.hpp

cp ../build/releases/ApprovalTests.$VERSION.hpp ../../ApprovalTests.Cpp.StarterProject/lib

git log ${LAST_VERSION}..HEAD --pretty=format:%s | \
    grep -v '^[der] ' | \
    grep -v 'Update to_do.txt' | \
    grep -v 'Update README.md' | \
    grep -v 'Update StyleGuide.h' | \
    sort
