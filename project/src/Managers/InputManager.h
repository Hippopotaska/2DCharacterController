#pragma once
#ifdef _WIN32_WINDOWS
#undef _WIN32_WINDOWS
#endif
#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif

#define _WIN32_WINDOWS 0x0501
#define _WIN32_WINNT   0x0501

// https://www.geeksforgeeks.org/ascii-table/
#define Keyboard_Esc 27
#define Keyboard_W 87
#define Keyboard_A 65 
#define Keyboard_S 83
#define Keyboard_D 68
#define Keyboard_Space VK_SPACE
#define Keyboard_R 32

#include <windows.h>

#include <unordered_map>

struct KeyState {
	bool keyUp;
	bool keyDown;
	bool keyHeld;
	bool keyReleased;

	KeyState() {
		keyUp = true;
		keyDown = false;
		keyHeld = false;
		keyReleased = false;
	}
};

class InputManager {
private:
	std::unordered_map<int, KeyState> mKeys = {
		{Keyboard_Esc, KeyState()},
			
		{Keyboard_W, KeyState()},
		{Keyboard_S, KeyState()},
		{Keyboard_D, KeyState()},
		{Keyboard_A, KeyState()},

		{Keyboard_Space, KeyState()},
		{Keyboard_R, KeyState()},
	};

	inline static InputManager* mInstance = nullptr;
	InputManager();

	void UpdateInput(bool state, int key);

public:
	static InputManager* GetInstance();

	void Update();

	bool KeyHeld(int key);
	bool KeyPressed(int key);
	bool KeyReleased(int key);

	InputManager(InputManager& other) = delete;
	void operator=(const InputManager&) = delete;
};