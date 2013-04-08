
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tests/igloo_self_test.h>

using namespace igloo;

class NullTestResultsOutput : public TestResultsOutput
{
    public:
      void PrintResult(const TestResults&) const 
      {
      }
};

class FakeTestListener : public TestListener
{
  public:
    void TestRunStarting()
    {
      callLog += "TestRunStarting\n";
    }

    void TestRunEnded(const TestResults& results)
    {
      std::stringstream stm;
      stm << "TestRunEnded called with " << results.NumberOfTestsRun() << " tests run" << std::endl;
      callLog += stm.str();
    }

    void ContextRunStarting(const ContextBase& context)
    {
      std::stringstream stm;
      stm << "ContextRunStarting called for context '" << context.Name() << "'" << std::endl;
      stm << "ContextRunStarting called with attribute '" << context.GetAttribute("attribute name") << "'" << std::endl;
      callLog += stm.str();
    }

    void ContextRunEnded(const ContextBase& context)
    {
      std::stringstream stm;
      stm << "ContextRunEnded called for context '" << context.Name() << "'" << std::endl;
      stm << "ContextRunEnded called with attribute '" << context.GetAttribute("attribute name") << "'" << std::endl;
      callLog += stm.str();
    }

    void SpecRunStarting(const ContextBase& context, const std::string& name)
    {
      std::stringstream stm;
      stm << "SpecRunStarting called for context '" << context.Name() << "' and spec '" << name << "'" << std::endl;
      callLog += stm.str();
    }

    void SpecSucceeded(const ContextBase& context, const std::string& name)
    {
      std::stringstream stm;
      stm << "SpecSucceeded called for context '" << context.Name() << "' and spec '" << name << "'" << std::endl;
      callLog += stm.str();
    }

    void SpecFailed(const ContextBase& context, const std::string& name)
    {
      std::stringstream stm;
      stm << "SpecFailed called for context '" << context.Name() << "' and spec '" << name << "'" << std::endl;
      callLog += stm.str();
    }

    std::string callLog;
};

class FakeContextRunner : public BaseContextRunner
{
  public:
    FakeContextRunner() : BaseContextRunner("ContextName") {}
    virtual void RunContext(TestResults& results, TestListener&) const
    {
      TestResultFactory factory(ContextName(), "SpecName");
      results.AddResult(factory.CreateSuccessful());
    }
};

Context(registering_a_test_listener)
{
  NullTestResultsOutput nullOutput;
  std::auto_ptr<TestRunner> runner;
  TestRunner::ContextRunners contextRunners;
  FakeTestListener listener;
  FakeContextRunner contextRunner;

  void SetUp()
  {
    runner = std::auto_ptr<TestRunner>(new TestRunner(nullOutput));
    runner->AddListener(&listener);

    contextRunners.push_back(&contextRunner);
  }

  Spec(a_callback_is_made_when_the_test_run_starts)
  {
    runner->Run(contextRunners);

    AssertThat(listener.callLog, Has().Exactly(1).EqualTo("TestRunStarting"));
  }

  Spec(a_callback_is_made_when_the_test_run_ends)
  {
    runner->Run(contextRunners);

    AssertThat(listener.callLog, Has().Exactly(1).EqualTo("TestRunEnded called with 1 tests run"));
  }
};

Context(a_registered_context)
{
  struct ContextToRun : public ContextProvider<ContextToRun, ContextWithAttribute<void> >
  {
    ContextAttribute("attribute name", "attribute value")

    Spec(SucceedingSpec)
    {
      Assert::That(true);
    }

    Spec(FailingSpec)
    {
      Assert::That(false);
    }
  };

  void SetUp()
  {
    ContextRegistry<ContextToRun>::RegisterSpec("SucceedingSpec", &ContextToRun::SucceedingSpec);
    ContextRegistry<ContextToRun>::Run<ContextToRun>("ContextToRun", testResults, testListener);
  }

  void TearDown()
  {
    ContextRegistry<ContextToRun>::ClearRegisteredSpecs();
  }

  Spec(ContextRunStarting_is_called)
  {
    AssertThat(testListener.callLog, Has().Exactly(1).EqualTo("ContextRunStarting called for context 'ContextToRun'"));
  }

  Spec(ContextRunStarting_is_called_with_attribute)
  {
    AssertThat(testListener.callLog, Has().Exactly(1).EqualTo("ContextRunStarting called with attribute 'attribute value'"));
  }

  Spec(ContextRunEnded_is_called)
  {
    AssertThat(testListener.callLog, Has().Exactly(1).EqualTo("ContextRunEnded called for context 'ContextToRun'"));
  }

  Spec(ContextRunEnded_is_called_with_attribute)
  {
    AssertThat(testListener.callLog, Has().Exactly(1).EqualTo("ContextRunEnded called with attribute 'attribute value'"));
  }

  Spec(SpecRunStarting_is_called)
  {
    AssertThat(testListener.callLog, Has().Exactly(1).EqualTo("SpecRunStarting called for context 'ContextToRun' and spec 'SucceedingSpec'"));
    AssertThat(testListener.callLog, Has().Exactly(1).EqualTo("SpecRunStarting called for context 'ContextToRun' and spec 'FailingSpec'"));
  }

  Spec(SpecSucceeded_is_called)
  {
    AssertThat(testListener.callLog, Has().Exactly(1).EqualTo("SpecSucceeded called for context 'ContextToRun' and spec 'SucceedingSpec'"));
  }

  Spec(SpecFailed_is_called)
  {
    AssertThat(testListener.callLog, Has().Exactly(1).EqualTo("SpecFailed called for context 'ContextToRun' and spec 'FailingSpec'"));
  }

  FakeTestListener testListener;
  TestResults testResults;
};
