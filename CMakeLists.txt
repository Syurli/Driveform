cmake_minimum_required(VERSION 3.25)

project(Driveform VERSION 0.1.0 LANGUAGES CXX)

option(DRIVEFORM_BUILD_TESTS "Build Driveform tests" ON)
option(DRIVEFORM_BUILD_C_API "Build the stable C ABI wrapper" ON)

add_library(DriveformCore STATIC
    Core/Source/world.cpp
)
add_library(Driveform::Core ALIAS DriveformCore)

target_compile_features(DriveformCore PUBLIC cxx_std_20)
target_include_directories(DriveformCore
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Core/Include>
)

if(MSVC)
    target_compile_options(DriveformCore PRIVATE /W4 /permissive-)
else()
    target_compile_options(DriveformCore PRIVATE -Wall -Wextra -Wpedantic)
endif()

if(DRIVEFORM_BUILD_C_API)
    add_library(DriveformC STATIC
        SDK/C/Source/driveform.cpp
    )
    add_library(Driveform::C ALIAS DriveformC)
    target_compile_features(DriveformC PUBLIC cxx_std_20)
    target_include_directories(DriveformC
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/SDK/C/Include>
    )
    target_link_libraries(DriveformC PRIVATE Driveform::Core)
endif()

if(DRIVEFORM_BUILD_TESTS)
    enable_testing()
    add_subdirectory(Tests)
endif()
