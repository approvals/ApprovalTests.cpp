# Build Environments Matrix

This page summarizes all environments used in our GitHub Actions workflow for CI builds, grouped by platform.

---

## Linux

| Job Name                        | OS Version | C++ Compiler   | Generator / Options                        |
|---------------------------------|------------|---------------|--------------------------------------------|
| clang14                         | 22.04      | clang++-14    | Unix Makefiles, libc++, C++20              |
| clang15                         | 22.04      | clang++-15    | Unix Makefiles                            |
| gcc9                            | 22.04      | g++-9         | Unix Makefiles                            |
| gcc10                           | 22.04      | g++-10        | Unix Makefiles                            |
| gcc13                           | 24.04      | g++-13        | Unix Makefiles                            |
| gcc10 unity                     | 22.04      | g++-10        | Unix Makefiles, CMAKE_UNITY_BUILD=yes      |
| gcc10 ninja in-source           | 22.04      | g++-10        | Ninja                                     |
| gcc10 ninja out-of-source       | 22.04      | g++-10        | Ninja                                     |
| gcc10 ninja-unity               | 22.04      | g++-10        | Ninja, CMAKE_UNITY_BUILD=yes               |

---

## macOS

| Job Name                        | OS Version | C++ Compiler   | Generator / Options                        |
|---------------------------------|------------|---------------|--------------------------------------------|
| xcode-15.4                      | latest     | AppleClang    | Unix Makefiles                            |
| xcode-15.4-ninja in-source      | latest     | AppleClang    | Ninja                                     |
| xcode-15.4-ninja out-of-source  | latest     | AppleClang    | Ninja                                     |

---

## Windows

| Job Name                        | OS Version | C++ Compiler   | Generator / Options                        |
|---------------------------------|------------|---------------|--------------------------------------------|
| VS-2019                         | 2019       | MSVC          | Visual Studio 16 2019                     |
| VS-2019 (clangcl)               | 2019       | clang-cl      | Visual Studio 16 2019 -T clangcl           |
| VS-latest                       | latest     | MSVC          | Visual Studio 17 2022                     |
| VS-latest (clangcl)             | latest     | clang-cl      | Visual Studio 17 2022 -T clangcl           |

---

**Notes:**
- macOS jobs use the AppleClang compiler provided by Xcode.
- Windows jobs use MSVC or clang-cl via Visual Studio generators.
- Some jobs use extra CMake flags or different generators to test various build configurations.
