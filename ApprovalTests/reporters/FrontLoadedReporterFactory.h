#ifndef APPROVALTESTS_CPP_FRONTLOADEDREPORTERFACTORY_H
#define APPROVALTESTS_CPP_FRONTLOADEDREPORTERFACTORY_H

#include "Reporter.h"
#include "DefaultFrontLoadedReporter.h"
#include "../Macros.h"

#include <vector>
#include <memory>

namespace ApprovalTests {
namespace Detail {
//! Implementation detail of Approvals::useAsFrontLoadedReporter()
class FrontLoadedReporterFactory
{
    using ReporterContainer = std::vector< std::shared_ptr<Reporter> >;
    APPROVAL_TESTS_MACROS_STATIC(ReporterContainer, frontLoadedReporterContainer, FrontLoadedReporterFactory::createReporterContainer())

    static ReporterContainer* createReporterContainer()
    {
        auto container = new ReporterContainer;
        container->push_back( std::make_shared<DefaultFrontLoadedReporter>());
        return container;
    }

public:
    static std::shared_ptr<Reporter> getFrontLoadedReporter()
    {
        return frontLoadedReporterContainer().at(0);
    }

    static void setFrontLoadedReporter( const std::shared_ptr<Reporter>& reporter)
    {
        frontLoadedReporterContainer().at(0) = reporter;
    }
};
}
}

#endif //APPROVALTESTS_CPP_FRONTLOADEDREPORTERFACTORY_H
