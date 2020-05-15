#ifndef ANDROIDUN7ZIP_NDKHELPER_H
#define ANDROIDUN7ZIP_NDKHELPER_H

#include <string>
#include <__locale>

#ifdef __cplusplus
extern "C" {
#endif

#include <jni.h>
#include <7zip/MyVersion.h>

#define JNI_FUNC(X) Java_com_hzy_libp7zip_P7ZipApi_##X

/**
 * To Get lib p7zip version info
 * @param env
 * @param type
 * @return
 */
JNIEXPORT jstring JNICALL
JNI_FUNC(get7zVersionInfo)(JNIEnv *env, jclass type);

/**
 * To execute some command with p7zip
 * @param env
 * @param type
 * @param command_
 * @return
 */
JNIEXPORT jint JNICALL
JNI_FUNC(executeCommand)(JNIEnv *env, jclass type, jstring command_);

JNIEXPORT jstring JNICALL
JNI_FUNC(executeCommandList)(JNIEnv *env, jclass type, jstring command_);

#ifdef __cplusplus
}
#endif

#endif
