add_executable(DriveformSmoke
    smoke.cpp
)

target_compile_features(DriveformSmoke PRIVATE cxx_std_20)
target_link_libraries(DriveformSmoke PRIVATE Driveform::C)

add_test(NAME DriveformSmoke COMMAND DriveformSmoke)
