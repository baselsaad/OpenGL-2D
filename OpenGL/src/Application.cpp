#include <GLFW/glfw3.h>
#include <iostream>

#include "Timer.h"


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

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);


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

	glfwTerminate();
	return 0;
}