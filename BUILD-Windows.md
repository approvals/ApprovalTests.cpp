# Building instructions - for Windows

## Prerequisites

* CMake 3.8 or higher
* A C++11 or above compiler

Optional:

* Google test framework, 1.8 or above

## Visual Studio 2017 Community Edition

Various ways to build with Visual Studio 2017 Community Edition ...

### Use Visual Studio 2017's "Open Folder" feature

* Build Output goes in `.vs`
* I found it fiddly to run the tests via this route

### Use CMake to generate Visual Studio 2017 configuration

Decide where to put the build files that CMake will generate.
In the following, we're putting the output in `cmake-build-vs` - that location is already ignored by git.

1. Go to start menu and open Developer Command Prompt for VS 2017
	* *This may not actually be necessary - opening any Command window may work*
2. Then run:

		cd ApprovalTests.cpp
		mkdir cmake-build-vs
		cd    cmake-build-vs
		cmake -G "Visual Studio 15 2017" ..

### Use CLion with Visual Studio installed

* Follow the instructions for experimental support of [Microsoft Visual C++ compiler](https://www.jetbrains.com/help/clion/quick-tutorial-on-configuring-clion-on-windows.html)
* Output is put in `cmake-build-debug`
* Tested with Visual Studio 2017
* **Major limitation**: Debugging is not yet supported by CLion, when compiling with Visual Studio, as of CLion 2017.3.3

---

## Obtaining Google Test for Windows (optional)

In order to run the tests of this project's optional integration with the Google Test framework, you'll need a built copy of that framework itself.

Here are some options: 

* build it from source - add to your project, or sub-project - see [google test's own instructions](https://github.com/google/googletest/tree/master/googletest)
* download it via Conan - there's a starting point at [claremacrae/googletest-starter-project](https://github.com/claremacrae/googletest-starter-project)
	* This will require making changes to your own `CMakeLists.txt` files 
* [Nuget package](https://www.nuget.org/packages/googletest/) - but it's not obvious how to use this inside CMake - see [Can't see how to configure CMake to find the Google Docs included in VS2017](https://github.com/MicrosoftDocs/visualstudio-docs/issues/580)
	* This is probably the best approach if you are maintaining your own Solution file, rather than generating it with CMake.

