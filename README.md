# 2D Platformer Game

This is a simple 2D platformer game written in C++ using [raylib](https://www.raylib.com/).  
It uses CMake and [vcpkg](https://github.com/microsoft/vcpkg) to manage dependencies and build the project across different platforms.

## Features

- Custom UI with buttons and menus
- Level loading and creation
- Built with modular C++20 code
- Cross-platform (Windows, Linux, macOS)

## Dependencies

- [raylib](https://github.com/raysan5/raylib)
- [vcpkg](https://github.com/microsoft/vcpkg) (for package management)
- CMake 3.15+ and a C++20-capable compiler (e.g., MSVC, clang, or g++)

---

## 🛠 Building the Project

1. Clone this repo:
    ```
    git clone https://github.com/youruser/yourproject.git
    cd yourproject
    ```

2. Install [vcpkg](https://github.com/microsoft/vcpkg):

    ```
    git clone https://github.com/microsoft/vcpkg
    cd vcpkg
    ./bootstrap-vcpkg.sh   # or .bat
    ```

3. Build the project:

    ```
    mkdir build
    cd build
    cmake .. -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
    cmake --build .
    ```

Replace `/path/to/vcpkg` with your vcpkg location.
