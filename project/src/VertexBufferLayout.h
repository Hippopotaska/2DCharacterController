#pragma once

#include <vector>
#include "Renderer.h"

struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int SizeofType(unsigned int type) {
		switch (type) {
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_UNSIGNED_BYTE:	return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout {
private:
	std::vector<VertexBufferElement> mElements;
	unsigned int mStride;

public:
	VertexBufferLayout()
		: mStride(0) {}

	void Push(unsigned int type, unsigned int count) {
		mElements.push_back({ type, count, GL_FALSE });
		mStride += count * VertexBufferElement::SizeofType(type);
	}

	inline const std::vector<VertexBufferElement> GetElements() const { return mElements; }
	inline unsigned int GetStride() const { return mStride; }
};