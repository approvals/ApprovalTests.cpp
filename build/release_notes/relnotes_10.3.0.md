<!-- See the [v.10.3.0 milestone](https://github.com/approvals/ApprovalTests.cpp/milestone/__MILESTONE_NUMBER__?closed=1) for the full list of changes. -->

* **Breaking changes**
    * None
* **New features**
    * Add `initializer_list` support to `Approvals::verifyAll()` (#152, thanks @alepez)  
    For example:
  ```cpp
        Approvals::verifyAll({10, 20, 30});
  ```

* **Bug fixes**
    * None
* **Other changes**
    * Overloads of `Approvals::verifyAll()` that previously only accepted `std::vector` now accept all container types (#152, thanks @alepez)
    * Better readability of the groups of member methods on Read the Docs, for example in [Approving Objects](https://approvaltestscpp.readthedocs.io/en/latest/api/approving.html) (#153)
