// https://docs.gl/

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


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
	// GPU driver and OpenGL Information
	std::cout << glGetString(GL_VERSION) << std::endl;


	float positions[6]
	{
		-0.5f,-0.5f,
		 0.5f,-0.5f,
		 0.0f, 0.5f
	};

	unsigned int buffer;
	/*
	*	n		-	Specifies the number of buffer object names to be generated.
	*	buffer	-	Specifies the name of a buffer object.
	*/
	glGenBuffers(1, &buffer);

	/*
	*	target - to which the buffer object is bound
	*	buffer - Specifies the name of a buffer object.
	*/
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	/*
	*	target - to which the buffer object is bound
	*	size   - Specifies the size in bytes of the buffer object's new data store.
	*	data   - Specifies a pointer to data that will be copied into the data store for initialization, or NULL if no data is to be copied.
	*   usage  - Specifies the expected usage pattern of the data store
	*/
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

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