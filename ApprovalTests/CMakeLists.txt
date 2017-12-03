cmake_minimum_required(VERSION 3.8)
project(ApprovalTests CXX)
set(SOURCE_FILES
        ApprovalTests.h
        Catch2Approvals.h
        FileUtils.h
        Macros.h)
add_library(ApprovalTests ${SOURCE_FILES} )