package com.github.iredbyte.ndk_example.storage;

/**
 * solutions for the course
 * <a href="https://stepik.org/course/7/syllabus">Stepik C++</a>
 * adapted for Android NDK
 */
public class Stepik {
    static {
        System.loadLibrary("stepik");
    }

    public Stepik() {
    }


    public native void helloWord();

    public native int power(int x, int p);

    public native int power_recursion(int x, int p);

    public native int max3(int a, int b, int c);

    public native int log2(int x);

    public native String quadratic_equation(int a, int b, int c);
}
