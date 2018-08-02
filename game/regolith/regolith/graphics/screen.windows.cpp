#if defined _WIN32

#include <regolith\platform\windows_glue\native.windows.h>
#include <regolith\graphics\screen.h>
#include <regolith\platform\log.h>

namespace regolith {
	namespace graphics {

		Screen::Screen(native_t native) : native(native) {}
		Screen::~Screen() {
			terminate();
		}

		void Screen::startup(const Config& config) {
			glfwWindowHint(GLFW_SAMPLES, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			// Open a window and create its OpenGL context
			native->window = glfwCreateWindow(
				config.width,
				config.height,
				config.title.c_str(),
				NULL, NULL);
			if (native->window == NULL)
				throw LoadError{ "Failed to open GLFW window" };

			// Ensure we can capture the escape key being pressed below
			glfwSetInputMode(native->window, GLFW_STICKY_KEYS, GL_TRUE);
			
			// must use before initializing GLEW
			glfwMakeContextCurrent(native->window);

			// Initialize GLEW
			glewExperimental = true; // Needed for core profile
			if (glewInit() != GLEW_OK) // must come after first window is created
				throw LoadError{ "Failed to initialize GLEW" };		
		}
		void Screen::terminate() {
			if (native->window != NULL) {				
				glfwDestroyWindow(native->window);
				native->window = NULL;
			}
		}
		void Screen::swapBuffers() {
			if (native->window != NULL) {
				glfwSwapBuffers(native->window);
			}
		}
	}
}

#endif