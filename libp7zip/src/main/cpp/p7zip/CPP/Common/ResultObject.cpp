//
// Created by ManhPhi on 14/05/2020.
//

#include "ResultObject.h"
#include <p7zip/CPP/7zip/UI/Common/ExitCode.h>

#define TAG "TOH_ResultObject.h"

ResultObject::ResultObject() {
    resultCode = NExitCode::kSuccess;
}

ResultObject::ResultObject(int code) {
    resultCode = code;
}

void ResultObject::clear() {
    resultData.Clear();
}

void ResultObject::addItem(UString item) {
    resultData.Add(item);
}

jstring ResultObject::convertResult(JNIEnv *env) {
    LOGTAGD(TAG, "Total item : %d", resultData.Size());
    UString result(L"[");
    for (int i = 0; i < resultData.Size() - 1; ++i) {
        result += resultData[i];
        result += L",";
    }
    if (resultData.Size() > 0) result += resultData[resultData.Size()-1];
    result += L"]";
    LOGTAGD(TAG, "Result convert json : %ls", result.Ptr());
    return fromWStr(env, const_cast<wchar_t *>(result.Ptr()));
}

jstring ResultObject::fromWStr(JNIEnv *env, wchar_t *result) {
    jobject bb = env->NewDirectByteBuffer((void *) result, wcslen(result) * sizeof(wchar_t));
    jclass cls_Charset = env->FindClass("java/nio/charset/Charset");
    jmethodID mid_Charset_forName = env->GetStaticMethodID(cls_Charset, "forName",
                                                           "(Ljava/lang/String;)Ljava/nio/charset/Charset;");
    jobject charset = env->CallStaticObjectMethod(cls_Charset, mid_Charset_forName,
                                                  env->NewStringUTF("UTF-32LE"));

    jmethodID mid_Charset_decode = env->GetMethodID(cls_Charset, "decode",
                                                    "(Ljava/nio/ByteBuffer;)Ljava/nio/CharBuffer;");
    jobject cb = env->CallObjectMethod(charset, mid_Charset_decode, bb);

    jclass cls_CharBuffer = env->FindClass("java/nio/CharBuffer");
    jmethodID mid_CharBuffer_toString = env->GetMethodID(cls_CharBuffer, "toString",
                                                         "()Ljava/lang/String;");
    jstring ret = static_cast<jstring>(env->CallObjectMethod(cb, mid_CharBuffer_toString));
    return ret;
}