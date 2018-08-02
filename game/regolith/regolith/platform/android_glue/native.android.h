#if defined __ANDROID__
#pragma once
#include <regolith/platform/android_glue/pch.h>

// android app data structure
#include <regolith\platform\application.h>
struct NativeData {
	// General data
	struct android_app* app;
	regolith::platform::Application* engine;

	// EGL display 
	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;
};
#endif