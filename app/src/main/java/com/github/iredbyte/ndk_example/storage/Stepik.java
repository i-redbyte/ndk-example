package com.github.iredbyte.ndk_example.storage;
/**
 * solutions for the course
 * <a href="https://stepik.org/course/7/syllabus">Stepik C++</a>
 * adapted for Android NDK
 * */
public class Stepik {
    static {
        System.loadLibrary("stepik");
    }

    public Stepik() {
    }


    public native void helloWord();
}