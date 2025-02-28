package com.github.iredbyte.ndk_example.ndkman.storage;

public class NdkMan {
    static {
        System.loadLibrary("ndkman");
    }
    public NdkMan() {}

    public native int getCount();

    public native String getString(String key);

    public native void setString(String key, String value);

}
