//
// Created by ManhPhi on 14/05/2020.
//

#include "ResultObject.h"
#include <p7zip/CPP/7zip/UI/Common/ExitCode.h>

#include <DebugLog.h>
TAG_FILE

ResultObject::ResultObject() {
    resultCode = NExitCode::kSuccess;
    resultData = UStringVector();
}

void ResultObject::setResultCode(int code) {
    resultCode = code;
}

void ResultObject::clear() {
    resultData.Clear();
}

void ResultObject::addItem(UString entryPath, bool isDirectory, UInt64 size) {
    UString itemDetail =
            (L"{\"path\":\"") + entryPath + L"\",\"isDirectory\":" + (isDirectory ? L"true" : L"false") + L",\"size\":" +
            std::to_wstring(size).data() + L"}";
    resultData.Add(itemDetail);
}

jstring ResultObject::convertResult(JNIEnv *env) {
    LOGD("Total item : %d", resultData.Size());
    UString resultList;
    if (resultData.Size() > 0) {
        resultList += L"[";
        for (int i = 0; i < resultData.Size() - 1; i++) {
            resultList += resultData[i];
            resultList += L",";
        }
        if (resultData.Size() > 0) resultList += resultData[resultData.Size() - 1];
        resultList += L"]";
    } else {
        resultList = L"[]";
    }
    UString resultJson = UString(L"{\"exitCode\":") + std::to_wstring(resultCode).data() + L",\"data\":" + resultList + L"}";
    LOGD("Result convert json : %ls", resultJson.Ptr());
    return fromWStr(env, const_cast<wchar_t *>(resultJson.Ptr()));
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