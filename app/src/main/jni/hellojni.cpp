#include <jni.h>
#include <string>
#include <vector>
#include "markov.h"

extern "C"
JNIEXPORT jstring

JNICALL
Java_com_github_iredbyte_ndk_1example_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject activity
) {
//    std::string appKey = "PuTy0uR4Ppl1C4TioNk3yH3re";
//    return env->NewStringUTF(appKey.c_str());
#if defined(__arm__)
#if defined(__ARM_ARCH_7A__)
#if defined(__ARM_NEON__)
#if defined(__ARM_PCS_VFP)
#define ABI "armeabi-v7a/NEON (hard-float)"
#else
#define ABI "armeabi-v7a/NEON"
#endif
#else
#if defined(__ARM_PCS_VFP)
#define ABI "armeabi-v7a (hard-float)"
#else
#define ABI "armeabi-v7a"
#endif
#endif
#else
#define ABI "armeabi"
#endif
#elif defined(__i386__)
#define ABI "x86"
#elif defined(__x86_64__)
#define ABI "x86_64"
#elif defined(__mips64)  /* mips64el-* toolchain defines __mips__ too */
#define ABI "mips64"
#elif defined(__mips__)
#define ABI "mips"
#elif defined(__aarch64__)
#define ABI "arm64-v8a"
#else
#define ABI "unknown"
#endif
    return env->NewStringUTF("Hello from JNI !  Compiled with ABI " ABI ".");
}

extern "C" JNIEXPORT jdoubleArray

JNICALL
Java_com_github_iredbyte_ndk_1example_MainActivity_markovPoissonProcess(
        JNIEnv *env,
        jobject activity
) {
    double lambda = 6.2;
    double t = 10;
    std::vector<double> data = poissonProcess(lambda, t);
    jdouble *outArray = &data[0];
    jdoubleArray outJNIArray = (*env).NewDoubleArray(data.size());
    if (outJNIArray == NULL) return NULL;
    (*env).SetDoubleArrayRegion(outJNIArray, 0, data.size(), outArray);
    return outJNIArray;
}