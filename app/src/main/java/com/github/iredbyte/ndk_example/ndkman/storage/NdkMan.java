package com.github.iredbyte.ndk_example.ndkman.storage;

public class NdkMan {
    static {
        System.loadLibrary("ndkman");
    }

    public NdkMan() {
    }

    public native int getCount();

    public native String getString(String key);

    public native void setString(String key, String value);

    public native int getInteger(String key);

    public native void setInteger(String key, int value);

    public native boolean getBoolean(String key);

    public native void setBoolean(String key, boolean value);
}
