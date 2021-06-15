cmake_minimum_required(VERSION 3.4.1)

message(STATUS "ANDROID_STL ${ANDROID_STL}")

add_library(hellojni SHARED
        hellojni.c)

# Include libraries needed for hello-jni lib
target_link_libraries(
        hellojni
        android
        log
)