cmake_minimum_required(VERSION 3.4.1)

message(STATUS "ANDROID_STL ${ANDROID_STL}")

#add_library(native-lib)

add_library(stepik SHARED
        com_github_iredbyte_ndk_example_storage_Stepik.h
        stepik/stepik_part1.cpp
        )

target_link_libraries(
        stepik
        android
        log
)