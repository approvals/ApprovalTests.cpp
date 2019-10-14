#ifndef APPROVALTESTS_CPP_COMPARATORFACTORY_H
#define APPROVALTESTS_CPP_COMPARATORFACTORY_H

#include <memory>
#include "ApprovalTests/core/ApprovalComparator.h"
#include "ApprovalTests/comparators/TextFileComparator.h"
#include "ApprovalTests/comparators/ComparatorDisposer.h"
#include "ApprovalTests/utilities/FileUtils.h"

namespace ApprovalTests {

class ComparatorFactory {
private:
    static ComparatorContainer &comparators() {
        static ComparatorContainer allComparators;
        return allComparators;
    }

public:
    static ComparatorDisposer
    registerComparator(const std::string &extensionWithDot, std::shared_ptr<ApprovalComparator> comparator) {
        return ComparatorDisposer(comparators(), extensionWithDot,
                                  getComparatorForFileExtensionWithDot(extensionWithDot),
                                  comparator);
    }

    static std::shared_ptr<ApprovalComparator> getComparatorForFile(const std::string &receivedPath) {
        const std::string fileExtension = FileUtils::getExtensionWithDot(receivedPath);
        return getComparatorForFileExtensionWithDot(fileExtension);
    }

    static std::shared_ptr<ApprovalComparator>
    getComparatorForFileExtensionWithDot(const std::string &fileExtensionWithDot) {
        auto iterator = comparators().find(fileExtensionWithDot);
        if (iterator != comparators().end()) {
            return iterator->second;
        }
        return std::make_shared<TextFileComparator>();
    }
};

}

#endif //APPROVALTESTS_CPP_COMPARATORFACTORY_H
