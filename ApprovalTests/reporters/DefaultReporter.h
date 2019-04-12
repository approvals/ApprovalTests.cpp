#ifndef APPROVALTESTS_CPP_DEFAULTREPORTER_H
#define APPROVALTESTS_CPP_DEFAULTREPORTER_H

#include "Reporter.h"
#include "DiffReporter.h"

#include <memory>
#include <vector>

class DefaultReporter : public Reporter
{
private:
//    using ReporterHandle = std::shared_ptr<Reporter>;
    using ReporterContainer = std::vector< std::shared_ptr<Reporter> >;
    APPROVAL_TESTS_MACROS_STATIC(ReporterContainer, defaultReporterContainer, DefaultReporter::createReporterContainer())
    
//    void ensureDefaultReporterCreated()
//    {
//        if (defaultReporterContainer()->empty())
//        {
//            defaultReporterContainer()->push_back( std::maker_shared<DiffReporter>());
//        }
//    }
    
    static ReporterContainer* createReporterContainer()
    {
        auto container = new ReporterContainer; 
        container->push_back( std::make_shared<DiffReporter>());
        return container;
    }

public:
    virtual bool report(std::string received, std::string approved) const override
    {
        return getDefaultReporter()->report(received, approved);
    }

    static std::shared_ptr<Reporter> getDefaultReporter()
    {
//        ensureDefaultReporterCreated();
        return defaultReporterContainer().at(0);
    }
    
    static void setDefaultReporter( const std::shared_ptr<Reporter>& reporter)
    {
//        ensureDefaultReporterCreated();
        defaultReporterContainer().at(0) = reporter;
    }

};

#endif //APPROVALTESTS_CPP_DEFAULTREPORTER_H
