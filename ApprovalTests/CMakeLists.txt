project(ApprovalTests CXX)
set(CMAKE_CXX_STANDARD 11)
add_library(${PROJECT_NAME}
        ApprovalTestsVersion.h
        ApprovalUtils.cpp
        ApprovalUtils.h
        Approvals.h
        ApprovalsMacroDefaults.h
        CombinationApprovals.h
        Storyboard.cpp
        Storyboard.h
        comparators/ComparatorDisposer.h
        comparators/ComparatorDisposer.cpp
        comparators/ComparatorFactory.h
        comparators/ComparatorFactory.cpp
        comparators/TextFileComparator.h
        comparators/TextFileComparator.cpp
        core/ApprovalComparator.h
        core/ApprovalException.h
        core/ApprovalException.cpp
        core/ApprovalNamer.h
        core/ApprovalWriter.h
        core/FileApprover.h
        core/FileApprover.cpp
        core/Options.h
        core/Options.cpp
        core/Reporter.h
        integrations/FrameworkIntegrations.cpp
        integrations/FrameworkIntegrations.h
        integrations/boost_test/BoostTestApprovals.h
        integrations/catch/Catch2Approvals.h
        integrations/catch/Catch2v3Approvals.h
        integrations/cpputest/CppUTestApprovals.h
        integrations/doctest/DocTestApprovals.h
        integrations/fmt/FmtApprovals.h
        integrations/fmt/FmtToString.h
        integrations/google/GoogleConfiguration.h
        integrations/google/GoogleConfiguration.cpp
        integrations/google/GoogleCustomizationsFactory.h
        integrations/google/GoogleCustomizationsFactory.cpp
        integrations/google/GoogleTestApprovals.h
        integrations/ut/UTApprovals.h
        launchers/CommandLauncher.h
        launchers/SystemLauncher.h
        launchers/SystemLauncher.cpp
        namers/ApprovalTestNamer.h
        namers/ApprovalTestNamer.cpp
        namers/DefaultNamerDisposer.h
        namers/DefaultNamerDisposer.cpp
        namers/DefaultNamerFactory.h
        namers/DefaultNamerFactory.cpp
        namers/ExistingFileNamer.h
        namers/ExistingFileNamer.cpp
        namers/FileNameSanitizerDisposer.h
        namers/FileNameSanitizerDisposer.cpp
        namers/FileNameSanitizerFactory.h
        namers/FileNameSanitizerFactory.cpp
        namers/HelpMessages.h
        namers/HelpMessages.cpp
        namers/NamerFactory.h
        namers/NamerFactory.cpp
        namers/SectionNameDisposer.h
        namers/SectionNameDisposer.cpp
        namers/SeparateApprovedAndReceivedDirectoriesNamer.h
        namers/SeparateApprovedAndReceivedDirectoriesNamer.cpp
        namers/SubdirectoryDisposer.h
        namers/SubdirectoryDisposer.cpp
        namers/TemplatedCustomNamer.h
        namers/TemplatedCustomNamer.cpp
        reporters/AutoApproveIfMissingReporter.h
        reporters/AutoApproveIfMissingReporter.cpp
        reporters/AutoApproveReporter.h
        reporters/AutoApproveReporter.cpp
        reporters/BlockingReporter.h
        reporters/BlockingReporter.cpp
        reporters/CIBuildOnlyReporter.h
        reporters/CIBuildOnlyReporter.cpp
        reporters/CIBuildOnlyReporterUtils.h
        reporters/CIBuildOnlyReporterUtils.cpp
        reporters/ClipboardReporter.h
        reporters/ClipboardReporter.cpp
        reporters/CombinationReporter.h
        reporters/CombinationReporter.cpp
        reporters/CommandReporter.h
        reporters/CommandReporter.cpp
        reporters/ConvertForCygwin.h
        reporters/ConvertForCygwin.cpp
        reporters/CrossPlatformReporters.h
        reporters/CrossPlatformReporters.cpp
        reporters/CustomReporter.h
        reporters/CustomReporter.cpp
        reporters/DefaultFrontLoadedReporter.h
        reporters/DefaultFrontLoadedReporter.cpp
        reporters/DefaultReporter.h
        reporters/DefaultReporter.cpp
        reporters/DefaultReporterDisposer.h
        reporters/DefaultReporterDisposer.cpp
        reporters/DefaultReporterFactory.h
        reporters/DefaultReporterFactory.cpp
        reporters/DiffInfo.h
        reporters/DiffInfo.cpp
        reporters/DiffPrograms.h
        reporters/DiffPrograms.cpp
        reporters/DiffReporter.h
        reporters/DiffReporter.cpp
        reporters/EnvironmentVariableReporter.cpp
        reporters/EnvironmentVariableReporter.h
        reporters/FirstWorkingReporter.h
        reporters/FirstWorkingReporter.cpp
        reporters/FrontLoadedReporterDisposer.h
        reporters/FrontLoadedReporterDisposer.cpp
        reporters/FrontLoadedReporterFactory.h
        reporters/FrontLoadedReporterFactory.cpp
        reporters/GenericDiffReporter.h
        reporters/GenericDiffReporter.cpp
        reporters/LinuxReporters.h
        reporters/LinuxReporters.cpp
        reporters/MacReporters.h
        reporters/MacReporters.cpp
        reporters/QuietReporter.h
        reporters/QuietReporter.cpp
        reporters/ReporterFactory.cpp
        reporters/ReporterFactory.h
        reporters/TextDiffReporter.h
        reporters/TextDiffReporter.cpp
        reporters/WindowsReporters.h
        reporters/WindowsReporters.cpp
        scrubbers/Scrubbers.h
        scrubbers/Scrubbers.cpp
        utilities/Blocker.h
        utilities/CartesianProduct.h
        utilities/DateUtils.cpp
        utilities/DateUtils.h
        utilities/EmptyFileCreatorByType.cpp
        utilities/EmptyFileCreatorByType.h
        utilities/EmptyFileCreatorDisposer.cpp
        utilities/EmptyFileCreatorDisposer.h
        utilities/EmptyFileCreatorFactory.cpp
        utilities/EmptyFileCreatorFactory.h
        utilities/ExceptionCollector.h
        utilities/ExceptionCollector.cpp
        utilities/FileUtils.h
        utilities/FileUtils.cpp
        utilities/FileUtilsSystemSpecific.h
        utilities/FileUtilsSystemSpecific.cpp
        utilities/Grid.h
        utilities/Grid.cpp
        utilities/MachineBlocker.h
        utilities/MachineBlocker.cpp
        utilities/Macros.h
        utilities/MoreHelpMessages.h
        utilities/MoreHelpMessages.cpp
        utilities/Path.cpp
        utilities/Path.h
        utilities/StringMaker.h
        utilities/StringUtils.h
        utilities/StringUtils.cpp
        utilities/SystemUtils.h
        utilities/SystemUtils.cpp
        utilities/WinMinGWUtils.h
        writers/ExistingFile.h
        writers/ExistingFile.cpp
        writers/StringWriter.h
        writers/StringWriter.cpp
        )
add_library(ApprovalTests::ApprovalTests ALIAS ApprovalTests)
target_include_directories(${PROJECT_NAME}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
        )
target_compile_options(${PROJECT_NAME} PUBLIC $<$<CXX_COMPILER_ID:MSVC>:/FC>)

if (("${CMAKE_GENERATOR}" MATCHES "Ninja") AND (${CMAKE_UNITY_BUILD}))
    # In case this is a Ninja Unity in-source build, disabling the
    # compile-time checking of __FILE__, to fix the compilation of our
    # Catch2 tests, and others which depend on __FILE__ - which then go on to pass,
    # even when built inside source trees.
    message(NOTICE "Ninja with Unity build detected: disabling unnecessary ApprovalTests compile-time check of __FILE__")
    target_compile_definitions(${PROJECT_NAME} PUBLIC APPROVAL_TESTS_DISABLE_FILE_MACRO_CHECK)
endif ()

# Install library
 install(TARGETS ${PROJECT_NAME}
         ARCHIVE)

 # Install headerfiles
 install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
         TYPE INCLUDE
         FILES_MATCHING
         PATTERN "*.h"
         PATTERN "*.hpp")

include(WarningsAsErrors)
