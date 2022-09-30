// https://docs.gl/

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

//https://docs.gl/

struct Shaders
{
	std::string VertexShader;
	std::string FragmentShader;
};

static Shaders ParaseShader(const std::string& filePath)
{
	std::ifstream stream(filePath);
	stream.open(filePath, std::ios_base::out);

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

	stream.close();
	return { source[0].str(),source[1].str() };
}

static uint32_t CompileShader(uint32_t type, const std::string& source)
{
	uint32_t id = glCreateShader(type);
	const char* src = source.c_str();
	const int HOW_MANY_SHADERS = 1;
	glShaderSource(id, HOW_MANY_SHADERS, &src, NULL);//Replaces the source code in a shader object
	glCompileShader(id);

	//Compile Error Handling
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);

		std::cout << "Shader Compile Error in " << (type == GL_FRAGMENT_SHADER ? "fragment Shader: " : "vertex Shader: ") << std::endl;
		std::cout << message;
		glDeleteShader(id);

		return 0;
	}


	return id;
}

static uint32_t CreateShader(const std::string& fragmentShader, const std::string& vertexShader)
{
	// creates an empty program object, is an object to which shader objects can be attached
	uint32_t programm = glCreateProgram();

	uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	uint32_t vs = CompileShader(GL_VERTEX_SHADER, vertexShader);

	glAttachShader(programm, fs);
	glAttachShader(programm, vs);

	glLinkProgram(programm);//links any attached shader to program
	glValidateProgram(programm); // checks, if can execute given the current OpenGL state

	glDeleteShader(fs);
	glDeleteShader(vs);

	return programm;
}

int main()
{
	/* Initialize the library */
	if (!glfwInit())
	{
		return -1;
	}

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);// Make the window's context current 
	GLenum state = glewInit();//glewInit should be called after a valid OpenGL rendering context has been created
	std::cout << glGetString(GL_VERSION) << std::endl;// GPU driver and OpenGL Information


	float positions[6]
	{
		-0.5f , -0.5f,
		 0.5f , -0.5f,
		 0.0f ,  0.5f
	};

	uint32_t bufferName;
	int numberOfBuffers = 1;
	glGenBuffers(numberOfBuffers, &bufferName);
	glBindBuffer(GL_ARRAY_BUFFER, bufferName);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

	/* tell OpenGL how to read vertexBuffer
	 * (index, size_of_values_per_vertex, type, if_values_are_normlized, offset_between_vertecis, offset_of_attribute)
	*/
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	glEnableVertexAttribArray(0);//should be called for glVertexAttribPointer

	Shaders shadersSource = ParaseShader("res/shaders/Basic.shader");
	uint32_t programm = CreateShader(shadersSource.FragmentShader, shadersSource.VertexShader);
	glUseProgram(programm);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		// because we generate and bind the buffer outside the loop, OpenGL knows which buffer should be drawn
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);//Swap front and back buffers

		/* Poll for and process events */
		glfwPollEvents();
	}

	// free allocated
	glDeleteProgram(programm);
	glfwTerminate();
	return 0;
}