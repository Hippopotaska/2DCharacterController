#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "Camera.h"

#include "Managers/InputManager.h"
#include "Managers/GameManager.h"

#include "Player.h"
#include "Solid.h"
#include "Transform.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

static struct WindowData {
    GLFWwindow* window;
    int width;
    int height;
    const char* name;
    bool isOpen;
} WindowData;


//void CollisionDetection(AABB a, AABB b, Shader& blockShader);
//void DoCollisions();

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
        Camera cam(-1.6f * mult, 1.6f * mult, -0.9f * mult, 0.9f * mult);

        // Assigning vertex data
        float positions[] = {
            -50.0f, -50.0f, 0.0f, 0.0f,
             50.0f, -50.0f, 1.0f, 0.0f,
             50.0f,  50.0f, 1.0f, 1.0f,
            -50.0f,  50.0f, 0.0f, 1.0f
        };

        // Index buffering
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        // Creating a vertex array and binding it
        unsigned int vao;
        GLCall(glGenVertexArrays(1, &vao));
        GLCall(glBindVertexArray(vao));

        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push(GL_FLOAT, 2);
        layout.Push(GL_FLOAT, 2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        Shader blockShader("src/shaders/AABBTesting.glsl");
        blockShader.Bind();
        blockShader.SetUniform4f("u_Color", 0.0f, 1.0f, 0.0f, 1.0f);

        Shader plShader("src/shaders/Basic.glsl");
        plShader.Bind();
        plShader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

        Texture texture("res/textures/Cyndaquil.jpg");
        texture.Bind();
        plShader.SetUniform1i("u_Texture", 0);

        blockShader.Unbind();
        plShader.Unbind();
        va.Unbind();
        vb.Unbind();
        ib.Unbind();

        Renderer renderer;

        float deltaTime = 0;
        float prev = 0;

        Transform playerTransform(glm::mat4(1.0f), glm::vec3(0.0f), glm::vec3(1.0f));
        AABB playerCollider(playerTransform, glm::vec2(100,100));

        Transform SolidTransform(glm::mat4(1.0f), glm::vec3(150.0f, 0.0f, 0.0f), glm::vec3(1.0f));
        AABB solidCollider(SolidTransform, glm::vec2(100, 100));

        SolidTransform.transform = glm::translate(glm::mat4(1.0f), SolidTransform.position);

        Player* player = new Player(playerTransform, playerCollider, 200.f);
        Solid* solid = new Solid(SolidTransform, solidCollider);

        std::vector<Solid*> level;
        level.push_back(solid);

        gameMgr->Init(player, level);

        /* Loop until the user closes the window */
        while (WindowData.isOpen) {
            /* Poll for and process events */
            GLCall(glfwPollEvents());
            GLCall(glfwSetKeyCallback(WindowData.window, InputManager::KeyCallbackDispatcher));

            auto elap = (float)glfwGetTime();
            deltaTime = elap - prev;
            prev = elap;

            gameMgr->Update(deltaTime);

            player->Update(deltaTime);

            if (inputMgr->IsKeyHeld(GLFW_KEY_ESCAPE)) {
                WindowData.isOpen = false;
            }
            renderer.Clear();

            renderer.Draw(va, ib, blockShader, cam, solid->GetTransform().transform);
            renderer.Draw(va, ib, plShader, cam, player->GetTransform().transform);
            //std::cout << "Player Position: (" << player->GetTransform().position.x << ", " << player->GetTransform().position.y << ")" << std::endl;

            /* Swap front and back buffers */
            GLCall(glfwSwapBuffers(WindowData.window));
        }
    }

    glfwTerminate();
    return 0;
}