#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

#include "thirdparty/imgui/imgui.h"
#include "thirdparty/imgui/imgui_impl_glfw.h"
#include "thirdparty/imgui/imgui_impl_opengl3.h"

#include "Camera.h"
#include "Renderer.h"

#include "Managers/InputManager.h"
#include "Managers/GameManager.h"
#include "Managers/CollisionManager.h"

#include "Player.h"
#include "Solid.h"
#include "Transform.h"

// Move window stuff into a new class OR the game manager
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

        gameMgr->Init();

        // Move time stuff into the game manager, since it should work there normally
        float lastFrameTime = 0.f;
        float time = 0.f;
        float delta = 0.f;

        // ImGui Test
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(WindowData.window, true);
        ImGui_ImplOpenGL3_Init();
        float f = 0;

        /* Loop until the user closes the window */
        while (WindowData.isOpen) {
            // Get time stuff
            time = (float)glfwGetTime();
            delta = time - lastFrameTime;
            lastFrameTime = time;

            // ImGui create new frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            /* Poll for and process events */
            GLCall(glfwPollEvents());

            renderer->Clear();
            gameMgr->Update(delta);

            if (inputMgr->KeyPressed(Keyboard_Esc)) {
                WindowData.isOpen = false;
            }

            // ImGui window settings
            ImGui::Begin("Settings");
            ImGui::Text("Hello user!");
            ImGui::SliderFloat("Character Speed", &f, 0.f, 1.0f);
            ImGui::End();

            // ImGui rendering things
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            GLCall(glfwSwapBuffers(WindowData.window));
        }
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}