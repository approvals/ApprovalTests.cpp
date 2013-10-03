#include "Menus.h"

using namespace std;

string Menus::BackToWorkMenu()
{
    return "Back to Work!\n\nPress Enter to start new Tomato\n";
}

string Menus::BreakMenu()
{
    stringstream prompt;
    prompt << "Time for a well-deserved break...\n\n" <<
           "[1] 5 minutes\n" <<
           "[2] 10 minutes\n" <<
           "[3] 15 minutes\n" <<
           "[4] 25 minutes\n\n" <<
           "How long? (Choose and press Enter) ";
    return prompt.str();
}

string Menus::MainMenu()
{
    return "Welcome to TomatoTime\n\nPress Enter to start new Tomato\n";
}

string Menus::TomatoFinishedMenu()
{
    return "Tomato Done!\n\nWhat did you work on?\n\n";
}