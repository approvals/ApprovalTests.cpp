
//          Copyright Bertrand Cachet 2012
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tests/igloo_self_test.h>
#include <memory>

using namespace igloo;

Context(XUnitResultsOutput_EmptyTestRun)
{
  std::auto_ptr<XUnitResultsOutput> output;
  std::stringstream resulting_stream;
  TestResults results;
  
  void SetUp()
  {
    output = std::auto_ptr<XUnitResultsOutput>(new XUnitResultsOutput(resulting_stream));
  }

  Spec(xml_output_should_content_testsuite_tag_with_tests_attr_set_to_0)
  {
    output->PrintResult(results);
    Assert::That(resulting_stream.str(), Is().Containing("<testsuite name=\"Igloo\" tests=\"0\" errors=\"0\" failures=\"0\"/>"));
  }

  Context(XUnitResultsOutput_one_failed_test_with_no_location_information)
  {
    void SetUp()
    {
      testResults().AddResult(FailedTestResult("A context name", "A failing spec", "The error message"));
      Parent().output->PrintResult(Parent().results);
    }

    Spec(xml_output_should_content_testsuite_tag_with_test_attr_set_to_1_and_failures_attr_set_to_1)
    {
      AssertThat(resulting_output(), Is().Containing("<testsuite name=\"Igloo\" tests=\"1\" errors=\"0\" failures=\"1\">"));
    }

    Spec(xml_output_should_content_testcase_with_failure_tag)
    {
      AssertThat(resulting_output(), Is().Containing("<testcase classname=\"A context name\" name=\"A failing spec\" time=\"0\">"));
      AssertThat(resulting_output(), Is().Containing("<failure message=\"The error message\"/>"));
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

  Context(XUnitResultsOutput_one_failed_test_and_one_succeeded_test)
  {
    void SetUp()
    {
      testResults().AddResult(FailedTestResult("A context name", "A failing spec", "The error message"));
      testResults().AddResult(SucceededTestResult("A context name", "A successful spec"));
      Parent().output->PrintResult(Parent().results);
    }

    Spec(xml_output_should_content_testsuite_tag_with_test_attr_set_to_2_and_failures_attr_set_to_1)
    {
      AssertThat(resulting_output(), Is().Containing("<testsuite name=\"Igloo\" tests=\"2\" errors=\"0\" failures=\"1\">"));
    }

    Spec(xml_output_should_content_two_testcase_nested_inside_testsuite)
    {
      AssertThat(resulting_output(), Is().Containing("<testcase classname=\"A context name\" name=\"A failing spec\" time=\"0\"><failure message=\"The error message\"/></testcase><testcase classname=\"A context name\" name=\"A successful spec\" time=\"0\"/>"));
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


  Context(XUnitResultOutput_one_failed_test_with_information_about_location_of_assertion)
  {
    void SetUp()
    {
      testResults().AddResult(FailedTestResult("A context name", "A failing spec", "The error message", "filename.cpp", 23));
      Parent().output->PrintResult(Parent().results);
    }

    Spec(xml_output_contains_one_testcase_tag_with_failure_tag)
    {
      AssertThat(resulting_output(), Is().Containing("<testcase classname=\"A context name\" name=\"A failing spec\" time=\"0\">"));
      AssertThat(resulting_output(), Is().Containing("<failure message="));
    }

    Spec(it_displays_error_text_for_failed_spec_with_location_information)
    {
      AssertThat(resulting_output(), Is().Containing("<failure message=\"filename.cpp(23): assertion failed error: The error message\"/>"));
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
