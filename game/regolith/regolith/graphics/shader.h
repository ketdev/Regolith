#pragma once

#include <string>
#include <regolith\types.h>

namespace regolith {
	namespace graphics {

		struct Shader {
			enum Type {
				Vertex,
				Fragment
			};
			struct CompileError {
				std::string msg;
			};
			
			const uint32 id;

			Shader(Type type, const std::string& code);
			~Shader();
		};

	}
}

