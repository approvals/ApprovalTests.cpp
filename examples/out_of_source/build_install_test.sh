#!/usr/bin/env bash

# Force execution to halt if there are any errors in this script:
set -e
set -o pipefail

pushd ../../cmake-build-spaces/cmake-build-debug-clang-mp-90
cmake --build . --target out_of_source

pushd examples/out_of_source
ctest .
popd

mkdir -p clare_install
echo 'Before install: ----------------------------------------------------------------------------'
ls -lsR clare_install/usr/local/out_of_source

rm -rf  clare_install/usr/local/out_of_source/*
ls -lsR clare_install/usr/local/out_of_source
DESTDIR=clare_install make install

echo 'After install: ----------------------------------------------------------------------------'
ls -lsR clare_install/usr/local/out_of_source

pushd ./clare_install/usr/local/out_of_source

# Test run that should pass
echo 'Should pass: ----------------------------------------------------------------------------'
APPROVED_FILES_ROOT_DIR=. APPROVAL_TESTS_USE_REPORTER=TextDiffReporter ./out_of_source

echo 'Should fail: ----------------------------------------------------------------------------'
# Test run that should fail
#echo "hello" >>out_of_source_test.out_of_source_sample.approved.txt
#APPROVED_FILES_ROOT_DIR=. APPROVAL_TESTS_USE_REPORTER=TextDiffReporter ./out_of_source

popd
