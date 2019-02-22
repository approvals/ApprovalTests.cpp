# How To Release

## Update ApprovalTests.cpp

* Change the version number in `build_hpp.sh`
* Run `build_hpp.sh`
* Write summary of changes since last release 
* Upload the .hpp to releases - call the release `Single Hpp File`
* Change the version numbers in `build_hpp.sh` to reflect the next version

## Update ApprovalTests.cpp.StarterProject

* Update version number in `ApprovalTests.hpp`
* Delete the previous release .hpp
* Update version number on line 156 in filename visual-studio-2017/StarterProject.vcxproj
* Commit and push

## Other stuff

* Tweet the release