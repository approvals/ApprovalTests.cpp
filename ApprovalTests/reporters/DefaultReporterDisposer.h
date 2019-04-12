#ifndef APPROVALTESTS_CPP_DEFAULTREPORTERDISPOSER_H
#define APPROVALTESTS_CPP_DEFAULTREPORTERDISPOSER_H

#include "DefaultReporter.h"

class DefaultReporterDisposer
{
private:
    std::shared_ptr<Reporter> previous_result;
public:
    explicit DefaultReporterDisposer(const std::shared_ptr<Reporter>& reporter)
    {
        previous_result = DefaultReporter::getDefaultReporter();
        DefaultReporter::setDefaultReporter(reporter);
    }

    ~DefaultReporterDisposer()
    {
        DefaultReporter::setDefaultReporter(previous_result);
    }
};

#endif //APPROVALTESTS_CPP_DEFAULTREPORTERDISPOSER_H
