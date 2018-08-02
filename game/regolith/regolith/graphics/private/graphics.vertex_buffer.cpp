#include <regolith\graphics\private\xgl.h>
#include <regolith\graphics\private\vertex_buffer.h>
#include <regolith\platform\log.h>

namespace regolith {
	namespace graphics {

		inline static GLuint createBuffer() {
			GLuint id;
			glGenBuffers(1, &id);
			return id;
		}

		VertexBuffer::VertexBuffer() : id(createBuffer()), dimension(0) {}

		VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &id); }

		void VertexBuffer::set(const void* data, uint32 dimension, uint32 count) {
			*const_cast<uint32*>(&this->dimension) = dimension;
			glBindBuffer(GL_ARRAY_BUFFER, id);
			glBufferData(GL_ARRAY_BUFFER, count * dimension * sizeof(float), data, GL_STATIC_DRAW);
		}

	}
}

