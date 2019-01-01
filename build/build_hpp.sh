#!/bin/sh
VERSION="v.2.1.0"
cd ../ApprovalTests
java -jar ../build/SingleHpp.v.0.0.2.jar ../build/releases/ApprovalTests.$VERSION.hpp

cp ../build/releases/ApprovalTests.$VERSION.hpp ../../ApprovalTests.Cpp.StarterProject/lib
