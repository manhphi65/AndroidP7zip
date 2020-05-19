#ifndef ANDROIDUN7ZIP_DEBUGLOG_H
#define ANDROIDUN7ZIP_DEBUGLOG_H

#include <string>
#include <__locale>
#include <cstddef>
#include <android/log.h>

#ifdef NATIVE_LOG

static const char *getTag(const char *file, const char *function, int line) {
    std::string TOH_TAG = "TOH_";
    std::string filePath = file;
    std::size_t lastIndexOfFileSeparator = filePath.find_last_of("/\\");
    std::string mTag = TOH_TAG + filePath.substr(lastIndexOfFileSeparator + 1) + ":" + function + ":" +
                       std::to_string(line);
    return mTag.data();
}

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,getTag(__FILE__,__FUNCTION__,__LINE__),__VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,getTag(__FILE__,__FUNCTION__,__LINE__),__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,getTag(__FILE__,__FUNCTION__,__LINE__),__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,getTag(__FILE__,__FUNCTION__,__LINE__),__VA_ARGS__)
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE,getTag(__FILE__,__FUNCTION__,__LINE__),__VA_ARGS__)
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,getTag(__FILE__,__FUNCTION__,__LINE__),__VA_ARGS__)

#else
#define LOGD(...) do{}while(0)
#define LOGI(...) do{}while(0)
#define LOGW(...) do{}while(0)
#define LOGE(...) do{}while(0)
#define LOGF(...) do{}while(0)
#endif

#endif
