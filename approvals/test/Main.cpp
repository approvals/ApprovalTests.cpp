
#include <igloo/igloo.h>
#include "../namers/Namer.h"
#include "../namers/IglooNamerFactory.h"
using namespace igloo;

int main()
{
    DefaultTestResultsOutput output;
    TestRunner runner( output );

    IglooMetadataListener listener;
    runner.AddListener( &listener );
    MinimalProgressTestListener mpl;
    runner.AddListener( &mpl );

    return TestRunner::RunAllTests();
}