#pragma once

#include "Component.h"

#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

class Sprite : public Component {
private:
	glm::vec3 mColor;
	Shader* mShader = nullptr;
	Texture* mTexture = nullptr;

	VertexArray* mVertexArray = nullptr;
	VertexBuffer mVertexBuffer;
	IndexBuffer* mIndexBuffer = nullptr;
	VertexBufferLayout mVertexBufferLayout;

	void InitSpriteData();

public:
	Sprite(Shader* nShader, Texture* nTexture, glm::vec3 nColor, Transform nTransform, Transform* nParent);
	~Sprite();

	void Update(float deltaTime) override;
	void DrawSprite();

	inline Shader* GetShader() { return mShader; }
	inline VertexArray* GetVA() { return mVertexArray; }
	inline IndexBuffer* GetIB() { return mIndexBuffer; }

	void SetPosition(glm::vec3 newPos);
};