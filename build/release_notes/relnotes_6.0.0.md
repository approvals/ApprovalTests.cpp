* **Breaking changes**
    * If you pass in a reporter to CombinationApprovals::verifyAllCombinations(), the argument order has changed: see [Passing in a Reporter](/doc/TestingCombinations.md#passing-in-a-reporter).
    * FileApprover::registerComparator() has been renamed to  FileApprover::registerComparatorForExtension(), and now returns a [Disposable Object](/doc/DisposableObjects.md#top). (#42)
* **New features**
    * Support for [Existing Catch Project - with your main()](/doc/UsingCatch.md#existing-project---with-your-main) (#36)
    * CombinationApprovals::verifyAllCombinations() now handles more than 9 parameters in the function being tested. (#33)
    * [Custom Comparators](/doc/CustomComparators.md#top) can be reverted (#42)
* **Bug fixes**
    * None
* **Other changes**
    * doctest 2.3.5 is now supported (2.3.4 remains supported)
