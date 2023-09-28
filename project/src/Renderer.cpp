#include "Renderer.h"
#include <iostream>

#include "glm/gtc/matrix_transform.hpp"

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

void Renderer::Init(Camera* camera) {
    mCamera = camera;
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
