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

static struct Player {
    glm::vec3 playerPos;
    float moveSpeed;

    bool moveLeft;
    bool moveRight;
    bool moveUp;
    bool moveDown;
} Player;

static struct WindowData {
    GLFWwindow* window;
    int width;
    int height;
    const char* name;
    bool isOpen;
} WindowData;

struct AABB {
    glm::vec3 position;
    glm::vec2 size;

    AABB(glm::vec3 nPosition, glm::vec2 nSize) {
        position = nPosition;
        size = nSize;
    }
};

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void CollisionDetection(AABB a, AABB b, Shader& blockShader);

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

    Player.playerPos = glm::vec3(0.0f);
    Player.moveSpeed = 200.f;
    Player.moveLeft, Player.moveRight, Player.moveUp, Player.moveDown = false;

    if (!WindowData.window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(WindowData.window);
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

        Shader blockShader("src/shaders/AABBTesting.shader");
        blockShader.Bind();
        blockShader.SetUniform4f("u_Color", 0.0f, 1.0f, 0.0f, 1.0f);

        Shader plShader("src/shaders/Basic.shader");
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

        glm::vec3 blockPosition(150.0f, 0.0f, 0.0f);

        AABB playerCollider(glm::vec3(0.0f), glm::vec2(100.f, 100.f));
        AABB blockCollider(blockPosition, glm::vec2(150.f, 150.f));

        /* Loop until the user closes the window */
        while (WindowData.isOpen) {
            /* Poll for and process events */
            GLCall(glfwPollEvents());
            GLCall(glfwSetKeyCallback(WindowData.window, KeyCallback));

            // CHECK PLAYER MOVEMENT
            if (Player.moveRight) {
                Player.playerPos.x += Player.moveSpeed * deltaTime;
            }
            if (Player.moveLeft) {
                Player.playerPos.x -= Player.moveSpeed * deltaTime;
            }
            if (Player.moveUp) {
                Player.playerPos.y += Player.moveSpeed * deltaTime;
            }
            if (Player.moveDown) {
                Player.playerPos.y -= Player.moveSpeed * deltaTime;
            }

            // Update collider positions
            playerCollider.position = Player.playerPos;
            blockCollider.position = blockPosition;

            // TODO: AABB
            CollisionDetection(playerCollider, blockCollider, blockShader);

            renderer.Clear();

            auto elap = (float)glfwGetTime();
            deltaTime = elap - prev;
            prev = elap;

            glm::mat4 plTransform = glm::translate(glm::mat4(1.0f), Player.playerPos);
            glm::mat4 blockTransform = glm::translate(glm::mat4(1.0f), blockPosition);

            renderer.Draw(va, ib, blockShader, cam, blockTransform);
            renderer.Draw(va, ib, plShader, cam, plTransform);
            std::cout << "Player Position: (" << Player.playerPos.x << ", " << Player.playerPos.y << ")" << std::endl;

            /* Swap front and back buffers */
            GLCall(glfwSwapBuffers(WindowData.window));
        }
    }

    glfwTerminate();
    return 0;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        WindowData.isOpen = false;
    }

    if (key == GLFW_KEY_D) {
        if (action == GLFW_PRESS)
            Player.moveRight = true;
        else if (action == GLFW_RELEASE)
            Player.moveRight = false;
    }
    if (key == GLFW_KEY_A) {
        if (action == GLFW_PRESS)
            Player.moveLeft = true;
        else if (action == GLFW_RELEASE)
            Player.moveLeft = false;
    }
    if (key == GLFW_KEY_W) {
        if (action == GLFW_PRESS)
            Player.moveUp = true;
        else if (action == GLFW_RELEASE)
            Player.moveUp = false;
    }
    if (key == GLFW_KEY_S) {
        if (action == GLFW_PRESS)
            Player.moveDown = true;
        else if (action == GLFW_RELEASE)
            Player.moveDown = false;
    }
}

void CollisionDetection(AABB a, AABB b, Shader& blockShader) {
    blockShader.Bind();
    // Comparison if here; If collision then set the block Shader color to be red and if not then green
    if (a.position.x < b.position.x + b.size.x &&
        a.position.x + a.size.x > b.position.x &&
        a.position.y < b.position.y + b.size.y &&
        a.position.y + a.size.y > b.position.y)
    {
        blockShader.SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
        // TODO: Solve collision
    }
    else
        blockShader.SetUniform4f("u_Color", 0.0f, 1.0f, 0.0f, 1.0f);

    blockShader.Unbind();
}