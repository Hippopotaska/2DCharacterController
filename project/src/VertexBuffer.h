#pragma once

class VertexBuffer {
private:
	unsigned int mRendererID;

public:
	VertexBuffer();
	~VertexBuffer();

	void Init(const void* data, unsigned int size);

	void Bind() const;
	void Unbind() const;
};