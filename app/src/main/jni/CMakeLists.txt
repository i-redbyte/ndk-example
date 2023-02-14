cmake_minimum_required(VERSION 3.4.1)

message(STATUS "ANDROID_STL ${ANDROID_STL}")

#add_library(native-lib)

add_library(hellojni SHARED
        hellojni.cpp)

add_library(stepik SHARED
        markov.cpp
        stepik.cpp)

target_link_libraries(
        hellojni
        stepik
        android
        log
)