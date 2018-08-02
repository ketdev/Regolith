#if defined _WIN32
#include <regolith/platform/windows_glue/native.windows.h>

#include <regolith/data/systems.h>

#include <core\kernel.h>
#include <platform\native_system.h>


using namespace regolith::platform;


void main(int argc, char* argv[]) {
	// initialize native data
	platform::NativeSystem native = { 0 };
	native.argc = argc;
	native.argv = argv;
	core::Kernel::newEntity<platform::NativeSystem>();

	// start kernel
	core::Kernel::run();



	NativeData userData = { 0 };
	userData.argc = argc;
	userData.argv = argv;	
	Application::run(userData);
}

#endif