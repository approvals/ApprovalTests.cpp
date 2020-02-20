<a id="top"></a>

# Build Machines and Continuous Integration servers

In automated builds, if a file verification fails, there is no point opening up a graphical diff tool to show any errors. At best it is a waste of resources, and at worst, it may stop the build from completing.

So by default, Approval tests will never launch any graphical reporters on supported CI machines. To do this, we use [Front Loaded Reporters](/doc/Reporters.md#front-loaded-reporters).

Supported CI systems:

snippet: supported_ci_systems

The CI detection is based on environment variables, so it may also just work on other systems that we are unaware of:

snippet: supported_ci_env_vars

Or you may be able to set one of these environment variables in the configuration of your CI system, to tell Approval Tests it's running under CI. 

However, if your CI system is not supported, and you want to create a custom CI reporter, we suggest you start by looking at [CIBuildOnlyReporter](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/reporters/CIBuildOnlyReporter.h).


---

[Back to User Guide](/doc/README.md#top)
