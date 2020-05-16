#include <ndkhelper.h>
#include <DebugLog.h>
#include <cmd/command.h>
#include <wchar.h>
#define TAG "TOH_p7zip.cpp"

JNIEXPORT jstring JNICALL
JNI_FUNC(get7zVersionInfo)(JNIEnv *env, jclass type) {
    return env->NewStringUTF(MY_VERSION_COPYRIGHT_DATE);
}

JNIEXPORT jint JNICALL
JNI_FUNC(executeCommand)(JNIEnv *env, jclass type, jstring command_) {
    const char *command = env->GetStringUTFChars(command_, nullptr);
    LOGI("CMD:[%s]", command);
    int ret = executeCommand(command);
    env->ReleaseStringUTFChars(command_, command);
    return ret;
}

JNIEXPORT jstring JNICALL
JNI_FUNC(executeCommandList)(JNIEnv *env, jclass type, jstring command_) {
    const char *command = env->GetStringUTFChars(command_, nullptr);
    LOGI("CMD:[%s]", command);
    jstring data = executeCommandList(env, command);
    env->ReleaseStringUTFChars(command_, command);
    return data;
}





