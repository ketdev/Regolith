#if defined __ANDROID__
#include <regolith/platform/native.android.h>
#include <regolith\types.h>
#include <regolith\platform\application.h>
#include <regolith\platform\log.h>

namespace regolith {
	namespace platform {
		
		static void handleCommand(struct android_app* app, int32 cmd) {
			NativeData* data = reinterpret_cast<NativeData*>(app->userData);
			
			// Process the next main command.
			switch (cmd) {
			case APP_CMD_INIT_WINDOW:
				if (data->app->window) {
					data->engine->startup();
				}
				break;

			case APP_CMD_SAVE_STATE:
				data->engine->state.save(data->app->savedState, data->app->savedStateSize);
				break;

			case APP_CMD_TERM_WINDOW:
				data->engine->terminate();
				break;

			case APP_CMD_LOST_FOCUS:
			case APP_CMD_GAINED_FOCUS:
				data->engine->update();
				break;
			}
		}

		// Process the next input event.
		static int32_t handleInput(struct android_app* app, AInputEvent* event) {
			NativeData* data = reinterpret_cast<NativeData*>(app->userData);

			if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
				data->engine->state.x = AMotionEvent_getX(event, 0);
				data->engine->state.y = AMotionEvent_getY(event, 0);
				return 1;
			}
			return 0;
		}


		Application::Application(native_t native) : native(native), screen(native), view(0) {
			// Initialize native handlers
			native->app->onAppCmd = handleCommand;
			native->app->onInputEvent = handleInput;
			
			// Restore previous saved state
			state.load(native->app->savedState, native->app->savedStateSize);
		}
		Application::~Application() {}

		void Application::pollEvents() {
			// Read all pending events.
			int ident;
			int events;
			struct android_poll_source* source;

			// If not animating, we will block forever waiting for events.
			// If animating, we loop until all events are read, then continue
			// to draw the next frame of animation.
			while ((ident = ALooper_pollAll(0, NULL, &events, (void**)&source)) >= 0) {
				if (source != NULL)
					source->process(native->app, source);
			}
		}

		bool Application::closeRequested() {
			return native->app->destroyRequested != 0;
		}
	}
}
#endif