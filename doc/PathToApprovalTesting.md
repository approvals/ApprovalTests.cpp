<a id="top"></a>

# The Path to Approval Testing

<!-- toc -->
<!-- endToc -->

You are undoubtedly doing some form of Approval testing already. The most basic form would be writing `REQUIRE(42 == 6 * 9)`, then running it, getting the result `42 != 54` and then changing the code to say `REQUIRE(54 == 6 * 9)`.

This is the path that we commonly see, as people move in to Approval Tests:

* Verify numbers
    * Have lots of numbers, like an array
* Strings - turn the array of numbers in to a string
    * Those strings become long
* Files - Golden Master
    * Managing them - coming up with names
* Some sort of naming convention
* Can be hard to understand what's in the files
    * Start using diff tools
* Start creating custom methods for the things you are testing
    * verifyThing

---

[Back to User Guide](/doc/README.md#top)
