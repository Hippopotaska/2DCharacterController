#pragma once

#include "Renderer.h"

#include "Transform.h"
#include "Shader.h"
#include "Texture.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

class Sprite {
private:
	Transform mTransform;
	glm::vec3 mColor;
	Shader* mShader = nullptr;
	Texture* mTexture = nullptr;

	VertexArray* mVertexArray = nullptr;
	VertexBuffer mVertexBuffer;
	IndexBuffer* mIndexBuffer = nullptr;
	VertexBufferLayout mVertexBufferLayout;

	void InitSpriteData();

public:
	Sprite(Shader* nShader, Texture* nTexture, Transform nTransform, glm::vec3 nColor);
	~Sprite();

	void DrawSprite();

	inline Transform GetTransform() { return mTransform; }
	inline Shader* GetShader() { return mShader; }
	inline VertexArray* GetVA() { return mVertexArray; }
	inline IndexBuffer* GetIB() { return mIndexBuffer; }

	void SetPosition(glm::vec3 newPos);
};