#include <jni.h>
#include <iostream>
#include <string>
#include <android/log.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "CppTheBest", __VA_ARGS__))
#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, "_debugNative", __VA_ARGS__))


#define MAX(x, y, r)  \
{                     \
int xx = x;           \
int yy = y;           \
r = xx > yy?xx:yy;    \
}


int power(int x, unsigned p) {
    if (p == 0) return 1;
    int answer = x;
    for (int i = 1; i < p; i++) answer *= x;
    return answer;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

int power_recursion(int x, unsigned p) {
    if (p == 0) return 1;
    return x * power_recursion(x, p - 1);
}

#pragma clang diagnostic pop

int log2(int x) {
    int result = 0;
    while (x >= 1) {
        ++result;
        x = x >> 1;
    }
    return --result;
}

extern "C" JNIEXPORT void JNICALL Java_com_github_iredbyte_ndk_1example_storage_Stepik_helloWord
        (JNIEnv *env, jobject) {
    std::cout << "Hello from C++ !!!" << std::endl;
    LOGD("Hello from NDK !!!");
    LOGI("Hello from JNI !!!");
}

extern "C" JNIEXPORT jint JNICALL Java_com_github_iredbyte_ndk_1example_storage_Stepik_power
        (JNIEnv *, jobject, jint x, jint p) {
    return power(x, p);
}

extern "C" JNIEXPORT jint JNICALL Java_com_github_iredbyte_ndk_1example_storage_Stepik_power_1recursion
        (JNIEnv *, jobject, jint x, jint p) {
    return power_recursion(x, p);
}


extern "C" JNIEXPORT jint JNICALL Java_com_github_iredbyte_ndk_1example_storage_Stepik_max3
        (JNIEnv *, jobject, jint a, jint b, jint c) {
    MAX(a, b, c)
    return c;
}

extern "C" JNIEXPORT jint JNICALL Java_com_github_iredbyte_ndk_1example_storage_Stepik_log2
        (JNIEnv *, jobject, jint x) {
    return log2(x);
}

extern "C" JNIEXPORT jstring JNICALL Java_com_github_iredbyte_ndk_1example_storage_Stepik_quadratic_1equation
        (JNIEnv *env, jobject, jint a, jint b, jint c) {
    int d = (b * b) - 4 * a * c;
    if (d < 0) {
        return env->NewStringUTF("No real roots");
    } else if (d == 1) {
        int x = (-b / (2 * a));
        char str[100];
        sprintf(str, "One root: x1 = %d, x2 = %d", x, x);
        return env->NewStringUTF(str);
    } else {
        double x1 = (-b + sqrt(d)) / (2 * a);
        double x2 = (-b - sqrt(d)) / (2 * a);
        char str[100];
        sprintf(str, "Roots: x1 = %f, x2 = %f", x1, x2);
        return env->NewStringUTF(str);
    }
}