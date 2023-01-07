#include "pch.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


void DrawQuad()
{
	glBegin(GL_QUADS);
	glVertex2d(-0.5f, 0.0f);
	glVertex2d(0.5f, 0.0f);
	glVertex2d(0.5f, 0.5f);
	glVertex2d(-0.5f, 0.5f);
	glEnd();
}

void DrawTriangle()
{
	glBegin(GL_TRIANGLES);
	glVertex2d(-0.5f, -0.5f);
	glVertex2d(0.5f, -0.5f);
	glVertex2d(0.0f, 0.5f);
	glEnd();
}

#if 0

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

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	//glewInit should be called after a valid OpenGL rendering context has been created
	GLenum state = glewInit();

	std::cout << glGetString(GL_VERSION) << std::endl;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		DrawTriangle();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	// free allocated
	glfwTerminate();
	return 0;
}

#endif