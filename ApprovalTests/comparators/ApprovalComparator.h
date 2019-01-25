#ifndef APPROVALTESTS_CPP_APPROVALCOMPARATOR_H
#define APPROVALTESTS_CPP_APPROVALCOMPARATOR_H

#include <string>

using ApprovalComparator = bool (*)(std::string receivedPath,
                                    std::string approvedPath);

#endif //APPROVALTESTS_CPP_APPROVALCOMPARATOR_H
