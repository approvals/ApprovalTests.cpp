
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tests/igloo_self_test.h>
#include <memory>

using namespace igloo;

Context(DefaultTestResultsOutput_EmptyTestRun)
{
  std::auto_ptr<DefaultTestResultsOutput> output;
  std::stringstream resulting_stream;
  TestResults results;

  void SetUp()
  {
    output = std::auto_ptr<DefaultTestResultsOutput>(new DefaultTestResultsOutput(resulting_stream));
  }

  Spec(OutputsASummaryLineWithNoTests)
  {
    output->PrintResult(results);

    Assert::That(resulting_stream.str(), Is().StartingWith("Test run complete. 0 tests run, 0 succeeded, 0 failed."));
  }

  Context(DefaultTestResultsOutput_OneFailedTest_with_no_info_about_location_of_error)
  {
    void SetUp()
    {
      testResults().AddResult(FailedTestResult("A context name", "A spec name", "The error message"));
      Parent().output->PrintResult(Parent().results);
    }

    Spec(DisplaysOneFailedTestOnSummary)
    {
      Assert::That(resulting_output(), Has().Exactly(1).StartingWith("Test run complete. 1 tests run, 0 succeeded, 1 failed."));
    }

    Spec(DisplaysErrorTextForFailedTestCorrectly)
    {
      Assert::That(resulting_output(), Is().StartingWith("A context name::A spec name failed:\nThe error message"));
    }

    TestResults& testResults() 
    {
      return Parent().results;
    }
    
    std::string resulting_output() 
    {
      return Parent().resulting_stream.str();
    }
  };

  Context(DefaultTestResultsOutput_one_failed_test_with_information_about_origin_of_assertion)
  {
    void SetUp()
    {
      testResults().AddResult(FailedTestResult("A context name", "A spec name", "The error message", "filewithfailure.cpp", 342));
      Parent().output->PrintResult(Parent().results);
    }

    Spec(DisplaysOneFailedTestOnSummary)
    {
      Assert::That(resulting_output(), Has().Exactly(1).StartingWith("Test run complete. 1 tests run, 0 succeeded, 1 failed."));
    }

    Spec(DisplaysErrorTextForFailedTestCorrectly)
    {
      Assert::That(resulting_output(), Is().StartingWith("A context name::A spec name failed:\nfilewithfailure.cpp(342): Assertion failed.\nThe error message"));
    }

    TestResults& testResults() 
    {
      return Parent().results;
    }
    
    std::string resulting_output() 
    {
      return Parent().resulting_stream.str();
    }
  };
};
