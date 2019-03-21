#ifndef APPROVALTESTS_CPP_SUBDIRECTORYDISPOSER_H
#define APPROVALTESTS_CPP_SUBDIRECTORYDISPOSER_H

#include "ApprovalTestNamer.h"

#include <string>

class SubdirectoryDisposer
{
public:
    explicit SubdirectoryDisposer(std::string subdirectory)
    {
        ApprovalTestNamer::getCurrentTest().subdirectory = subdirectory;

    }

    ~SubdirectoryDisposer()
    {
        ApprovalTestNamer::getCurrentTest().subdirectory = "";
    }
};

#endif //APPROVALTESTS_CPP_SUBDIRECTORYDISPOSER_H
