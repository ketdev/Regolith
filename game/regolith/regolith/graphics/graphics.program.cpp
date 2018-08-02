#include <regolith\graphics\private\xgl.h>
#include <vector>
#include <regolith\graphics\program.h>
#include <regolith\platform\log.h>

namespace regolith {
	namespace graphics {

		Program::Program() : id(glCreateProgram()) {}
		Program::~Program() { glDeleteProgram(id); }

		void Program::link(std::initializer_list<Shader> shaders) {
			for (Shader shader : shaders)
				glAttachShader(id, shader.id);

			glLinkProgram(id);

			for (Shader shader : shaders)
				glDetachShader(id, shader.id);

			// check program
			GLint result = GL_FALSE;
			int len;
			glGetProgramiv(id, GL_COMPILE_STATUS, &result);
			glGetProgramiv(id, GL_INFO_LOG_LENGTH, &len);
			if (len > 0) {
				std::vector<char> msg(len + 1);
				glGetShaderInfoLog(id, len, NULL, &msg[0]);
				if (msg[0] != 0) {
					auto str = std::string(msg.begin(), msg.end());
					for (Shader shader : shaders)
						glDetachShader(id, shader.id);
					throw Program::LinkError{ str };
				}
			}
		}

		void Program::use() {
			glUseProgram(id);
		}
	}
}

