#include <regolith\graphics\private\xgl.h>
#include <regolith\graphics\private\vertex_array.h>
#include <regolith\platform\log.h>

namespace regolith {
	namespace graphics {

		inline static GLuint createVertexArray() {
			GLuint id;
			glGenVertexArrays(1, &id);
			return id;
		}

		VertexArray::VertexArray() : id(createVertexArray()) {}
		VertexArray::~VertexArray() { glDeleteVertexArrays(1, &id); }

		VertexArray::Attribute VertexArray::setAttrib(uint32 index, 
			const VertexBuffer& buffer, bool normalized, usize stride, const void* offset){		
			glBindVertexArray(id);
			Attribute attrib(index);
			glBindBuffer(GL_ARRAY_BUFFER, buffer.id);
			glVertexAttribPointer(
				index, buffer.dimension, GL_FLOAT,
				normalized ? GL_TRUE : GL_FALSE,
				stride, offset
			);
			return attrib;
		}

		void VertexArray::drawTriangles(uint32 first, uint32 count) {
			glBindVertexArray(id);
			glDrawArrays(GL_TRIANGLES, first, count);
		}

		VertexArray::Attribute::Attribute(uint32 index) : index(index) {
			glEnableVertexAttribArray(index);
		}
		VertexArray::Attribute::Attribute(const VertexArray::Attribute& o) : index(o.index) {
			*const_cast<uint32*>(&o.index) = -1;
		}
		VertexArray::Attribute::~Attribute() {
			if (index != -1)
				glDisableVertexAttribArray(index);
		}

	}
}

