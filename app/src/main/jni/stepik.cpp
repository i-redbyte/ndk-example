#include <jni.h>
#include <iostream>

/* присваивает r максимум из x и y */
#define MAX(x, y, r)  \
{                     \
int xx = x;           \
int yy = y;           \
r = xx > yy?xx:yy;    \
}

// определите только функцию power_recurion, где
//    x - число, которое нужно возвести в степень
//    p - степень, в которую нужно возвести x
//
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

extern "C" JNIEXPORT void JNICALL Java_com_github_iredbyte_ndk_1example_storage_Stepik_helloWord
        (JNIEnv *env, jobject) {
    std::cout << "Hello from C++ !!!" << std::endl;
}

extern "C" JNIEXPORT jint JNICALL Java_com_github_iredbyte_ndk_1example_storage_Stepik_power
        (JNIEnv *, jobject, jint x, jint p) {
    return power(x, p);
}

extern "C" JNIEXPORT jint JNICALL Java_com_github_iredbyte_ndk_1example_storage_Stepik_power_1recursion
        (JNIEnv *, jobject, jint x, jint p) {
    return power_recursion(x, p);
}