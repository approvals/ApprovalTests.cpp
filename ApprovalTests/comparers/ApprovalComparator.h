#ifndef APPROVALTESTS_CPP_APPROVALCOMPARER_H
#define APPROVALTESTS_CPP_APPROVALCOMPARER_H

#include <string>

using ApprovalComparator = bool (*)(std::string receivedPath,
                                    std::string approvedPath);

#endif //APPROVALTESTS_CPP_APPROVALCOMPARER_H
