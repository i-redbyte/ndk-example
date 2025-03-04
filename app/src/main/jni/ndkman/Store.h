#ifndef NDK_EXAMPLE_STORE_H
#define NDK_EXAMPLE_STORE_H

#include <cstdint>
#include "jni.h"

#define STORE_MAX_CAPACITY 16

typedef enum {
    StoreType_Integer,
    StoreType_String,
} StoreType;

typedef union {
    int32_t integer;
    char *string;
} StoreValue;

typedef struct {
    char *key;
    StoreType type;
    StoreValue value;
} StoreEntry;

typedef struct {
    StoreEntry entries[STORE_MAX_CAPACITY];
    int32_t length;
} Store;

bool isEntryValid(JNIEnv *pEnv, StoreEntry *pEntry, StoreType pType);

StoreEntry *allocateEntry(JNIEnv *pEnv, Store *pStore, jstring pKey);

StoreEntry *findEntry(JNIEnv *pEnv, Store *pStore, jstring pKey);

void releaseEntryValue(JNIEnv *pEnv, StoreEntry *pEntry);

#endif //NDK_EXAMPLE_STORE_H
