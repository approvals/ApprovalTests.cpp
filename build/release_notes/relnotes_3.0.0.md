* **Breaking changes**
    * Some virtual methods in the following classes have been renamed to begin with a lower-case letter:
        * ApprovalWriter
        * CommandLauncher 
        * Reporter
    * ApprovalWriter's getFileExtension() has been renamed to getFileExtensionWithDot()
    * Any custom implementations of these interfaces will need to be updated
* **New features**
    * Allow registration of custom file comparators by file extension: see ApprovalComparator and FileApprover::registerComparator()
* **Bug fixes**
    * CombinationApprovals now uses any supplied Reporter
    * Fixed compilation on some Windows builds
    * Tests can now distinguish between types of failure, by catching ApprovalMissingException or ApprovalMismatchException
* **Other changes**
    * Added Apache 2.0 license

