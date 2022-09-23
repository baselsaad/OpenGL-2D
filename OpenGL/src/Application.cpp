// https://docs.gl/

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

//https://docs.gl/

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
		-0.5f,-0.5f,
		 0.5f,-0.5f,
		 0.0f, 0.5f
	};
	unsigned int buffer;

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		// because we generate and bind the buffer outside the loop, OpenGL works like state-machine, so it knows which buffer should be drawn
		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* Poll for and process events */
		glfwPollEvents();
	}

	// free allocated
	glfwTerminate();
	return 0;
}