#include <regolith\graphics\private\xgl.h> // TODO: remove, only graphics should use
#include <regolith\core\view.h>
#include <regolith\math\vector.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

using namespace regolith::graphics;

static const char vertexShaderSource[] = "\
	#version 100															\n\
																			\n\
	attribute vec3 vertexPosition_modelspace;								\n\
																			\n\
	// Values that stay constant for the whole mesh.						\n\
	uniform mat4 MVP;														\n\
																			\n\
	void main(){															\n\
		gl_Position = MVP * vec4(vertexPosition_modelspace, 1);				\n\
	}																		\n\
";

static const char fragmentShaderSource[] = "\
	#version 100															\n\
																			\n\
	void main() {															\n\
		gl_FragColor = vec4(1, 0, 0, 1);									\n\
	}																		\n\
";

#if 0
#include <string>
#include <fstream>
using namespace std;

std::string readFile(const char* path) {
	std::string out;
	std::ifstream file(path, std::ios::in);
	if (file.is_open()) {
		std::string Line = "";
		while (getline(file, Line))
			out += "\n" + Line;
		file.close();
	}
	else {
		throw std::exception("File not found!");
	}
	return out;
}
#endif

namespace regolith {
	namespace logic {
		
		View::View() {
			Shader vertexShader(Shader::Vertex, vertexShaderSource);
			Shader fragmentShader(Shader::Fragment, fragmentShaderSource);

			// Link the program
			program.link({ vertexShader, fragmentShader });
			
			// Set vertex data
			math::Vector<3> triangle[] = {
				-1.0f, -1.0f, 0.0f,
				1.0f, -1.0f, 0.0f,
				0.0f,  1.0f, 0.0f,
			};
			geometry.set(triangle, 3);
			
		}
		View::~View() {	}

		void View::update() {
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(0.0f, 1.0f, 0.5f, 1.0f);

			program.use();

			// -- TODO: Memoization!! --
			// Projection matrix : Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
			glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
			// Or, for an ortho camera :
			//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

			// Camera matrix
			glm::mat4 View = glm::lookAt(
				glm::vec3(3, 3, 3), // Camera is at (4,3,3), in World Space
				glm::vec3(0, 0, 0), // and looks at the origin
				glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
			);
			// Model matrix : an identity matrix (model will be at the origin)
			glm::mat4 Model = glm::mat4(1.0f);
			// Our ModelViewProjection : multiplication of our 3 matrices
			glm::mat4 MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around

			// Get a handle for our "MVP" uniform
			uint32 matrixId = glGetUniformLocation(program.id, "MVP");
			//--

			// Send our transformation to the currently bound shader, 
			// in the "MVP" uniform
			glUniformMatrix4fv(matrixId, 1, GL_FALSE, &MVP[0][0]);


			geometry.draw();
		}

	}
}