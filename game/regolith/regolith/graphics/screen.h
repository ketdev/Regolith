#pragma once

#include <string>
#include <regolith/types.h>
typedef struct NativeData* native_t;

namespace regolith {
	namespace graphics {

		struct Screen {
			struct Config {
				std::string title;
				int width;
				int height;
			};
			struct LoadError {
				std::string msg;
			};

			const native_t native;

			Screen(native_t native);
			~Screen();

			void startup(const Config& config);
			void terminate();

			void swapBuffers();
		};

	}
}

