#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "Camera.h"

#include <iostream>

#include "glm/gtc/matrix_transform.hpp"

#include "Managers/GameManager.h"

#include "Player.h"
#include "Shader.h"
#include "Sprite.h"

// Error checking functions
void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << "): " << function <<
            "\n" << file << " : Line " << line << std::endl;
        return false;
    }
    return true;
}

// Renderer class functions
Renderer::Renderer() 
    : mCamera(nullptr) {
    GLCall(glClearColor(0.42f, 0.42f, 0.42f, 1));
}

Renderer* Renderer::GetInstance() {
    if (!mInstance)
        mInstance = new Renderer();
    return mInstance;
}

void Renderer::Init() {
    float mult = 250.f;
    mCamera = mCamera->GetInstance();
    mCamera->Init(-1.6f * mult, 1.6f * mult, -0.9f * mult, 0.9f * mult);
}

void Renderer::Clear() const {
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(Sprite& spr) {
    Shader* shader = spr.GetShader();
    shader->Bind();

    shader->SetUniformMat4("u_ModelViewProjection", mCamera->GetProjectionViewMatrix() * *spr.GetParent()->GetTransform());
    spr.GetVA()->Bind();
    spr.GetIB()->Bind();

    GLCall(glDrawElements(GL_TRIANGLES, spr.GetIB()->GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::MoveCamera(glm::vec3 newPos) {
    GameManager* gameMGR = GameManager::GetInstance();
    newPos += gameMGR->GetPlayerRef()->GetMoveDirection() * mLookAheadMult;

    glm::vec3 movement = glm::mix(mCamera->GetPosition(), newPos, mSmoothMult * gameMGR->GetDeltaTime());
    mCamera->SetPosition(movement);
}