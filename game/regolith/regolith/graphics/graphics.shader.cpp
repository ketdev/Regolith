#include <regolith\graphics\private\xgl.h>
#include <vector>
#include <regolith\graphics\shader.h>
#include <regolith\platform\log.h>

namespace regolith {
	namespace graphics {

		static uint32 glShaderType(Shader::Type type) {
			switch (type) {
			case Shader::Vertex:
				return GL_VERTEX_SHADER;
			case Shader::Fragment:
				return GL_FRAGMENT_SHADER;
			}
			return 0;
		}



		Shader::Shader(Type type, const std::string& code)
			: id(glCreateShader(glShaderType(type))) {
			const char* c_code = code.c_str();
			glShaderSource(id, 1, &c_code, NULL);
			glCompileShader(id);

			// check shader
			GLint result = GL_FALSE;
			int len;
			glGetShaderiv(id, GL_COMPILE_STATUS, &result);
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
			if (len > 0) {
				std::vector<char> msg(len + 1);
				glGetShaderInfoLog(id, len, NULL, &msg[0]);
				if (msg[0] != 0) {
					auto str = std::string(msg.begin(), msg.end());
					throw Shader::CompileError{ str };
				}
			}
		}
		Shader::~Shader() {
			glDeleteShader(id);
		}

	}
}

