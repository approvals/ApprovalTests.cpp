#ifndef APPROVALS_H
#define APPROVALS_H

#include <string>
#include <functional>
#include "FileApprover.h"
#include "reporters/DiffReporter.h"
#include "reporters/Reporter.h"
#include "namers/ApprovalTestNamer.h"

class Approvals
{
private:
    Approvals() {}
    ~Approvals() {}
public:
    static void verify( std::string contents,const Reporter& reporter = DiffReporter() )
    {
        StringWriter writer( contents );
        ApprovalTestNamer namer;
        FileApprover::verify(namer, writer, reporter);
    }

    template <typename T>
    static void verify(T contents, const Reporter& reporter = DiffReporter())
    {
        std::stringstream s;
        s << contents;
        verify(s.str(), reporter);
    }

    template <typename Iterator>
    static void verifyAll(std::string header,
                          const Iterator& start, const Iterator& finish,
                          std::function<void (typename Iterator::value_type, std::ostream&)> converter,
                          const Reporter& reporter = DiffReporter())
    {
        std::stringstream s;
        if( !header.empty())
        {
            s << header << "\n\n\n";
        }
        for (auto it = start; it != finish; ++it)
        {
            converter(*it, s);
            s << '\n';
        }
        verify(s.str(), reporter);
    }

    template <typename Container>
    static void verifyAll(std::string header,
                          const Container& list,
                          std::function<void (typename Container::value_type, std::ostream&)> converter,
                          const Reporter& reporter = DiffReporter())
    {
        verifyAll<typename Container::const_iterator>(header, list.begin(), list.end(), converter, reporter);
    }

    template <typename T>
    static void verifyAll(std::string header,
                          const std::vector<T>& list,
                          const Reporter& reporter = DiffReporter())
    {
        int i = 0;
        verifyAll<std::vector<T>>(header, list, [&](T e, std::ostream& s){s << "[" << i++ << "] = " << e;}, reporter);
    }

    template <typename T>
    static void verifyAll(const std::vector<T>& list,
                          const Reporter& reporter = DiffReporter())
    {
        verifyAll<T>("", list, reporter);
    }
};

#endif