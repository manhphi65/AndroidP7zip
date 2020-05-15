#include <str2args/str2args.h>
#include <ndkhelper.h>
#include <p7zip/CPP/Common/ResultObject.h>
#include <p7zip/CPP/7zip/UI/Common/ExitCode.h>
#include "command.h"
#include <DebugLog.h>

int executeCommand(const char *cmd) {
    int argc = 0;
    char temp[ARGC_MAX][ARGV_LEN_MAX];
    char *argv[ARGC_MAX];
    if (!str2args(cmd, temp, &argc)) {
        return 7;
    }
    for (int i = 0; i < argc; i++) {
        argv[i] = temp[i];
        LOGD("arg[%d]:[%s]", i, argv[i]);
    }
    return main(argc, argv);
}

extern int main2(
#ifndef _WIN32
        int numArgs, char *args[], ResultObject *resultObject
#endif
);

jstring executeCommandList(JNIEnv *env, const char *cmd) {
    int argc = 0;
    char temp[ARGC_MAX][ARGV_LEN_MAX];
    char *argv[ARGC_MAX];
    ResultObject resultObject;
    if (!str2args(cmd, temp, &argc)) {
        resultObject.setResultCode(NExitCode::kUserError);
        return resultObject.convertResult(env);
    }
    for (int i = 0; i < argc; i++) {
        argv[i] = temp[i];
        LOGD("arg[%d]:[%s]", i, argv[i]);
    }
    main2(argc, argv, &resultObject);
    return resultObject.convertResult(env);
}