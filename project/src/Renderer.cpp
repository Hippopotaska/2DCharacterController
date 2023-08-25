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

void Renderer::Clear() const {
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, Shader& shader, const Camera& camera, const glm::mat4& model) const {
    shader.Bind();
    shader.SetUniformMat4("u_ModelViewProjection", camera.GetProjectionViewMatrix() * model);
    va.Bind();
    ib.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
