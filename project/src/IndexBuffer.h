#pragma once

class IndexBuffer {
private:
	unsigned int mRendererID;
	unsigned int mCount;

public:
	IndexBuffer();
	~IndexBuffer();

	void Init(const unsigned int* data, unsigned int count);

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return mCount; }
};