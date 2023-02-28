#ifndef NDK_EXAMPLE_UTILS_H
#define NDK_EXAMPLE_UTILS_H

/* Java String to C String */
static int jstr_to_cstr(JNIEnv *env, jstring jstr, char *cstr) {
    jsize jlen, clen;
    clen = env->GetStringUTFLength(jstr);
    jlen = env->GetStringLength(jstr);
    env->GetStringUTFRegion(jstr, 0, jlen, cstr);
    if (env->ExceptionCheck()) {
        return -EIO;
    }
    return 0;
}

#endif //NDK_EXAMPLE_UTILS_H
