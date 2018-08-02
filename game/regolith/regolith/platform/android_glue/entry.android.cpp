#if defined __ANDROID__
#include <regolith/platform/native.android.h>
using namespace regolith::platform;

void android_main(struct android_app* app) {
	NativeData userData = { 0 };
	userData.app = app;
	app->userData = &userData;
	Application::run(userData);	
}

#endif