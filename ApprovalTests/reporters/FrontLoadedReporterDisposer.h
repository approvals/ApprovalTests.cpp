#ifndef APPROVALTESTS_CPP_FRONTLOADEDREPORTERDISPOSER_H
#define APPROVALTESTS_CPP_FRONTLOADEDREPORTERDISPOSER_H

#include "DefaultFrontLoadedReporter.h"
#include "FrontLoadedReporterFactory.h"

namespace ApprovalTests {
//! Implementation detail of Approvals::useAsFrontLoadedReporter()
class APPROVAL_TESTS_NO_DISCARD FrontLoadedReporterDisposer
{
private:
    std::shared_ptr<Reporter> previous_result;
public:
    explicit FrontLoadedReporterDisposer(const std::shared_ptr<Reporter>& reporter)
    {
        previous_result = FrontLoadedReporterFactory::getFrontLoadedReporter();
        FrontLoadedReporterFactory::setFrontLoadedReporter(reporter);
    }

    ~FrontLoadedReporterDisposer()
    {
        FrontLoadedReporterFactory::setFrontLoadedReporter(previous_result);
    }

};
}

#endif //APPROVALTESTS_CPP_FRONTLOADEDREPORTERDISPOSER_H
