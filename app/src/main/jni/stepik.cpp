#include <jni.h>
#include <iostream>

extern "C" JNIEXPORT void JNICALL Java_com_github_iredbyte_ndk_1example_storage_Stepik_helloWord
        (JNIEnv *env, jobject) {
    std::cout << "Hello from C++ !!!" << std::endl;
}
