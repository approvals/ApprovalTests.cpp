#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>

#include "TestTracking.h"
#include <iostream>
#include <stdexcept>
#include <string>

#if defined(_WIN32)
#define NOMINMAX
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

namespace
{
    int modulesRun = 0;

    class LoadedLibrary
    {
    public:
        explicit LoadedLibrary(const char* path)
        {
#if defined(_WIN32)
            handle = LoadLibraryA(path);
            if (!handle)
            {
                throw std::runtime_error(std::string("Cannot load ") + path +
                                         ": " + std::to_string(GetLastError()));
            }
#else
            handle = dlopen(path, RTLD_NOW | RTLD_GLOBAL);
            if (!handle)
            {
                throw std::runtime_error(std::string("Cannot load ") + path +
                                         ": " + dlerror());
            }
#endif
        }

        ~LoadedLibrary()
        {
#if defined(_WIN32)
            FreeLibrary(handle);
#else
            dlclose(handle);
#endif
        }

        LoadedLibrary(const LoadedLibrary&) = delete;
        LoadedLibrary& operator=(const LoadedLibrary&) = delete;

    private:
#if defined(_WIN32)
        HMODULE handle;
#else
        void* handle;
#endif
    };
}

void recordModuleTest(int module)
{
    modulesRun |= module;
}

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        std::cerr << "Expected paths to both test libraries\n";
        return 1;
    }
    try
    {
        LoadedLibrary one(argv[1]);
        LoadedLibrary two(argv[2]);
        doctest::Context context;
        context.applyCommandLine(argc - 2, argv + 2);
        const int result = context.run();
        if (!context.shouldExit() && modulesRun != 3)
        {
            std::cerr << "Tests from both libraries must run\n";
            return 1;
        }
        return result;
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
