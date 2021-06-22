cmake_minimum_required(VERSION 3.4.1)

message(STATUS "ANDROID_STL ${ANDROID_STL}")

#add_library(native-lib)

add_library(hellojni SHARED
        markov.cpp
        hellojni.cpp)

# Include libraries needed for hello-jni lib
target_link_libraries(
        hellojni
        android
        log
)