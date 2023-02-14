#include <jni.h>
#include <string>
#include <vector>
#include "markov.h"


extern "C" JNIEXPORT jdoubleArray

JNICALL
Java_com_github_iredbyte_ndk_1example_storage_PowerOfStroustrup_markovPoissonProcess(
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