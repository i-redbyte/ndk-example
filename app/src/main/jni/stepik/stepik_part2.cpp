#include <jni.h>

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void rotate(int a[], unsigned size, unsigned shift) {
    shift %= size;
    unsigned int n = size - 1;
    for (int i = 0; i < shift; ++i) {
        for (int j = 0; j < n; j++) {
            swap(&a[j], &a[j + 1]);
        }
    }
}

extern "C" JNIEXPORT void JNICALL Java_com_github_iredbyte_ndk_1example_storage_Stepik_rotate
        (JNIEnv *env, jobject obj, jintArray array, jint size, jint shift) {
    jint *a = (*env).GetIntArrayElements(array, nullptr);
    rotate(a, size, shift);
    (*env).ReleaseIntArrayElements(array, a, 0);
}