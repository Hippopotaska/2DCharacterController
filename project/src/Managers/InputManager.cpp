#include "InputManager.h"

#include <iostream>
#include <WinUser.h>

InputManager::InputManager() {}

InputManager* InputManager::GetInstance() {
    if (!mInstance)
        mInstance = new InputManager();
    return mInstance;
}

void InputManager::Update() {
    uint8_t keyStates[256]{ 0 };
    auto ret = GetKeyboardState(keyStates);

    bool state;
    for (size_t i = 0; i < 256; i++) {
        state = (keyStates[i] & 0x80) != 0;
        UpdateInput(state, i);
    }
}

void InputManager::UpdateInput(bool state, int key) {
    if (!mKeys.contains(key))
        return;

    const bool held = KeyHeld(key);

    mKeys.at(key).keyHeld = state;

    mKeys.at(key).keyDown = !state && held;
    mKeys.at(key).keyUp = !state && held;
}

bool InputManager::KeyHeld(int key) {
    return mKeys.at(key).keyHeld;
}
bool InputManager::KeyPressed(int key) {
    return mKeys.at(key).keyDown;
}
bool InputManager::KeyReleased(int key) {
    return mKeys.at(key).keyUp;
}