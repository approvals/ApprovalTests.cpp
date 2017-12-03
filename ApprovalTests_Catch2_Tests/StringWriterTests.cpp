#include "../ApprovalTests/Catch2Approvals.h"

using namespace std;

string readFileAndDelete(const char *fileName) {
    ifstream in(fileName, ios_base::in);
    stringstream written;
    written << in.rdbuf();
    in.close();
    remove(fileName);

    string text = written.str();
    return text;
}

TEST_CASE("ItWritesTheContentsToAFile") {
    StringWriter s("Hello");
    auto fileName = "out.txt";
    s.Write(fileName);

    string text = readFileAndDelete(fileName);
    REQUIRE(text == "Hello\n");
}

TEST_CASE("ItWritesTheContentsToAStream") {
    stringstream out;
    StringWriter s("Hello");
    s.Write(out);
    REQUIRE(out.str() == "Hello\n");
}

TEST_CASE("TheDefaultExtensionIsText") {
    StringWriter s("Hello");
    REQUIRE(s.GetFileExtension() == ".txt");
}

TEST_CASE("TheExtensionIsConfigurable") {
    StringWriter s("Hello", ".html");
    REQUIRE(s.GetFileExtension() == ".html");
}