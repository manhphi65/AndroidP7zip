//
// Created by ManhPhi on 14/05/2020.
//

#ifndef ANDROIDP7ZIP_RESULTOBJECT_H
#define ANDROIDP7ZIP_RESULTOBJECT_H

#include <string>
#include <wchar.h>
#include <jni.h>

#include <ndkhelper.h>
#include <p7zip/CPP/Common/MyString.h>

class ResultObject {
    int resultCode;
    UStringVector resultData;

public:
    ResultObject();

    ResultObject(int code);

    void addItem(UString item);

    void clear();

    jstring convertResult(JNIEnv *env);

    jstring fromWStr(JNIEnv *env, wchar_t *result);
};

#endif //ANDROIDP7ZIP_RESULTOBJECT_H
