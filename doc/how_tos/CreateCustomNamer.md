<a id="top"></a>

# How to Create a Custom Namer - NOT IMPLEMENTED YET!

toc

## Overview

Warning - this is NOT IMPLEMENTED YET!

The easiest way to create a custom namer is by modifying the parts of CustomizableNamer.

CustomizableNamer has two main methods:

* `getApprovedFile(std::string extensionWithDot)`
This works by composing:
`{TestFolderForApproved}`/`{RelativePathOfSourceDirectoryFromSourceRootForApproved}`/`{FileNameAndTestName}`.approved.`{FileExtension}`

* `getReceivedFile(std::string extensionWithDot)`
This works by composing:
`{TestFolderForReceived}`/`{RelativePathOfSourceDirectoryFromSourceRootForReceived}`/`{FileNameAndTestName}`.received.`{FileExtension}`

## Overriding Parts

Both the getApprovedFile and getReceivedFile methods can be overridden, as well as any of the composable parts. By default, anything with a for received/apprroved simply calls the base.

For example:

```cpp
auto myNamer = CustomizableNamer()
    .withTestFolder([]{return "C:/ApprovalFiles";})
    .withTestFolderForReceived([]{return getTestFolder() + "/received"});

Approvals::verify("Hello World", Options().withNamer(myNamer));
```

{TestFolder}/{RelativePathOfSourceDirectoryFromSourceRoot}/{FileNameAndTestName}.approved.{FileExtension}

{TestFolder}/{ReceivedOrApproved}/{RelativePathOfSourceDirectoryFromSourceRoot}/{SourceFileName}-{SectionNames}.{FileExtension}

---

[Back to User Guide](/doc/README.md#top)
