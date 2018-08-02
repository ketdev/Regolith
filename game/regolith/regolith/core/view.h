#pragma once

#include <regolith\types.h>
#include <regolith\graphics\program.h>
#include <regolith\graphics\geometry.h>

namespace regolith {
	namespace logic {

		struct View {

			View();
			~View();

			void update();
			
			graphics::Program program;
			graphics::Geometry geometry;
		};

	}
}

