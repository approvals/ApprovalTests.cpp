<a id="top"></a>

# How to Create a Custom Namer

toc

## Overview

The easiest way to create a custom namer is to use a `TemplatedCustomNamer`.

Here is an example:

snippet: templated_custom_namer_example

## Supported tags

snippet: custom_namer_tags

##  

```cpp
auto myNamer = CustomizableNamer()
    .withTestFolder([]{return "C:/ApprovalFiles";})
    .withTestFolderForReceived([]{return getTestFolder() + "/received"});

Approvals::verify("Hello World", Options().withNamer(myNamer));
```


---

[Back to User Guide](/doc/README.md#top)
