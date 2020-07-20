#include "ApprovalTests/comparators/ComparatorFactory.h"
#include "ApprovalTests/utilities/FileUtils.h"
#include "TextFileComparator.h"

namespace ApprovalTests
{
    ComparatorContainer& ComparatorFactory::comparators()
    {
        static ComparatorContainer allComparators;
        return allComparators;
    }

    ComparatorDisposer
    ComparatorFactory::registerComparator(const std::string& extensionWithDot,
                                          std::shared_ptr<ApprovalComparator> comparator)
    {
        return ComparatorDisposer(comparators(),
                                  extensionWithDot,
                                  getComparatorForFileExtensionWithDot(extensionWithDot),
                                  comparator);
    }

    std::shared_ptr<ApprovalComparator>
    ComparatorFactory::getComparatorForFile(const std::string& receivedPath)
    {
        const std::string fileExtension = FileUtils::getExtensionWithDot(receivedPath);
        return getComparatorForFileExtensionWithDot(fileExtension);
    }

    std::shared_ptr<ApprovalComparator>
    ComparatorFactory::getComparatorForFileExtensionWithDot(
        const std::string& fileExtensionWithDot)
    {
        auto iterator = comparators().find(fileExtensionWithDot);
        if (iterator != comparators().end())
        {
            return iterator->second;
        }
        return std::make_shared<TextFileComparator>();
    }
}
