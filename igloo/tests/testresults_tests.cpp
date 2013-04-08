
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tests/igloo_self_test.h>
using namespace igloo;

struct HasSpecWithName
{
  HasSpecWithName(const std::string& expectedName) : expectedName_(expectedName)
  {
  }

  bool Matches(const FailedTestResult& actual) const
  {
    return actual.GetSpecName() == expectedName_;
  }

  bool Matches(const SucceededTestResult& actual) const
  {
    return actual.GetSpecName() == expectedName_;
  }

  std::string expectedName_;
};

std::ostream& operator<<(std::ostream& stm, const HasSpecWithName& matcher)
{
  stm << "TestResult for spec named " << matcher.expectedName_;
  return stm;
}

Context(An_empty_test_run)
{
  TestResults results;

  Spec(Number_of_tests_should_be_0)
  {
    Assert::That(results.NumberOfTestsRun(), Is().EqualTo(0));
  }

  Spec(Number_of_failed_tests_should_be_0)
  {
    Assert::That(results.NumberOfFailedTests(), Is().EqualTo(0));
  }

  Spec(Number_of_succeeded_tests_should_be_0)
  {
    Assert::That(results.NumberOfSucceededTests(), Is().EqualTo(0));
  }

  Context(One_failed_test)
  {
    void SetUp()
    {
      Results().AddResult(FailedTestResult("The context name", "A failing spec", "The error message"));
    }

    Spec(Number_of_tests_should_be_1)
    {
      Assert::That(Results().NumberOfTestsRun(), Is().EqualTo(1));
    }

    Spec(Number_of_failed_tests_should_be_1)
    {
      Assert::That(Results().NumberOfFailedTests(), Is().EqualTo(1));
    }

    Spec(Number_of_succeeded_tests_should_be_0)
    {
      Assert::That(Results().NumberOfSucceededTests(), Is().EqualTo(0));
    }

    Spec(The_correct_testresult_should_be_recorded)
    {
      Assert::That(Results().FailedTests(), Has().Exactly(1).EqualTo(FailedTestResult("The context name", "A failing spec", "The error message")));
    }

    TestResults& Results()
    {
      return Parent().results;
    }

    Context(One_failed_and_one_succeeded_tests)
    {
      void SetUp()
      {
        Results().AddResult(SucceededTestResult("The context name", "A succeeding spec"));
      }

      Spec(Number_of_tests_should_be_2)
      {
        Assert::That(Results().NumberOfTestsRun(), Is().EqualTo(2));
      }
      
      Spec(Number_of_failed_tests_should_be_1)
      {
        Assert::That(Results().NumberOfFailedTests(), Is().EqualTo(1));
      }

      Spec(Number_of_succeeded_tests_should_be_1)
      {
        Assert::That(Results().NumberOfSucceededTests(), Is().EqualTo(1));
      }

      Spec(The_correct_testresults_should_be_recorded)
      {
        Assert::That(Results().FailedTests(), Has().Exactly(1).Fulfilling(HasSpecWithName("A failing spec")));
        Assert::That(Results().SucceededTests(), Has().Exactly(1).Fulfilling(HasSpecWithName("A succeeding spec")));
      }

      TestResults& Results()
      {
        return Parent().Results();
      }
    };
  };
};
