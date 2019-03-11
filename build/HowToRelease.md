# How To Release

## Update ApprovalTests.cpp

* Check that the builds are passing: https://github.com/approvals/ApprovalTests.cpp/commits/master
* Determine the semantic version number
* Update the version number in `build_hpp.sh`
* Run `build_hpp.sh`
* Write summary of changes since last release 
* Upload the .hpp to releases - call the release `Single Hpp File`
* Change the version numbers in `build_hpp.sh` to reflect the next version
* Commit and push

## Update ApprovalTests.cpp.StarterProject

* Check that the starter project builds
* Commit and push

## Other stuff

* Tweet the release
#ApprovalTests.cpp v3.1.0 released, now with converter-based Approvals::verify(object, lambda_converter) overload!
https://github.com/approvals/ApprovalTests.cpp/releases/tag/v.3.1.0 
or try the starter project: https://github.com/approvals/ApprovalTests.cpp.StarterProject
Thanks @LlewellynFalco!