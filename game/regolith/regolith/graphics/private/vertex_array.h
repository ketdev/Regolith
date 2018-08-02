#pragma once

#include <string>
#include <regolith\types.h>
#include <regolith\graphics\private\vertex_buffer.h>

namespace regolith {
	namespace graphics {

		struct VertexArray {
			struct Attribute {
				volatile const uint32 index;

				Attribute(uint32 index);
				Attribute(const Attribute& o);
				~Attribute();
			};

			const uint32 id;

			VertexArray();
			~VertexArray();
			
			Attribute setAttrib(uint32 index, const VertexBuffer& buffer, 
				bool normalized, usize stride, const void* offset);
			void drawTriangles(uint32 first, uint32 count);
		};

	}
}

