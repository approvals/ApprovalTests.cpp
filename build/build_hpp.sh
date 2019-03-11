#!/bin/sh

# to run this in cygwin (after installing dos2unix):
#   cat build_hpp.sh | dos2unix | bash

# Force execution to halt if there are any errors in this script:
set -e
set -o pipefail

LAST_VERSION="v.3.1.0"
VERSION="v.3.1.1"

OLD_SINGLE_HEADER=ApprovalTests.$LAST_VERSION.hpp
NEW_SINGLE_HEADER=ApprovalTests.$VERSION.hpp

STARTER_PROJECT_DIR=../../ApprovalTests.Cpp.StarterProject

STARTER_PATH_OLD_SINGLE_HEADER=$STARTER_PROJECT_DIR/lib/$OLD_SINGLE_HEADER
STARTER_PATH_NEW_SINGLE_HEADER=$STARTER_PROJECT_DIR/lib/$NEW_SINGLE_HEADER

# ------------------------------------------------------------------------------------------------
# Create new single-header file

cd ../ApprovalTests
java -jar ../build/SingleHpp.v.0.0.2.jar ../build/releases/$NEW_SINGLE_HEADER

sed -i '1s|^|// More information at: https://github.com/approvals/ApprovalTests.cpp\n|' ../build/releases/$NEW_SINGLE_HEADER
sed -i "1s|^|// Approval Tests version $VERSION\n|" ../build/releases/$NEW_SINGLE_HEADER

# ------------------------------------------------------------------------------------------------
# Update Starter Project 

# Make sure starter project folder is clean
pushd $STARTER_PROJECT_DIR
git reset --hard
popd

cp ../build/releases/ApprovalTests.$VERSION.hpp $STARTER_PROJECT_DIR/lib

# Delete the last release:
if [ -f $STARTER_PATH_OLD_SINGLE_HEADER ] ; then
    rm $STARTER_PATH_OLD_SINGLE_HEADER
fi

# Update the version in the "redirect" header:
sed -i -e "s/$LAST_VERSION/$VERSION/" $STARTER_PROJECT_DIR/lib/ApprovalTests.hpp

# Update the version number in the Visual Studio project:
sed -i -e "s/$OLD_SINGLE_HEADER/$NEW_SINGLE_HEADER/" $STARTER_PROJECT_DIR/visual-studio-2017/StarterProject.vcxproj

# Check the starter project builds
pushd $STARTER_PROJECT_DIR/cmake-build-debug
cmake --build .
popd

# Commit starter project
pushd $STARTER_PROJECT_DIR
git add .
git commit -m "Update to Approvals $VERSION"
popd

# ------------------------------------------------------------------------------------------------

# The prefixes used in our commit messages come from: https://github.com/RefactoringCombos/ArlosCommitNotation
git log ${LAST_VERSION}..HEAD --pretty=format:%s | \
    grep -v '^[dert] ' | \
    grep -v 'Update to_do.txt' | \
    grep -v 'Update HowToRelease.md' | \
    grep -v 'Update README.md' | \
    grep -v 'Update StyleGuide.h' | \
    sort
