#ifndef APPROVALTESTS_CPP_SUBDIRECTORYDISPOSER_H
#define APPROVALTESTS_CPP_SUBDIRECTORYDISPOSER_H

#include "ApprovalTestNamer.h"

#include <string>

namespace ApprovalTests {
namespace Detail {
//! Implementation detail of Approvals::useApprovalsSubdirectory()
class APPROVAL_TESTS_NO_DISCARD SubdirectoryDisposer
{
private:
    std::string previous_result;
public:
    explicit SubdirectoryDisposer(std::string subdirectory)
    {
        previous_result = ApprovalTestNamer::testConfiguration().subdirectory;
        ApprovalTestNamer::testConfiguration().subdirectory = subdirectory;
    }

    ~SubdirectoryDisposer()
    {
        ApprovalTestNamer::testConfiguration().subdirectory = previous_result;
    }
};
}
}

#endif //APPROVALTESTS_CPP_SUBDIRECTORYDISPOSER_H
