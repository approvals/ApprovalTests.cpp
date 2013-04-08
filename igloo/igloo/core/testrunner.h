
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef IGLOO_TESTRUNNER_H
#define IGLOO_TESTRUNNER_H

#include <igloo/core/testresult.h>
#include <igloo/core/testresults.h>
#include <igloo/core/testlisteners/minimalprogresstestlistener.h>

namespace igloo {

  class TestRunner 
  {
    public:
      typedef std::list<BaseContextRunner*> ContextRunners;

      static int RunAllTests()
      {
        DefaultTestResultsOutput output;
        TestRunner runner(output);

        MinimalProgressTestListener progressOutput;
        runner.AddListener(&progressOutput);

        return runner.Run();
      }


      TestRunner(const TestResultsOutput& output) 
        : output_(output)
      {}

      int Run(const ContextRunners& runners)
      {
        TestResults results;

        listenerAggregator_.TestRunStarting();

        for (ContextRunners::const_iterator it = runners.begin(); it != runners.end(); it++)
        {
          BaseContextRunner* contextRunner = *it;
          contextRunner->Run(results, listenerAggregator_);
        }

        listenerAggregator_.TestRunEnded(results);

        output_.PrintResult(results);
        return results.NumberOfFailedTests();
      }

      int Run()
      {
        int numberOfFailedTests = Run(RegisteredRunners());
        CleanUpRunners();
        return numberOfFailedTests;
      }


      template <typename ContextRunnerType>
        static void RegisterContext(const std::string& name)
        {
          if(!ContextIsRegistered(name))
          {
            ContextRunnerType* contextRunner = 0;

            try
            {
              // Must add runner first...
              contextRunner = new ContextRunnerType(name);
              TestRunner::RegisteredRunners().push_back(contextRunner);

              // ... and then instantiate context, because context ctor calls this method again,
              // possibly for the same context, depending on inheritance chain.
              contextRunner->InstantiateContext();
            }
            catch (...)
            {
              delete contextRunner;
              throw;
            }
          }
        }

      void AddListener(TestListener* listener)
      {
        listenerAggregator_.AddListener(listener);
      }

    private:
      static void CleanUpRunners()
      {
        while(!RegisteredRunners().empty())
        {
          delete RegisteredRunners().front();
          RegisteredRunners().pop_front();
        }
      }

      static bool ContextIsRegistered(const std::string& name)
      {
        for (ContextRunners::const_iterator it = RegisteredRunners().begin(); it != RegisteredRunners().end(); ++it)
        {
          if((*it)->ContextName() == name)
          {
            return true;
          }
        }

        return false;
      }

      static TestRunner::ContextRunners& RegisteredRunners()
      {
        static TestRunner::ContextRunners contextRunners;
        return contextRunners;
      }

    private:
      const TestResultsOutput& output_;
      TestListenerAggregator listenerAggregator_;
  };
}

#endif // IGLOO_TESTRUNNER_H
