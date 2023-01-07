#pragma once
class PlayerInput;
class DeltaTime;
class OpenGLWindow;

class Layer
{
public:
	virtual void OnStart(OpenGLWindow* window) {}
	virtual void OnUpdate(const DeltaTime& deltaTime) {}
	virtual void OnDestroy() {}

	virtual void SetupPlayerInput(PlayerInput* input) {}
};
