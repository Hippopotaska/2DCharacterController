#pragma once
#include <GLFW/glfw3.h>
#include <unordered_map>

class InputManager {
private:
	GLFWwindow* mWindow;
	std::unordered_map<int, bool> mKeys = {
		{GLFW_KEY_ESCAPE, false},
		
		{GLFW_KEY_A, false},
		{GLFW_KEY_S, false},
		{GLFW_KEY_D, false},
		{GLFW_KEY_W, false},

		{GLFW_KEY_SPACE, false},
		{GLFW_KEY_R, false},
	};

	inline static InputManager* mInstance = nullptr;

	InputManager();

public:
	void SetWindow(GLFWwindow* nWindow);

	static InputManager* GetInstance();

	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void KeyCallbackDispatcher(GLFWwindow* window, int key, int scancode, int action, int mods);

	bool KeyHeld(int key);
	bool KeyPressed(int key);
	bool KeyReleased(int key);

	InputManager(InputManager& other) = delete;
	void operator=(const InputManager&) = delete;
};