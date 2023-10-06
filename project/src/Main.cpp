#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

#include "Camera.h"
#include "Renderer.h"

#include "Managers/InputManager.h"
#include "Managers/GameManager.h"

#include "Player.h"
#include "Solid.h"
#include "Transform.h"

static struct WindowData {
    GLFWwindow* window;
    int width;
    int height;
    const char* name;
    bool isOpen;
} WindowData;

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

    if (!WindowData.window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(WindowData.window);
    glfwSwapInterval(1);

    InputManager* inputMgr = inputMgr->GetInstance();
    inputMgr->SetWindow(WindowData.window);

    GameManager* gameMgr = gameMgr->GetInstance();

    // Initialize GLEW
    if (glewInit() != GLEW_OK)
        std::cout << "Error setting up GLEW!" << std::endl;
    else
        std::cout << "GLEW set up correctly" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        // Create camera
        float mult = 250.f;
        Camera* camera = camera->GetInstance();
        camera->Init(-1.6f * mult, 1.6f * mult, -0.9f * mult, 0.9f * mult);

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        Renderer* renderer = renderer->GetInstance();
        renderer->Init(camera);

        Transform* plT = new Transform();
        Transform* sldT1 = new Transform(glm::mat4(1.0f), glm::vec3(0.f, -150.f, 0.f), glm::vec3(5.0f, 0.85f, 1.0f));
        Transform* sldT2 = new Transform(glm::mat4(1.0f), glm::vec3(100.f, -100.f, 0.f), glm::vec3(1.5f, 1.0f, 1.0f));
        Transform* sldT3 = new Transform(glm::mat4(1.0f), glm::vec3(0.f, 150.f, 0.f), glm::vec3(4.f, 0.75f, 1.0f));

        Player* player = new Player(plT, 50.f);
        Solid* solid1 = new Solid(sldT1);
        Solid* solid2 = new Solid(sldT2);
        Solid* solid3 = new Solid(sldT3);
        
        std::vector<Solid*> level;
        level.push_back(solid1);
        level.push_back(solid2);
        level.push_back(solid3);

        gameMgr->Init(player, level);

        float frames = 0;
        float fps = 0;
        
        /* Loop until the user closes the window */
        while (WindowData.isOpen) {
            /* Poll for and process events */
            GLCall(glfwPollEvents());
            GLCall(glfwSetKeyCallback(WindowData.window, InputManager::KeyCallbackDispatcher));

            renderer->Clear();
            gameMgr->GameTime->UpdateTime();
            frames++;
            gameMgr->Update();

            if (inputMgr->KeyPressed(GLFW_KEY_ESCAPE)) {
                WindowData.isOpen = false;
            }

            fps = frames / gameMgr->GameTime->delta;
            frames = 0;

            std::cout << "Cur FPS: " << fps << std::endl;

            /* Swap front and back buffers */
            GLCall(glfwSwapBuffers(WindowData.window));
        }
    }

    glfwTerminate();
    return 0;
}