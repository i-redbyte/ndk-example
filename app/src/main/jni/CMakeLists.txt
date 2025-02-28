cmake_minimum_required(VERSION 3.4.1)

message(STATUS "ANDROID_STL ${ANDROID_STL}")

#add_library(native-lib)

add_library(stepik SHARED
        stepik/stepik_part1.cpp
        stepik/stepik_part2.cpp
)

target_link_libraries(
        stepik
        android
        log
)

add_library(ndkman SHARED
        ndkman/Store.cpp
)
target_link_libraries(ndkman
        android
        log
)