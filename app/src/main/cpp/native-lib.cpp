#include <jni.h>
#include <string>
#include <android/log.h>

extern "C" {
#include "includes/libavcodec/version.h"
#include "includes/libavcodec/avcodec.h"
#include "includes/libavformat/version.h"
#include "includes/libavutil/version.h"
#include "includes/libavfilter/version.h"
#include "includes/libswresample/version.h"
#include "includes/libswscale/version.h"
#include <libavformat/avformat.h>
#include <libavutil/time.h>
}

// 进度回调函数
static int progress_callback(void *ctx, int what, int64_t param1, int param2, int total) {
    JNIEnv *env;
    JavaVM *g_jvm = nullptr;
    jobject g_obj = nullptr;

    // 获取全局 JVM 变量
    g_jvm->AttachCurrentThread(&env, nullptr);

    // 通过 JNI 调用 Kotlin 层的回调函数
    jclass clazz = env->GetObjectClass(g_obj);
    jmethodID onProgress = env->GetMethodID(clazz, "onProgress", "(II)V");

    // 传递进度信息到 Kotlin 层
    env->CallVoidMethod(g_obj, onProgress, param1, total);

    // 释放线程
    g_jvm->DetachCurrentThread();

    return 0;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_lanier_ffmpegbuild_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_lanier_ffmpegbuild_MainActivity_ffmpegVersion(JNIEnv *env, jobject thiz) {
    char strBuffer[1024 * 4] = {0};
    strcat(strBuffer, "libavcodec : ");
    strcat(strBuffer, AV_STRINGIFY(LIBAVCODEC_VERSION));
    strcat(strBuffer, "\nlibavformat : ");
    strcat(strBuffer, AV_STRINGIFY(LIBAVFORMAT_VERSION));
    strcat(strBuffer, "\nlibavutil : ");
    strcat(strBuffer, AV_STRINGIFY(LIBAVUTIL_VERSION));
    strcat(strBuffer, "\nlibavfilter : ");
    strcat(strBuffer, AV_STRINGIFY(LIBAVFILTER_VERSION));
    strcat(strBuffer, "\nlibswresample : ");
    strcat(strBuffer, AV_STRINGIFY(LIBSWRESAMPLE_VERSION));
    strcat(strBuffer, "\nlibswscale : ");
    strcat(strBuffer, AV_STRINGIFY(LIBSWSCALE_VERSION));
    strcat(strBuffer, "\navcodec_config : ");
    strcat(strBuffer, avcodec_configuration());
    strcat(strBuffer, "\navcodec_license : ");
    strcat(strBuffer, avcodec_license());

    return env->NewStringUTF(strBuffer);
}


extern "C"
JNIEXPORT jint JNICALL
Java_com_lanier_ffmpegbuild_MainActivity_executeCommand(JNIEnv *env, jobject thiz,
                                                        _jstring *command) {
    const char* cmd = env->GetStringUTFChars(command, nullptr);
    if (cmd == nullptr) {
        return -1;
    }

    int result = system(cmd);

    env->ReleaseStringUTFChars(command, cmd);

    return result;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_lanier_ffmpegbuild_MainActivity_executeCommandWithProgress(JNIEnv *env, jobject thiz,
                                                                    jstring command) {
}