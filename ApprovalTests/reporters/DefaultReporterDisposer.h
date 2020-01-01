#ifndef APPROVALTESTS_CPP_DEFAULTREPORTERDISPOSER_H
#define APPROVALTESTS_CPP_DEFAULTREPORTERDISPOSER_H

#include "DefaultReporterFactory.h"

namespace ApprovalTests
{
    //! Implementation detail of Approvals::useAsDefaultReporter()
    class APPROVAL_TESTS_NO_DISCARD DefaultReporterDisposer
    {
    private:
        std::shared_ptr<Reporter> previous_result;

    public:
        explicit DefaultReporterDisposer(
            const std::shared_ptr<Reporter>& reporter)
        {
            previous_result = DefaultReporterFactory::getDefaultReporter();
            DefaultReporterFactory::setDefaultReporter(reporter);
        }

        ~DefaultReporterDisposer()
        {
            DefaultReporterFactory::setDefaultReporter(previous_result);
        }
    };
}

#endif //APPROVALTESTS_CPP_DEFAULTREPORTERDISPOSER_H
