#if defined _WIN32
#include <regolith\platform\windows_glue\native.windows.h>
#include <regolith\types.h>
#include <regolith\platform\application.h>
#include <regolith\platform\log.h>

namespace regolith {
	namespace platform {

		Application::Application(native_t native) : native(native), screen(native), view(0) {
			if (!glfwInit()) // must come before any opengl calls
				throw InitError{ "Failed to initialize GLFW" };	
			startup();

			// Restore previous saved state
			//state.load(native->app->savedState, native->app->savedStateSize);
		}
		Application::~Application() {
			screen.terminate();
			glfwTerminate();
		}

		void Application::pollEvents() {
			glfwPollEvents();
		}

		bool Application::closeRequested() {
			if (native->window == NULL) return false;
			return glfwWindowShouldClose(native->window) != 0;
		}

	}
}

#endif