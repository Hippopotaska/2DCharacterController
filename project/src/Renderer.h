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

    float mSmoothMult = 8.25f;

    // This looks a bit too jarring, needs to be fixed
    float mLookAheadMult = 0.f;
    
    inline static Renderer* mInstance = nullptr;

    Renderer();

public:
    static Renderer* GetInstance();

    void Init(Camera* camera);

    void Clear() const;
    void Draw(class Sprite& spr);

    void MoveCamera(glm::vec3 newPos);

    Renderer(Renderer& other) = delete;
    void operator=(const Renderer&) = delete;
};