<!-- See the [v.10.13.0 milestone](https://github.com/approvals/ApprovalTests.cpp/milestone/__MILESTONE_NUMBER__?closed=1) for the full list of changes. -->

* **Breaking changes**
    * If you are building against the Catch2v2 in the ApprovalTests repository: The CMake library target name changed from `Catch2::Catch2` to `Catch2v2::Catch2v2`
* **New features**
    * Add support for [Catch2 v3](/doc/UsingCatch.md)
    * Added CrossPlatformReporters::VSCode - Launches via the [VSCode command line interface](https://code.visualstudio.com/docs/setup/mac). Requires `code` to be in your PATH.
* **Bug fixes**
    * None
* **Other changes**
    * Remove mingw `getenv_s()` declaration workaround
