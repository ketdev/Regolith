#if defined _WIN32

#include <windows.h> 
#include <stdio.h> 
#include <exception>

#include <graphics/private/xgl.h>
#include <game.h>

BOOL __stdcall CtrlHandler(DWORD fdwCtrlType) {
	switch (fdwCtrlType) {
	case CTRL_C_EVENT:
	case CTRL_CLOSE_EVENT:
		return TRUE;

	case CTRL_BREAK_EVENT:
	case CTRL_LOGOFF_EVENT:
	case CTRL_SHUTDOWN_EVENT:
	default:
		return FALSE;
	}
}

void errorCallback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}

int main(int argc, char* argv[]) {
	// platform::System system = { 0 };
	// system.argc = argc;
	// system.argv = argv;

	try {
		// Initialise GLFW
		if (!glfwInit())
			throw std::exception("Failed to initialize GLFW");
		glfwSetErrorCallback(errorCallback);

		// Handle console events
		if (!SetConsoleCtrlHandler(CtrlHandler, TRUE))
			throw std::exception("Failed set CtrlHandler");

		// Open a window and create its OpenGL context
		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		system.window = glfwCreateWindow(1024, 768, "Tutorial 01", NULL, NULL);
		if (system.window == NULL) {
			throw std::exception("Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		}
		glfwMakeContextCurrent(system.window);

		// Initialize GLEW
		if (glewInit() != GLEW_OK) {
			throw std::exception("Failed to initialize GLEW\n");
		}

		// Ensure we can capture the escape key being pressed below
		glfwSetInputMode(system.window, GLFW_STICKY_KEYS, GL_TRUE);

		// Initialize game
		Game game;

		// ---

		// Dark blue background
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

		do {
			// Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
			glClear(GL_COLOR_BUFFER_BIT);

			// Draw nothing, see you in tutorial 2 !
			game.eventLoop();

			// Swap buffers
			glfwSwapBuffers(system.window);
			glfwPollEvents();

		} // Check if the ESC key was pressed or the window was closed
		while (glfwGetKey(system.window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			glfwWindowShouldClose(system.window) == 0);

	}
	catch (const std::exception& ex) {
		fprintf(stderr, ex.what());
		getchar();
		return 1;
	}

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
	return 0;
}

#endif