#include "Renderer.h"
#include <iostream>

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
    : mCamera(nullptr) {}

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

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, Shader& shader, const glm::mat4& model) const {
    shader.Bind();
    shader.SetUniformMat4("u_ModelViewProjection", mCamera->GetProjectionViewMatrix() * model);
    va.Bind();
    ib.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
