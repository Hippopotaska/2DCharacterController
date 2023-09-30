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

bool InputManager::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (!mKeys.contains(key))
        return false;
    
    if (action == GLFW_PRESS) {
        mKeys.at(key) = true;
        return true;
    }
    else if (action == GLFW_RELEASE) {
        mKeys.at(key) = false;
        return true;
    }
    else {
        return false;
    }
}

void InputManager::KeyCallbackDispatcher(GLFWwindow* window, int key, int scancode, int action, int mods) {
    mInstance->KeyCallback(window, key, scancode, action, mods);
}

bool InputManager::KeyHeld(int key) {
    return mKeys.at(key);
}
bool InputManager::KeyPressed(int key) {
    return mInstance->KeyCallback(mWindow, key, 1, GLFW_PRESS, 1);
}
bool InputManager::KeyReleased(int key) {
    return mInstance->KeyCallback(mWindow, key, 1, GLFW_RELEASE, 1);
}