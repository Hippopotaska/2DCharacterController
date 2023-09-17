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
        float mult = 50.f;
        Camera* camera = camera->GetInstance();
        camera->Init(-1.6f * mult, 1.6f * mult, -0.9f * mult, 0.9f * mult);

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        Renderer* renderer = renderer->GetInstance();
        renderer->Init(camera);


#pragma region Rendering Test
        float positions[] = {		// Vertex data
        -50.0f, -50.0f, 0.0f, 0.0f,
         50.0f, -50.0f, 1.0f, 0.0f,
         50.0f,  50.0f, 1.0f, 1.0f,
        -50.0f,  50.0f, 0.0f, 1.0f
        };

        unsigned int indices[] = {	// Index Buffer
        0, 1, 2,
        2, 3, 0
        };

        unsigned int vao;
        GLCall(glGenVertexArrays(1, &vao));
        GLCall(glBindVertexArray(vao));

        VertexBuffer vb;
        vb.Init(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout vbl;
        vbl.Push(GL_FLOAT, 2);
        vbl.Push(GL_FLOAT, 2);

        VertexArray va;
        va.AddBuffer(vb, vbl);

        IndexBuffer ib;
        ib.Init(indices, 6);

        Shader shader("src/shaders/Basic.glsl");
        shader.Bind();
        shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

        Texture texture("res/textures/Cyndaquil.jpg");
        shader.SetUniform1i("u_Texture", 0);

        shader.Unbind();
        va.Unbind();
        vb.Unbind();
        ib.Unbind();
#pragma endregion

        float deltaTime = 0;
        float prev = 0;

        Transform playerTransform(glm::mat4(1.0f), glm::vec3(0.0f), glm::vec3(1.0f));
        playerTransform.transform = glm::translate(glm::mat4(1.0f), playerTransform.position);

        AABB playerCollider(playerTransform, glm::vec2(100,100));
        Shader* playerShader = new Shader("src/shaders/Basic.glsl");
        Texture* playerTexture = new Texture("res/textures/Pixel.png");
        Sprite playerSprite(playerShader, playerTexture, playerTransform, glm::vec3(1.0f, 1.0f, 1.0f));
        
        Transform solidTransform(glm::mat4(1.0f), glm::vec3(150.0f, 0.0f, 0.0f), glm::vec3(1.0f));
        solidTransform.transform = glm::translate(glm::mat4(1.0f), solidTransform.position);
        
        AABB solidCollider(solidTransform, glm::vec2(100, 100));
        Shader* solidShader = new Shader("src/shaders/Basic.glsl");
        Texture* solidTexture = new Texture("res/textures/Pixel.png");
        Sprite solidSprite(solidShader, solidTexture, solidTransform, glm::vec3(1.0f, 1.0f, 0.0f));

        Player* player = new Player(playerTransform, playerCollider, playerSprite, 200.f);
        Solid* solid = new Solid(solidTransform, solidCollider, solidSprite);
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
            solid->Update(deltaTime);

#pragma region Rendering Test      
            shader.Bind();

            glm::mat4 projection = camera->GetProjectionMatrix();
            glm::mat4 view = camera->GetViewMatrix();
            glm::mat4 model = glm::translate(glm::mat4(1.0f), playerTransform.position);

            glm::mat4 mvp = projection * view * model;

            shader.SetUniformMat4("u_ModelViewProjection", mvp);
            va.Bind();
            ib.Bind();

            GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
#pragma endregion



            if (inputMgr->IsKeyHeld(GLFW_KEY_ESCAPE)) {
                WindowData.isOpen = false;
            }

            renderer->Clear();
            GLCall(glClear(GL_COLOR_BUFFER_BIT));

            /* Swap front and back buffers */
            GLCall(glfwSwapBuffers(WindowData.window));
        }
    }

    glfwTerminate();
    return 0;
}