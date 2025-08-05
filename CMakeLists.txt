cmake_minimum_required(VERSION 3.15)
project(MyGameProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable vcpkg integration
if(DEFINED ENV{VCPKG_ROOT})
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "")
endif()

# Add source and header files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.c)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS include/*.h)

# Copy assets to build directory
file(COPY Assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Levels DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include_directories(include)

add_executable(MyGameProject ${SOURCES} ${HEADERS})

# Link raylib automatically via vcpkg
find_package(raylib CONFIG REQUIRED)
target_link_libraries(MyGameProject PRIVATE raylib)