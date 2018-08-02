#pragma once

namespace regolith {
	namespace platform {
		namespace log {

			int debug(const char* const format, ...);
			int warning(const char* const format, ...);

		}
	}
}