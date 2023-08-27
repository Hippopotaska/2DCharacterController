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

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

namespace Player {
    static glm::vec3 playerPos(0.0f);
    static float deltaTime = 0.0f;
    static float moveSpeed = 200.0f;

    static bool moveLeft = false;
    static bool moveRight = false;
    static bool moveUp = false;
    static bool moveDown = false;
}

namespace WindowData {
    static GLFWwindow* window = nullptr;
    static float width = 1280;
    static float height = 720;
    static std::string name = "2D Character Controller";
    static bool isOpen = true;
};

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main(void) {
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    WindowData::window = glfwCreateWindow(WindowData::width, WindowData::height, WindowData::name.c_str(), NULL, NULL);
    if (!WindowData::window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(WindowData::window);
    glfwSwapInterval(1);

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

        Shader shader("src/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

        Texture texture("res/textures/Cyndaquil.jpg");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        Renderer renderer;

        Player::deltaTime = 0;
        float prev = 0;
        float n = 0;
        float incr = 0.05f;

        /* Loop until the user closes the window */
        while (WindowData::isOpen) {
            /* Poll for and process events */
            GLCall(glfwPollEvents());
            GLCall(glfwSetKeyCallback(WindowData::window, KeyCallback));

            // CHECK PLAYER MOVEMENT
            if (Player::moveRight) {
                Player::playerPos.x += Player::moveSpeed * Player::deltaTime;
            }
            if (Player::moveLeft) {
                Player::playerPos.x -= Player::moveSpeed * Player::deltaTime;
            }
            if (Player::moveUp) {
                Player::playerPos.y += Player::moveSpeed * Player::deltaTime;
            }
            if (Player::moveDown) {
                Player::playerPos.y -= Player::moveSpeed * Player::deltaTime;
            }


            renderer.Clear();

            auto elap = glfwGetTime();
            Player::deltaTime = elap - prev;
            prev = elap;

            glm::mat4 transform = glm::translate(glm::mat4(1.0f), Player::playerPos);

            renderer.Draw(va, ib, shader, cam, transform);
            std::cout << "Player Position: (" << Player::playerPos.x << ", " << Player::playerPos.y << ")" << std::endl;

            /* Swap front and back buffers */
            GLCall(glfwSwapBuffers(WindowData::window));
        }
    }

    glfwTerminate();
    return 0;
}
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        WindowData::isOpen = false;
    }
    
    if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        Player::moveRight = true;
    }
    if (key == GLFW_KEY_D && action == GLFW_RELEASE) {
        Player::moveRight = false;
    } 

    if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        Player::moveLeft = true;
    }
    if (key == GLFW_KEY_A && action == GLFW_RELEASE) {
        Player::moveLeft = false;
    }

    if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        Player::moveUp = true;
    }
    if (key == GLFW_KEY_W && action == GLFW_RELEASE) {
        Player::moveUp = false;
    }

    if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        Player::moveDown = true;
    }
    if (key == GLFW_KEY_S && action == GLFW_RELEASE) {
        Player::moveDown = false;
    }
}