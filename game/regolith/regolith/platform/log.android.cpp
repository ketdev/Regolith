#if defined __ANDROID__
#include <android/log.h>

namespace regolith {
	namespace platform {
		namespace log {

			int debug(const char* const format, ...) {
				va_list varg;
				va_start(varg, format);
				int res = __android_log_vprint(ANDROID_LOG_DEBUG, "Artbox.NativeActivity", format, varg);
				va_end(varg);
				return res;
			}

			int warning(const char* const format, ...) {
				va_list varg;
				va_start(varg, format);
				int res = __android_log_vprint(ANDROID_LOG_WARN, "Artbox.NativeActivity", format, varg);
				va_end(varg);
				return res;
			}
		}
	}
}

#endif