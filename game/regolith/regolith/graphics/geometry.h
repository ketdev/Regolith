#pragma once

#include <regolith\types.h>
#include <regolith\math\vector.h>
#include <regolith\graphics\private\vertex_buffer.h>
#include <regolith\graphics\private\vertex_array.h>

namespace regolith {
	namespace graphics {

		struct Geometry {
			VertexArray vao;
			VertexBuffer vbo;
			volatile const uint32 count;
			
			Geometry() : count(0) {}
			~Geometry() {}		

			template<uint32 _Dim>
			void set(const math::Vector<_Dim> *data, uint32 count) {
				*const_cast<uint32*>(&this->count) = count;
				vbo.set(data, _Dim, count);
			}
			void draw() {
				VertexArray::Attribute attrib = vao.setAttrib(0, vbo, false, 0, 0);
				vao.drawTriangles(0, count);
			}
		};
		
	}
}

