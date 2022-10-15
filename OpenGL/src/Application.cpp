// https://docs.gl/

#include "Renderer.h"
#include "VertextBuffer.h"
#include "IndexBuffer.h"

#include <fstream>
#include <string>
#include <sstream>

struct Shaders
{
	std::string VertexShader;
	std::string FragmentShader;
};

static Shaders ParaseShader(const std::string& filePath)
{
	std::ifstream stream(filePath);
	enum class ParsingState
	{
		None = -1, Vertex = 0, Fragment = 1
	};

	ParsingState state = ParsingState::None;
	std::string line;
	std::stringstream source[2];//two shaders

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				state = ParsingState::Vertex;
			else if (line.find("fragment") != std::string::npos)
				state = ParsingState::Fragment;
		}
		else
		{
			source[(uint32_t)state] << line << '\n';
		}
	}

	return { source[0].str(),source[1].str() };
}

static uint32_t CompileShader(uint32_t type, const std::string& source)
{
	uint32_t id = glCreateShader(type);
	const char* src = source.c_str();
	const int HOW_MANY_SHADERS = 1;
	GL_CALL(glShaderSource(id, HOW_MANY_SHADERS, &src, NULL));//Replaces the source code in a shader object
	GL_CALL(glCompileShader(id));

	//Compile Error Handling
	int result;
	GL_CALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		GL_CALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		GL_CALL(glGetShaderInfoLog(id, length, &length, message));

		std::cout << "Shader Compile Error in " << (type == GL_FRAGMENT_SHADER ? "fragment Shader: " : "vertex Shader: ") << std::endl;
		std::cout << message;
		GL_CALL(glDeleteShader(id));

		return 0;
	}


	return id;
}

static uint32_t CreateShader(const std::string& fragmentShader, const std::string& vertexShader)
{
	// creates an empty program object.
	// program object is an object to which shaders can be attached
	uint32_t programm = glCreateProgram();

	uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	uint32_t vs = CompileShader(GL_VERTEX_SHADER, vertexShader);

	GL_CALL(glAttachShader(programm, fs));
	GL_CALL(glAttachShader(programm, vs));

	GL_CALL(glLinkProgram(programm));//links any attached shader to program
	GL_CALL(glValidateProgram(programm)); // checks, if can execute given the current OpenGL state

	GL_CALL(glDeleteShader(fs));
	GL_CALL(glDeleteShader(vs));

	return programm;
}

int main()
{
	/* Initialize the library */
	if (!glfwInit())
	{
		return -1;
	}

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE); //should be called for glDebugMessageCallback
	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);// Make the window's context current 
	glfwSwapInterval(true); // vsync
	GLenum state = glewInit();//glewInit should be called after a valid OpenGL rendering context has been created

	GL_CALL(glDebugMessageCallback(Callback, nullptr));
	std::cout << glGetString(GL_VERSION) << std::endl;// GPU driver and OpenGL Information

	// Each "Line" for X , Y 
	float positions[2 * 4] =
	{
		-0.5f , -0.5f, // 0 bottom_left 
		 0.5f , -0.5f, // 1 bottom_right
		 0.5f ,  0.5f, // 2 top_right
		-0.5f ,  0.5f  // 3 top_left
	};
	VertexBuffer* vertextBuffer = new VertexBuffer(positions, 2 * 4 * sizeof(float));

	uint32_t indices[6] =
	{
		0, 1, 2,
		2, 3, 0
	};
	IndexBuffer* indexBuffer = new IndexBuffer(indices, 6);

	/**************************************************
	 *				3 * * * * * * * * * * * 2
	 *				*					*   *
	 *				* 			   *		*
	 *				*  		  *				*
	 * 				*  	  *					*
	 * 				*  *					*
	 * 				0 * * * * * * * * * * * 1
	 **************************************************/


	/* tell OpenGL how to read vertexBuffer
	 * (index, size_of_values_per_vertex, type, if_values_are_normlized, offset_between_vertecis, offset_of_attribute)
	*/
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	glEnableVertexAttribArray(0);//should be called for glVertexAttribPointer

	// Shaders
	Shaders shadersSource = ParaseShader("res/shaders/Basic.shader");
	uint32_t programm = CreateShader(shadersSource.FragmentShader, shadersSource.VertexShader);
	GL_CALL(glUseProgram(programm)); //bind shaders

	GL_CALL(int location = glGetUniformLocation(programm, "u_Color"));
	ASSERT(location != -1);
	GL_CALL(glUniform4f(location, 1.0f, 0.5f, 0.0f, 1.0f));
	float r = 0.0f;
	float increamnt = 0.03f;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

		GL_CALL(glUseProgram(programm)); //bind shaders
		GL_CALL(glUniform4f(location, r, 0.5f, 0.0f, 1.0f));

		// because we generate and bind the buffer outside the loop, OpenGL knows which buffer should be drawn
		indexBuffer->Bind();
		GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

		if (r > 1.0f || r < 0.0f)
			increamnt *= -1;

		r += increamnt;

		GL_CALL(glfwSwapBuffers(window));//Swap front and back buffers

		/* Poll for and process events */
		GL_CALL(glfwPollEvents());
	}

	GL_CALL(glDeleteProgram(programm));
	// should be delete before glfwTerminate
	delete indexBuffer;
	delete vertextBuffer;
	glfwTerminate();

	return 0;
}