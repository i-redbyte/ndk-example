#include <jni.h>
#include <android/log.h>

#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, "_debugNative", __VA_ARGS__))

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

unsigned mystrlen(const char *str) {
    unsigned result = 0;
    while (*str++) ++result;
    return result;
}

void mystrcat(char *to, const char *from) {
    unsigned len = mystrlen(to);
    while (*from != '\0') {
        to[len] = *from;
        *from++;
        ++len;
    }
    to[len] = '\0';
}

extern "C" JNIEXPORT void JNICALL Java_com_github_iredbyte_ndk_1example_stepik_storage_Stepik_rotate
        (JNIEnv *env, jobject obj, jintArray array, jint size, jint shift) {
    jint *a = (*env).GetIntArrayElements(array, nullptr);
    rotate(a, size, shift);
    (*env).ReleaseIntArrayElements(array, a, 0);
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_github_iredbyte_ndk_1example_stepik_storage_Stepik_strcat(JNIEnv *env, jobject, jstring toObj,
                                                                   jstring fromObj) {
    const char *toString;
    const char *fromString;
    toString = (*env).GetStringUTFChars(toObj, nullptr);
    fromString = (*env).GetStringUTFChars(fromObj, nullptr);
    LOGD("%s", toString);
    LOGD("%s", fromString);
    mystrcat((char *) toString, fromString);
    LOGD("%s", toString);
    env->ReleaseStringChars(toObj, (jchar *) toString);
    env->ReleaseStringChars(fromObj, (jchar *) fromString);
    return env->NewStringUTF(toString);
}