#pragma once

#include <memory>
#include "ApprovalException.h"
#include "ApprovalTests/writers/StringWriter.h"
#include "Reporter.h"
#include "ApprovalTests/reporters/FrontLoadedReporterDisposer.h"
#include "ApprovalTests/core/ApprovalNamer.h"
#include "ApprovalComparator.h"
#include "ApprovalTests/comparators/ComparatorFactory.h"
#include "ApprovalTests/utilities/FileUtils.h"

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
                                       std::shared_ptr<ApprovalComparator> comparator)
        {
            return ComparatorFactory::registerComparator(extensionWithDot, comparator);
        }

        //! This overload is an implementation detail. To add a new comparator, use registerComparatorForExtension().
        static void verify(const std::string& receivedPath,
                           const std::string& approvedPath,
                           const ApprovalComparator& comparator)
        {
            if (!FileUtils::fileExists(approvedPath))
            {
                throw ApprovalMissingException(receivedPath, approvedPath);
            }

            if (!FileUtils::fileExists(receivedPath))
            {
                throw ApprovalMissingException(approvedPath, receivedPath);
            }

            if (!comparator.contentsAreEquivalent(receivedPath, approvedPath))
            {
                throw ApprovalMismatchException(receivedPath, approvedPath);
            }
        }

        static void verify(const std::string& receivedPath,
                           const std::string& approvedPath)
        {
            verify(receivedPath,
                   approvedPath,
                   *ComparatorFactory::getComparatorForFile(receivedPath));
        }

        static void
        verify(const ApprovalNamer& n, const ApprovalWriter& s, const Reporter& r)
        {
            std::string approvedPath = n.getApprovedFile(s.getFileExtensionWithDot());
            std::string receivedPath = n.getReceivedFile(s.getFileExtensionWithDot());
            s.write(receivedPath);
            try
            {
                verify(receivedPath, approvedPath);
                s.cleanUpReceived(receivedPath);
            }
            catch (const ApprovalException&)
            {
                reportAfterTryingFrontLoadedReporter(receivedPath, approvedPath, r);
                throw;
            }
        }

        static void reportAfterTryingFrontLoadedReporter(const std::string& receivedPath,
                                                         const std::string& approvedPath,
                                                         const Reporter& r)
        {
            auto tryFirst = FrontLoadedReporterFactory::getFrontLoadedReporter();
            if (!tryFirst->report(receivedPath, approvedPath))
            {
                r.report(receivedPath, approvedPath);
            }
        }
    };
}
