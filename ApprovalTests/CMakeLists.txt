cmake_minimum_required(VERSION 3.8)
project(ApprovalTests CXX)
set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES
        ApprovalException.h
        Approvals.h
        ApprovalWriter.h
        Catch2Approvals.h
        FileApprover.h
        FileUtils.h
        Macros.h
        StringWriter.h
        SystemUtils.h
        CombinationApprovals.h
        comparers/ApprovalComparator.h
        comparers/TextFileComparator.h
        namers/ApprovalNamer.h
        namers/ApprovalTestNamer.h
        reporters/CommandLauncher.h
        reporters/ClipboardReporter.h
        reporters/Reporter.h 
        reporters/FirstWorkingReporter.h
        reporters/DiffReporter.h
        reporters/DiffPrograms.h
        reporters/DiffInfo.h
        reporters/WindowsReporters.h
        reporters/MacReporters.h
        reporters/LinuxReporters.h StringUtils.h reporters/GenericDiffReporter.h reporters/CommandReporter.h OkraApprovals.h
        GoogleTestApprovals.h
        reporters/SystemLauncher.h writers/ExistingFile.h writers/ExistingFile.h namers/ExistingFileNamer.h reporters/CombinationReporter.h)
add_library(${PROJECT_NAME} ${SOURCE_FILES} )
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
