#ifndef APPROVALTESTS_CPP_OKRAAPPPROVALS_H
#define APPROVALTESTS_CPP_OKRAAPPPROVALS_H

#include "namers/ApprovalTestNamer.h"
#ifdef APPROVALS_OKRA

// <SingleHpp unalterable>
#include "Okra.h"


struct OkraApprovalListener : public okra::IListener
{
 TestName currentTest;

public:
 void OnStart(const okra::TestInfo &testInfo) override
 {
  currentTest.fileName = testInfo.file_path;
  currentTest.sections = {testInfo.name};
  ApprovalTestNamer::currentTest(&currentTest);
 }

 void OnEnd(const okra::TestInfo &testInfo, std::chrono::high_resolution_clock::duration duration) override {
 }
 void OnFail(const std::string &message) override {
 }
};

OKRA_REGISTER_LISTENER(OkraApprovalListener);
// </SingleHpp>
#endif
#endif //APPROVALTESTS_CPP_OKRAAPPPROVALS_H
