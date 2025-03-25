cmake_minimum_required(VERSION 3.10)
project(FLVK)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# General include and library paths for all future libraries
set(THIRD_PARTY_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Include")
set(THIRD_PARTY_LIB_DIR "${CMAKE_SOURCE_DIR}/Lib")

# Ensure consistent runtime library settings
if (MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
endif()

# Find Vulkan
find_package(Vulkan REQUIRED)

# Add the Include directory so all libraries inside it can be found
include_directories(${THIRD_PARTY_INCLUDE_DIR})

# Add executable
add_executable(flvk src/main.cpp "src/logger.h" "src/fl_window.hpp" "src/fl_window.cpp" "src/fl_app.hpp" "src/fl_app.cpp" "src/fl_pipeline.hpp" "src/fl_pipeline.cpp" "src/fl_device.hpp" "src/fl_device.cpp")

# Link GLFW and Vulkan (and any future libraries)
target_link_libraries(flvk 
    ${THIRD_PARTY_LIB_DIR}/glfw3.lib 
    Vulkan::Vulkan
)
