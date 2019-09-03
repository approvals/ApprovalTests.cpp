<a id="top"></a>

# Build Machines and Continuous Integration servers

In automated builds, if a file verification fails, there is no point opening up a graphical diff tool to show any errors. At best it is a waste of resources, and at worst, it may stop the build from completing.

If your build machine doesn't have any graphical tools, no action is required.

However, if your build machine *does* have any graphical diff tools installed, you will need to prevent Approvals from opening them on failure. The following Reporter features provide ways of doing this: 

* [Front Loaded Reporters](/doc/Reporters.md#front-loaded-reporters)
* [Blocking Reporters](/doc/Reporters.md#blocking-reporters)

---

[Back to User Guide](/doc/README.md#top)
