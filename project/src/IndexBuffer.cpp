#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer() : mCount(0), mRendererID(0) {}
IndexBuffer::~IndexBuffer() {
    GLCall(glDeleteBuffers(1, &mRendererID));
}

void IndexBuffer::Init(const unsigned int* data, unsigned int count) {
    mCount = count;

    GLCall(glGenBuffers(1, &mRendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

void IndexBuffer::Bind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID));
}

void IndexBuffer::Unbind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
