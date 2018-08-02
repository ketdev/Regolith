#if defined _WIN32
#include <stdio.h>
#include <Windows.h>

namespace regolith {
namespace platform {
namespace log {

	int debug(const char* const format, ...) {
		va_list varg;
		va_start(varg, format);
		int res = _vprintf_l(format, NULL, varg);
		va_end(varg);
		return res;
	}
	int warning(const char* const format, ...) {
		va_list varg;
		va_start(varg, format);
		int res = _vprintf_l(format, NULL, varg);
		va_end(varg);
		return res;
	}

}
}
}

#endif