#if defined __ANDROID__
#include <jni.h>
#include <errno.h>

#include <string.h>
#include <unistd.h>
#include <sys/resource.h>

#include <regolith\graphics\private\xgl.h>

#include <android/sensor.h>
#include <android/log.h>

#include <regolith/platform/android_glue/android_native_app_glue.h>

#endif