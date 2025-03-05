#include "../com_github_iredbyte_ndk_example_ndkman_storage_NdkMan.h"
#include "Store.h"
#include <cstdlib>
#include <cstring>
#include <android/log.h>

#define LOG_TAG "NDK_LOG"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

static Store store;

JNIEXPORT jint JNI_OnLoad(JavaVM *pVM, void *reserved) {
    JNIEnv *env;
    if (pVM->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        abort();
    }

    store.length = 0;
    return JNI_VERSION_1_6;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_github_iredbyte_ndk_1example_ndkman_storage_NdkMan_getCount
        (JNIEnv *, jobject) {
    return store.length;
}

bool isEntryValid(JNIEnv *pEnv, StoreEntry *pEntry, StoreType pType) {
    if (pEntry == NULL) {
        LOGW("Entry is NULL");
        return false;
    }

    if (pEntry->type != pType) {
        LOGW("Invalid type: expected=%d, actual=%d", pType, pEntry->type);
        return false;
    }

    LOGD("Entry is valid: key=%s, type=%d", pEntry->key, pEntry->type);
    return true;
}

StoreEntry *findEntry(JNIEnv *pEnv, Store *pStore, jstring pKey) {
    if (pKey == NULL) {
        LOGE("Key is NULL");
        return NULL;
    }

    const char *tmpKey = pEnv->GetStringUTFChars(pKey, NULL);
    LOGD("Searching for key: %s", tmpKey);

    StoreEntry *entry = pStore->entries;
    StoreEntry *entryEnd = entry + pStore->length;

    while (entry < entryEnd) {
        if (entry->key != NULL) {
            LOGD("Comparing with stored key: %s", entry->key);
        } else {
            LOGW("Stored key is NULL");
        }

        if (strcmp(entry->key, tmpKey) == 0) {
            LOGD("Key found: %s", entry->key);
            pEnv->ReleaseStringUTFChars(pKey, tmpKey);
            return entry;
        }

        ++entry;
    }

    pEnv->ReleaseStringUTFChars(pKey, tmpKey);
    LOGW("Key not found: %s", tmpKey);
    return NULL;
}

StoreEntry *allocateEntry(JNIEnv *pEnv, Store *pStore, jstring pKey) {
    StoreEntry *entry = findEntry(pEnv, pStore, pKey);
    if (entry != NULL) {
        releaseEntryValue(pEnv, entry);
    } else {
        entry = pStore->entries + pStore->length;
        const char *tmpKey = pEnv->GetStringUTFChars(pKey, NULL);
        entry->key = new char[strlen(tmpKey) + 1];
        strcpy(entry->key, tmpKey);
        pEnv->ReleaseStringUTFChars(pKey, tmpKey);
        ++pStore->length;
    }
    return entry;
}

void releaseEntryValue(JNIEnv *pEnv, StoreEntry *pEntry) {
    switch (pEntry->type) {
        case StoreType_String:
            delete pEntry->value.string;
            break;
    }
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_github_iredbyte_ndk_1example_ndkman_storage_NdkMan_getString
        (JNIEnv *pEnv, jobject pThis, jstring pKey) {
    const char *cstr = pEnv->GetStringUTFChars(pKey, NULL);
    StoreEntry *entry = findEntry(pEnv, &store, pKey);
    if (isEntryValid(pEnv, entry, StoreType_String)) {
        return pEnv->NewStringUTF(entry->value.string);
    } else {
        return NULL;
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_github_iredbyte_ndk_1example_ndkman_storage_NdkMan_setString
        (JNIEnv *pEnv, jobject pThis, jstring pKey, jstring pValue) {
    StoreEntry *entry = allocateEntry(pEnv, &store, pKey);
    if (entry != NULL) {
        entry->type = StoreType_String;
        jsize stringLength = pEnv->GetStringUTFLength(pValue);
        const char *cstr = pEnv->GetStringUTFChars(pValue, NULL);
        entry->value.string = new char[stringLength + 1];
        pEnv->GetStringUTFRegion(pValue, 0, stringLength, entry->value.string);
        entry->value.string[stringLength] = '\0';
    }
}

extern "C" JNIEXPORT jint JNICALL
Java_com_github_iredbyte_ndk_1example_ndkman_storage_NdkMan_getInteger
        (JNIEnv *pEnv, jobject pThis, jstring key) {
    StoreEntry *entry = findEntry(pEnv, &store, key);
    if (isEntryValid(pEnv, entry, StoreType_Integer)) {
        return entry->value.integer;
    } else {
        return 0;
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_github_iredbyte_ndk_1example_ndkman_storage_NdkMan_setInteger
        (JNIEnv *pEnv, jobject pThis, jstring key, jint value) {
    StoreEntry *entry = allocateEntry(pEnv, &store, key);
    if (entry != NULL) {
        entry->type = StoreType_Integer;
        entry->value.integer = value;
    }
}
extern "C" JNIEXPORT jboolean JNICALL
Java_com_github_iredbyte_ndk_1example_ndkman_storage_NdkMan_getBoolean
        (JNIEnv *pEnv, jobject pThis, jstring key) {
    StoreEntry *entry = findEntry(pEnv, &store, key);
    if (isEntryValid(pEnv, entry, StoreType_Boolean)) {
        return entry->value.boolean;
    } else {
        return false;
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_github_iredbyte_ndk_1example_ndkman_storage_NdkMan_setBoolean
        (JNIEnv *pEnv, jobject pThis, jstring key, jboolean value) {
    StoreEntry *entry = allocateEntry(pEnv, &store, key);
    if (entry != NULL) {
        entry->type = StoreType_Boolean;
        entry->value.boolean = value;
    }
}

extern "C" JNIEXPORT jfloat JNICALL
Java_com_github_iredbyte_ndk_1example_ndkman_storage_NdkMan_getFloat
        (JNIEnv *pEnv, jobject pThis, jstring key) {
    StoreEntry *entry = findEntry(pEnv, &store, key);
    if (isEntryValid(pEnv, entry, StoreType_Float)) {
        return entry->value.float_t;
    } else {
        return 0;
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_github_iredbyte_ndk_1example_ndkman_storage_NdkMan_setFloat
        (JNIEnv *pEnv, jobject pThis, jstring key, jfloat value) {
    StoreEntry *entry = allocateEntry(pEnv, &store, key);
    if (entry != NULL) {
        entry->type = StoreType_Float;
        entry->value.float_t = value;
    }
}

extern "C" JNIEXPORT jdouble JNICALL
Java_com_github_iredbyte_ndk_1example_ndkman_storage_NdkMan_getDouble
        (JNIEnv *pEnv, jobject pThis, jstring key) {
    StoreEntry *entry = findEntry(pEnv, &store, key);
    if (isEntryValid(pEnv, entry, StoreType_Double)) {
        return entry->value.double_t;
    } else {
        return 0;
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_github_iredbyte_ndk_1example_ndkman_storage_NdkMan_setDouble
        (JNIEnv *pEnv, jobject pThis, jstring key, jdouble value) {
    StoreEntry *entry = allocateEntry(pEnv, &store, key);
    if (entry != NULL) {
        entry->type = StoreType_Double;
        entry->value.double_t = value;
    }
}