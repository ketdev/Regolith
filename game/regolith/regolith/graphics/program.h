#pragma once

#include <string>
#include <regolith\types.h>
#include <regolith\graphics\shader.h>

namespace regolith {
	namespace graphics {

		struct Program {
			struct LinkError {
				std::string msg;
			};

			const uint32 id;

			Program();
			~Program();
			void link(std::initializer_list<Shader> shaders);
			void use();
		};

	}
}

