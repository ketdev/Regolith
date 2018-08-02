#pragma once

#include <string>
#include <regolith\types.h>
#include <regolith\math\vector.h>

namespace regolith {
	namespace graphics {

		struct VertexBuffer {
			const uint32 id;
			volatile const uint32 dimension;

			VertexBuffer();
			~VertexBuffer();

			void set(const void* data, uint32 dimension, uint32 count);
		};

	}
}

