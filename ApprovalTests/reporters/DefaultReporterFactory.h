#ifndef APPROVALTESTS_CPP_DEFAULTREPORTERFACTORY_H
#define APPROVALTESTS_CPP_DEFAULTREPORTERFACTORY_H

#include "ApprovalTests/core/Reporter.h"
#include "DiffReporter.h"

#include <memory>
#include <vector>

namespace ApprovalTests {
//! Implementation detail of Approvals::useAsDefaultReporter()
class DefaultReporterFactory
{
private:
    using ReporterContainer = std::vector< std::shared_ptr<Reporter> >;
    static ReporterContainer& defaultReporterContainer()
    {
        static ReporterContainer reporters = *createReporterContainer();
        return reporters;
    }
    
    static ReporterContainer* createReporterContainer()
    {
        auto container = new ReporterContainer;
        container->push_back( std::make_shared<DiffReporter>());
        return container;
    }

public:
    static std::shared_ptr<Reporter> getDefaultReporter()
    {
        return defaultReporterContainer().at(0);
    }
    
    static void setDefaultReporter( const std::shared_ptr<Reporter>& reporter)
    {
        defaultReporterContainer().at(0) = reporter;
    }

};
}

#endif //APPROVALTESTS_CPP_DEFAULTREPORTERFACTORY_H
