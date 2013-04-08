
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tests/igloo_self_test.h>
using namespace igloo;

Context(AContextWithAFailingSpec)
{
  
  void SetUp()
  {
    failing_context.SetName("FailingContext");
    FailingContext::callLog() = "";

    ContextRegistry<FailingContext>::CallSpec(failing_context, "AFailingSpec", &FailingContext::AFailingSpec, results);
  }

  Spec(FailingSpecShouldBeRegisteredAsFailed)
  {
    
    Assert::That(results.FailedTests(), HasLength(1));
    Assert::That(results.FailedTests(), Has().Exactly(1).EqualTo(FailedTestResult("FailingContext", "AFailingSpec", "This should fail")));    
  }

  Spec(SetUp_and_TearDown_should_be_called)
  {
    Assert::That(FailingContext::callLog(), Is().StartingWith("SetUp called.").And().EndingWith("TearDown called."));
  }
  
  struct FailingContext : public ContextProvider<FailingContext, ContextWithAttribute<void> >
  {
    void SetUp()
    {
      std::stringstream stm;
      stm << "SetUp called.";
      callLog() += stm.str();
    }

    void TearDown()
    {
      std::stringstream stm;
      stm << "TearDown called.";
      callLog() += stm.str();
    }

    Spec(AFailingSpec)
    {
      Assert::Failure("This should fail");
    }

    static std::string& callLog()
    {
      static std::string callLog;
      return callLog;
    }

  } failing_context;
  
  TestResults results;
};

Context(AContextWithAFailingTearDown)
{
  
  void SetUp()
  {
    failing_context.SetName("FailingContext");
  }

  Spec(SpecShouldBeRegisteredAsFailed)
  {
    ContextRegistry<FailingContext>::CallSpec(failing_context, "TrivialSpec", &FailingContext::TrivialSpec, results);
    
    Assert::That(results.FailedTests(), HasLength(1));
    Assert::That(results.FailedTests(), Has().Exactly(1).EqualTo(FailedTestResult("FailingContext", "TrivialSpec", "This should fail")));    
  }
  
  struct FailingContext : public ContextProvider<FailingContext, ContextWithAttribute<void> >
  {
    void TearDown()
    {
      Assert::Failure("This should fail");
    }
    
    Spec(TrivialSpec)
    {
    }
    
  } failing_context;
  
  TestResults results;
};

Context(a_context_that_throws_an_unknown_exception_during_set_up)
{
  struct ContextThatFailsDuringSetUp : public ContextProvider<ContextThatFailsDuringSetUp, ContextWithAttribute<void> >
  {
    void SetUp()
    {
      throw "unknown error";
    }

    Spec(a_spec)
    {
    }
  } failing_context;

  void SetUp()
  {
    failing_context.SetName("ContextThatFailsDuringSetUp");
  }

  Spec(exception_should_be_stored_in_test_result)
  {
    ContextRegistry<ContextThatFailsDuringSetUp>::CallSpec(failing_context, "a_spec", &ContextThatFailsDuringSetUp::a_spec, results);
    Assert::That(results.FailedTests(), Has().Exactly(1).EqualTo(FailedTestResult("ContextThatFailsDuringSetUp", "a_spec", "Caught unknown exception")));
  }

  TestResults results;
};

Context(a_context_that_throws_an_unknown_exception_during_test_run)
{
  struct ContextThatFailsDuringTestRun : public ContextProvider<ContextThatFailsDuringTestRun, ContextWithAttribute<void> >
  {
    Spec(a_spec)
    {
      throw "unknown error";
    }
  } failing_context;

  void SetUp()
  {
    failing_context.SetName("ContextThatFailsDuringTestRun");
  }

  Spec(exception_should_be_stored_in_test_result)
  {
    ContextRegistry<ContextThatFailsDuringTestRun>::CallSpec(failing_context, "a_spec", &ContextThatFailsDuringTestRun::a_spec, results);
    Assert::That(results.FailedTests(), Has().Exactly(1).EqualTo(FailedTestResult("ContextThatFailsDuringTestRun", "a_spec", "Caught unknown exception")));
  }

  TestResults results;
};

Context(a_context_that_throws_an_unknown_exception_during_tear_down)
{
  struct ContextThatFailsDuringTeardown : public ContextProvider<ContextThatFailsDuringTeardown, ContextWithAttribute<void> >
  {
    void TearDown()
    {
      throw "unknown error";
    }

    Spec(a_spec)
    {
    }
  } failing_context;

  void SetUp()
  {
    failing_context.SetName("ContextThatFailsDuringTeardown");
  }

  Spec(exception_should_be_stored_in_test_result)
  {
    ContextRegistry<ContextThatFailsDuringTeardown>::CallSpec(failing_context, "a_spec", &ContextThatFailsDuringTeardown::a_spec, results);
    Assert::That(results.FailedTests(), Has().Exactly(1).EqualTo(FailedTestResult("ContextThatFailsDuringTeardown", "a_spec", "Caught unknown exception")));
  }

  TestResults results;
};
