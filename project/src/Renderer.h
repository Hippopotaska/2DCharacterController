#pragma once

#include <GL/glew.h>

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
    void Draw(class Sprite& spr);

    Renderer(Renderer& other) = delete;
    void operator=(const Renderer&) = delete;
};