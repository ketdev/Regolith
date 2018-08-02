#pragma once

#include <string>
#include <regolith\types.h>
#include <regolith\graphics\screen.h>
#include <regolith\core\view.h>
#include <regolith\core\saved_state.h>

namespace regolith {
	namespace platform {

		struct Application {
			// types ----------------------------------------------------------
			struct InitError {
				std::string msg;
			};

			// data -----------------------------------------------------------
			const native_t native;
			graphics::Screen screen;
			logic::View *view;
			system::SavedState state;

			// functions ------------------------------------------------------
			template<typename _Native>
			static void run(_Native& native) {
				Application application(&native);
				native.engine = &application;

				while (!application.closeRequested()) {
					application.pollEvents();
					application.update();
				}
			}


			void startup() {
				screen.startup(Application::getConfig());
				if (!view) {
					view = new logic::View();
				}
			}
			void terminate() {
				screen.terminate();
				if (view) {
					delete view;
					view = NULL;
				}
			}
			void update() {
				if(view)
					view->update();
				screen.swapBuffers();
			}

		private:
			Application(native_t native);
			~Application();
			void pollEvents();
			bool closeRequested();
			static graphics::Screen::Config getConfig() {
				return {
					"Artbox",	// title
					1024,		// width
					768			// height
				};
			}
		};

	}
}

