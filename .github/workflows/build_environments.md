# Build Environments Matrix

This page summarizes all environments used in our GitHub Actions workflow for CI builds, grouped by platform.

---

## Linux

| Job Name                        | OS Version | C++ Compiler   | Generator / Options                        |
|---------------------------------|------------|---------------|--------------------------------------------|
| clang16                         | 24.04      | clang++-16    | Unix Makefiles                             |
| clang18                         | 24.04      | clang++-18    | Unix Makefiles                             |
| gcc12                           | 24.04      | g++-12        | Unix Makefiles                             |
| gcc14                           | 24.04      | g++-14        | Unix Makefiles                             |
| gcc14 unity                     | 24.04      | g++-14        | Unix Makefiles, CMAKE_UNITY_BUILD=yes      |
| gcc14 ninja in-source           | 24.04      | g++-14        | Ninja                                      |
| gcc14 ninja out-of-source       | 24.04      | g++-14        | Ninja                                      |
| gcc14 ninja-unity               | 24.04      | g++-14        | Ninja, CMAKE_UNITY_BUILD=yes               |

---

## macOS

| Job Name                        | OS Version | C++ Compiler   | Generator / Options                        |
|---------------------------------|------------|---------------|--------------------------------------------|
| xcode-26.6                      | latest     | AppleClang    | Unix Makefiles                             |

---

## Windows

| Job Name                        | OS Version | C++ Compiler   | Generator / Options                        |
|---------------------------------|------------|---------------|--------------------------------------------|
| WIN-2025-VS-2026                | 2025       | MSVC          | Visual Studio 18 2026                      |
| WIN-2025-VS-2026 (clangcl)      | 2025       | clang-cl      | Visual Studio 18 2026 -T clangcl           |
| WIN-2022-VS-2022                | 2022       | MSVC          | Visual Studio 17 2022                      |

---

**Notes:**
- The macOS job explicitly selects the matrix's Xcode version.
- Windows jobs use MSVC or clang-cl via Visual Studio generators.
- Some jobs use extra CMake flags or different generators to test various build configurations.
