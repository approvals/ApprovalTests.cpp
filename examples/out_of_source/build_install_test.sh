#!/usr/bin/env bash

# Force execution to halt if there are any errors in this script:
set -e
set -o pipefail

cwd=`pwd`
cpp_files=`ls *.cpp`
#echo $cpp_files

pushd ../../cmake-build-spaces/cmake-build-debug-clang-11.0.0
cmake --build . --target out_of_source

pushd examples/out_of_source
ctest .
popd

mkdir -p clare_install/usr/local/out_of_source
echo 'Before install: ----------------------------------------------------------------------------'
ls -lsR  clare_install/usr/local/out_of_source

rm -rf   clare_install/usr/local/out_of_source/*
ls -lsR  clare_install/usr/local/out_of_source
DESTDIR=clare_install cmake --build . --target install

echo 'After install: ----------------------------------------------------------------------------'
ls -lsR clare_install/usr/local/out_of_source

# Remove source files
#echo ">>>>>>>>>>>>>>>>>>>> "
#pwd
#ls -ls ${cwd}
rm -f ${cwd}/*.cpp

pushd ./clare_install/usr/local/out_of_source

# Test run that should pass
echo 'Should pass: ----------------------------------------------------------------------------'
APPROVAL_TESTS_USE_REPORTER=TextDiffReporter ./out_of_source

# Test run that should pass - with environment variable
echo 'Should pass - with env var: -------------------------------------------------------------'
APPROVED_FILES_ROOT_DIR=. APPROVAL_TESTS_USE_REPORTER=TextDiffReporter ./out_of_source

# Test run that should fail
#echo 'Should fail: ----------------------------------------------------------------------------'
#echo "hello" >>out_of_source_test.out_of_source_sample.approved.txt
#APPROVED_FILES_ROOT_DIR=. APPROVAL_TESTS_USE_REPORTER=TextDiffReporter ./out_of_source

popd

popd

#pwd
git checkout master -- $cpp_files