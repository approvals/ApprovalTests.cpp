#ifndef APPROVALTESTS_CPP_BLOCKER_H
#define APPROVALTESTS_CPP_BLOCKER_H

class Blocker
{
public:
    virtual bool isBlockingOnThisMachine() const = 0;
};

#endif //APPROVALTESTS_CPP_BLOCKER_H
