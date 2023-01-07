#include "pch.h"
#include "Application.h"

int main()
{
	Debug::Init("Sandbox-App");
	Application app;
	app.Run();

	return 0;
}