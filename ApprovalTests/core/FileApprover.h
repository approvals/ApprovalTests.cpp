#pragma once

#include "ApprovalTests/writers/StringWriter.h"
#include "ApprovalTests/core/Reporter.h"
#include "ApprovalTests/core/ApprovalNamer.h"
#include "ApprovalTests/core/ApprovalComparator.h"
#include "ApprovalTests/comparators/ComparatorFactory.h"

#include <memory>
#include <functional>

namespace ApprovalTests
{
    class FileApprover
    {

    public:
        FileApprover() = default;

        ~FileApprover() = default;

        /*! \brief Register a custom comparater, which will be used to compare approved
         *         and received files with the given extension.
         *
         * @param extensionWithDot A file extention, such as ".jpg"
         * @param comparator <tt>std::shared_ptr</tt> to a ApprovalTests::ApprovalComparator
         *                   instance
         * @return A "Disposable" object. The caller should hold on to this object.
         *         When it is destroyed, the customisation will be reversed.
         *
         * \see For more information, see
         *      \userguide{CustomComparators,Custom Comparators}
         */
        static ComparatorDisposer
        registerComparatorForExtension(const std::string& extensionWithDot,
                                       std::shared_ptr<ApprovalComparator> comparator);

        //! This overload is an implementation detail. To add a new comparator, use registerComparatorForExtension().
        static void verify(const std::string& receivedPath,
                           const std::string& approvedPath,
                           const ApprovalComparator& comparator);

        static void verify(const std::string& receivedPath,
                           const std::string& approvedPath);

        static void
        verify(const ApprovalNamer& n, const ApprovalWriter& s, const Reporter& r);

        static void reportAfterTryingFrontLoadedReporter(const std::string& receivedPath,
                                                         const std::string& approvedPath,
                                                         const Reporter& r);

        using TestPassedNotification = std::function<void()>;
        static void setTestPassedNotification(TestPassedNotification notification);
        static void notifyTestPassed();

    private:
        static TestPassedNotification testPassedNotification_;
    };
}
