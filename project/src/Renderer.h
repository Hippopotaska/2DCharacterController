#pragma once

#include <GL/glew.h>

// Macro to add break point if error has been encountered
#define ASSERT(x) if ((!x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

// Error checking functions
void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);