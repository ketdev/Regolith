#pragma once

namespace platform {

	struct NativeSystem {
#if defined _WIN32

		// Command line
		int argc;
		char** argv;

#elif defined __ANDROID__

#endif
	};

}