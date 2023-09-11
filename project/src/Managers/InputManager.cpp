#include "InputManager.h"

InputManager::InputManager() {
    mWindow = nullptr;
}

void InputManager::SetWindow(GLFWwindow* nWindow) {
    this->mWindow = nWindow;
}

InputManager* InputManager::GetInstance() {
    if (!mInstance)
        mInstance = new InputManager();
    return mInstance;
}

void InputManager::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (!mKeys.contains(key))
        return;
    
    if (action == GLFW_PRESS)
        mKeys.at(key) = true;
    else if (action == GLFW_RELEASE)
        mKeys.at(key) = false;
}

void InputManager::KeyCallbackDispatcher(GLFWwindow* window, int key, int scancode, int action, int mods) {
    mInstance->KeyCallback(window, key, scancode, action, mods);
}

bool InputManager::IsKeyHeld(int key) {
    return mKeys.at(key);
}