#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define ASSERT(x) if (!(x)) __debugbreak();

#define GL_CALL(x)									\
	GlClearErros();									\
	x;												\
	ASSERT(GlLogCall(#x, __FILE__, __LINE__))

static void GlClearErros()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GlLogCall(const char* functionName, const char* fileName, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << fileName << ": " << functionName << " at Line (" << line << ")" << std::endl;
		printf("OpenGL-Error: %.6x (%d)", error, error);

		return false;
	}


	return true;
}

static void Callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length
	, const GLchar* message, const void* userParam)
{
#if 0
	std::cout << "Error: " << message << std::endl;
	__debugbreak();
#endif
}
