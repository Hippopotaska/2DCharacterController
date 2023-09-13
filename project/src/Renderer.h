#pragma once

#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Camera.h"

// Macro to add break point if error has been encountered
#define ASSERT(x) if ((!x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

// Error checking functions
void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer {
private:
    Camera* mCamera;
    
    inline static Renderer* mInstance = nullptr;

    Renderer();

public:
    static Renderer* GetInstance();

    void Init(Camera* camera);

    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, Shader& shader, const glm::mat4& model) const;

    Renderer(Renderer& other) = delete;
    void operator=(const Renderer&) = delete;
};