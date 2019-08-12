* **Breaking changes**
    * `CombinationApprovals::verifyAllCombinations()` no longer requires the template types to be specified. The changes to allow this have changed the template parameters, so it will cause compilation failures in existing code until they are deleted.   
To change the code, simply delete the `<....>` from your call. For example:

```diff
- CombinationApprovals::verifyAllCombinations<std::vector<std::string>, std::string>(
+ CombinationApprovals::verifyAllCombinations(
    [](std::string s){return s + "!";}, words);
```

* **New features**
    * Better support for doctest - this requires doctest 2.4 - currently in beta.
* **Bug fixes**
    * None
* **Other changes**
    * None
