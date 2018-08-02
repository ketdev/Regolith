#if defined __ANDROID__
#include <regolith\platform\android_glue\native.android.h>
#include <regolith\graphics\screen.h>
#include <regolith\platform\log.h>

namespace regolith {
	namespace graphics {

		Screen::Screen(native_t native) : native(native) {}
		Screen::~Screen() {
			terminate();
		}

		void Screen::startup(const Config& config) {
			native->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
			eglInitialize(native->display, 0, 0);

			/*
			* Here specify the attributes of the desired configuration.
			* Below, we select an EGLConfig with at least 8 bits per color
			* component compatible with on-screen windows
			*/
			const EGLint attribs[] = {
				EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
				EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
				EGL_RED_SIZE, 8,
				EGL_GREEN_SIZE, 8,
				EGL_BLUE_SIZE, 8,
				EGL_ALPHA_SIZE, 8,
				EGL_DEPTH_SIZE, 0,
				EGL_STENCIL_SIZE, 0,
				EGL_NONE
			};
			int attrib_list[] = { 
				EGL_CONTEXT_CLIENT_VERSION, 3, 
				EGL_NONE 
			};

			/* Here, the application chooses the configuration it desires. In this
			* sample, we have a very simplified selection process, where we pick
			* the first EGLConfig that matches our criteria */
			EGLint numConfigs;
			EGLConfig eglConfig;
			eglChooseConfig(native->display, attribs, &eglConfig, 1, &numConfigs);

			/* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
			* guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
			* As soon as we picked a EGLConfig, we can safely reconfigure the
			* ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
			EGLint format;
			eglGetConfigAttrib(native->display, eglConfig, EGL_NATIVE_VISUAL_ID, &format);

			ANativeWindow_setBuffersGeometry(native->app->window, 0, 0, format);
			native->surface = eglCreateWindowSurface(native->display, eglConfig, native->app->window, NULL);
			native->context = eglCreateContext(native->display, eglConfig, EGL_NO_CONTEXT, attrib_list);
			
			if (eglMakeCurrent(native->display, native->surface, native->surface, native->context) == EGL_FALSE) {
				platform::log::warning("Unable to eglMakeCurrent");
				return;
			}

			//eglQuerySurface(display, surface, EGL_WIDTH, &w);
			//eglQuerySurface(display, surface, EGL_HEIGHT, &h);

			// Initialize GL state.
			//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
			glEnable(GL_CULL_FACE);
			//glShadeModel(GL_SMOOTH);
			glDisable(GL_DEPTH_TEST);

		}

		void Screen::terminate() {
			if (native->display != EGL_NO_DISPLAY) {
				eglMakeCurrent(native->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
				if (native->context != EGL_NO_CONTEXT) {
					eglDestroyContext(native->display, native->context);
				}
				if (native->surface != EGL_NO_SURFACE) {
					eglDestroySurface(native->display, native->surface);
				}
				eglTerminate(native->display);
			}
			native->display = EGL_NO_DISPLAY;
			native->context = EGL_NO_CONTEXT;
			native->surface = EGL_NO_SURFACE;
		}
		
		void Screen::swapBuffers() {
			eglSwapBuffers(native->display, native->surface);
		}
	}
}



#endif