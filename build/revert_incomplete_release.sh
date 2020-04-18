#!/bin/sh

git checkout -- \
  version.ini \
  ../ApprovalTests/ApprovalTestsVersion.h \
  ../doc/Features.md \
  ../doc/mdsource/Features.source.md \
  ../mdsource/README.source.md \
  ../README.md

# TODO Un-stage and remove build/release_notes/relnotes_9.0.0.md
# TODO Revert changes to starter project
# TODO Revert changes to conan-center-index fork - including deleting any newly-created branches
