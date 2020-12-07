<!-- See the [v.10.5.1 milestone](https://github.com/approvals/ApprovalTests.cpp/milestone/__MILESTONE_NUMBER__?closed=1) for the full list of changes. -->

* **Breaking changes**
    * None
* **New features**
    * None
* **Bug fixes**
* **Other changes**
  * Update Boost.ut integration to work with latest version of that library.  
    (A change after Boost.ut v1.1.8 resulted in a build error - this is now fixed)
  * GitHub Actions CI build added for our Python code (#165)
  * VS2017 Debug x64 build of ApprovalTests.cpp.StarterProject gave "C1128: number of sections exceeded object file
    format limit: compile with
    /bigobj" ([ApprovalTests.cpp.StarterProject#16](https://github.com/approvals/ApprovalTests.cpp.StarterProject/issues/16))
  * Removed undocumented ability to verify `std::wstring` and `wchar_t*`. This gave compiler warnings on C++17 and above, and did not work on Visual Studio. (#154, which contains the deleted code for future reference)
