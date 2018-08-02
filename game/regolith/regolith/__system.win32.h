#pragma once
#if defined _WIN32

#include <graphics/xgl.h>

namespace platform {

	struct System final {
		// Command line
		int argc;
		char** argv;

		// GLFW window
		GLFWwindow* window;
	};

}

#endif