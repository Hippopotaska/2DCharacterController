#pragma once
#include <GLFW/glfw3.h>

#include <unordered_map>

class InputManager {
private:
	GLFWwindow* mWindow;
	std::unordered_map<int, bool> mKeys = {
		{256, false},	// Escape
		
		{65, false},	// A
		{83, false},	// S
		{68, false},	// D
		{87, false},	// W

		{32, false},	// Space
	};

	inline static InputManager* mInstance = nullptr;

	InputManager();

public:
	void SetWindow(GLFWwindow* nWindow);

	static InputManager* GetInstance();

	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void KeyCallbackDispatcher(GLFWwindow* window, int key, int scancode, int action, int mods);

	bool IsKeyHeld(int key);
	bool KeyIsPressed(int key);
	bool KeyIsReleased(int key);

	InputManager(InputManager& other) = delete;
	void operator=(const InputManager&) = delete;
};