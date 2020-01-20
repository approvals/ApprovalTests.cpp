#! /usr/bin/env python3

# Constants
import os
import subprocess

UNSET_VERSION="v.X.X.X"

LAST_VERSION="v.7.0.0"
VERSION=UNSET_VERSION

PUSH_TO_PRODUCTION=True
# Note that we won't push if the version number is unset

OLD_SINGLE_HEADER=F"ApprovalTests.{LAST_VERSION}.hpp"
NEW_SINGLE_HEADER=F"ApprovalTests.{VERSION}.hpp"
NEW_SINGLE_HEADER_TEMP=F"{NEW_SINGLE_HEADER}.tmp"

RELEASE_DIR=F"../build/releases"
RELEASE_NEW_SINGLE_HEADER=F"{RELEASE_DIR}/{NEW_SINGLE_HEADER}"
RELEASE_NEW_SINGLE_HEADER_TEMP=F"{RELEASE_DIR}/{NEW_SINGLE_HEADER_TEMP}"

STARTER_PROJECT_DIR=F"../../ApprovalTests.Cpp.StarterProject"
STARTER_PATH_OLD_SINGLE_HEADER=F"{STARTER_PROJECT_DIR}/lib/{OLD_SINGLE_HEADER}"
STARTER_PATH_NEW_SINGLE_HEADER=F"{STARTER_PROJECT_DIR}/lib/{NEW_SINGLE_HEADER}"

# TODO copy in checks from https://github.com/pages-themes/minimal/blob/master/script/release

# ------------------------------------------------------------------------------------------------
# Create new single-header file

# TODO Rework to not write tmp file
def create_single_header_file():
    os.chdir("../ApprovalTests")
    subprocess.call(["java", "-jar", "../build/SingleHpp.v.0.0.2.jar", RELEASE_NEW_SINGLE_HEADER_TEMP], shell=True)
    with open(RELEASE_NEW_SINGLE_HEADER_TEMP) as input:
        text = input.read()
    text = F"""
// Approval Tests version {VERSION}
// More information at: https://github.com/approvals/ApprovalTests.cpp

{text}
"""
    with open(RELEASE_NEW_SINGLE_HEADER, 'w') as output:
        output.write(text)


create_single_header_file()

# ------------------------------------------------------------------------------------------------
# Update Starter Project 

# Make sure starter project folder is clean
pushd $STARTER_PROJECT_DIR
git clean -fx
git reset --hard
popd

cp $RELEASE_NEW_SINGLE_HEADER $STARTER_PATH_NEW_SINGLE_HEADER

# Delete the last release:
if [ -f $STARTER_PATH_OLD_SINGLE_HEADER ] ; then
    rm $STARTER_PATH_OLD_SINGLE_HEADER
fi

# Update the version in the "redirect" header:
sed -i '' -e "s/$LAST_VERSION/$VERSION/" $STARTER_PROJECT_DIR/lib/ApprovalTests.hpp

# Update the version number in the Visual Studio project:
sed -i '' -e "s/$OLD_SINGLE_HEADER/$NEW_SINGLE_HEADER/" $STARTER_PROJECT_DIR/visual-studio-2017/StarterProject.vcxproj

# Check the starter project builds
pushd $STARTER_PROJECT_DIR/cmake-build-debug
cmake --build .
popd

if [ "$VERSION" == "$UNSET_VERSION" ] ; then
    echo "Everything worked - version number not set, so didn't commit or push"
    exit
fi

if [ "$PUSH_TO_PRODUCTION" == "false" ] ; then
    # Don't push to production if we haven't set the version number
    echo "Everything worked - didn't commit or push"
    exit
fi

# Commit and push starter project
pushd $STARTER_PROJECT_DIR
git add .
git commit -m "Update to Approvals $VERSION"
git push origin master
popd

# ------------------------------------------------------------------------------------------------

# Update the top-level readme file and other documentation
pushd ..
sed -i -e "s/$LAST_VERSION/$VERSION/g" mdsource/README.source.md
./run_markdown_templates.sh
popd

# Draft the tweet
open "https://twitter.com/intent/tweet?text=%23ApprovalTests.cpp+$VERSION+released%2C+now+with+___%21%0D%0Ahttps%3A%2F%2Fgithub.com%2Fapprovals%2FApprovalTests.cpp%2Freleases%2Ftag%2F$VERSION+%0D%0Aor+try+the+starter+project%3A+https%3A%2F%2Fgithub.com%2Fapprovals%2FApprovalTests.cpp.StarterProject%0D%0AThanks+%40LlewellynFalco+%40ClareMacraeUK+%21"

# Draft the upload to github - do this last, so this tab appears on top
open "https://github.com/approvals/ApprovalTests.cpp/releases/new?tag=$VERSION&title=Single%20Hpp%20File%20-%20$VERSION"

open $RELEASE_DIR/

# The prefixes used in our commit messages come from: https://github.com/RefactoringCombos/ArlosCommitNotation
git log ${LAST_VERSION}..HEAD --pretty=format:%s | \
    grep -v '^[dert] ' | \
    grep -v 'Update to_do.txt' | \
    grep -v 'Update HowToRelease.md' | \
    grep -v 'Update README.md' | \
    grep -v 'Update StyleGuide.h' | \
    sort

# TODO In future - prompt for version number
#read -p "Enter the next version number (last was:  $LAST_VERSION )" VERSION
#sed -i -e "s/$LAST_VERSION/$VERSION/g" ../build/build_hpp.sh

