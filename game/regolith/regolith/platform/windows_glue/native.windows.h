#pragma once
#if defined _WIN32

#include <regolith/graphics/private/xgl.h>

// windows app data structure
#include <regolith/platform/application.h>
struct NativeData {
	// General data
	regolith::platform::Application* engine;

	// Command line
	int argc;
	char** argv;
	
	// GLFW window
	GLFWwindow* window;
	
};

#endif