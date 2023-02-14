package com.github.iredbyte.ndk_example.storage

class PowerOfStroustrup {

    init {
        System.loadLibrary("hellojni")
//        System.loadLibrary("stepik")
    }

    external fun stringFromJNI(): String?

    external fun markovPoissonProcess(): DoubleArray?
}