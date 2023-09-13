#pragma once

#include <string>

#include "Transform.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

class Sprite {
private:
	Transform mTransform;

	VertexArray* mVertexArray = nullptr;
	VertexBuffer* mVertexBuffer = nullptr;
	VertexBufferLayout* mLayout = nullptr;
	IndexBuffer* mIndexBuffer = nullptr;

	Shader* mShader = nullptr;
	Texture* mTexture = nullptr;

public:
	Sprite(Transform nTransform, std::string shaderSrc);
	~Sprite();

	void Draw();

	void SetTexture(std::string textureSrc);

	void SetPosition(glm::vec3 newPosition);
	glm::vec3 GetPosition();
};