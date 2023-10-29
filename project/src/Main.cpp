#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

#include "Managers/GameManager.h"
#include "Renderer.h"

int main(void) {
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    WindowData.width = 1280;
    WindowData.height = 720;
    WindowData.name = "2D Character Controller";
    WindowData.isOpen = true;
    WindowData.window = glfwCreateWindow(WindowData.width, WindowData.height, WindowData.name, NULL, NULL);

    /* Make the window's context current */
    glfwMakeContextCurrent(WindowData.window);
    glfwSwapInterval(1);

    // Initialize GLEW
    if (glewInit() != GLEW_OK)
        std::cout << "Error setting up GLEW!" << std::endl;
    else
        std::cout << "GLEW set up correctly" << std::endl;

    Renderer* renderer = renderer->GetInstance();
    renderer->Init();

    InputManager* inputMgr = inputMgr->GetInstance();
    GameManager* gameMgr = gameMgr->GetInstance();
    UIManager* uiMgr = uiMgr->GetInstance();

    if (!WindowData.window) {
        glfwTerminate();
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        gameMgr->Init();
        uiMgr->Init(gameMgr->GetPlayerRef(), WindowData.window);

        while (WindowData.isOpen) {
            GLCall(glfwPollEvents());

            if (inputMgr->KeyPressed(Keyboard_Esc)) {
                WindowData.isOpen = false;
            }

            renderer->Clear();
            gameMgr->Update();
            uiMgr->Update();

            GLCall(glfwSwapBuffers(WindowData.window));
        }
    }

    uiMgr->Stop();
    glfwTerminate();
    return 0;
}