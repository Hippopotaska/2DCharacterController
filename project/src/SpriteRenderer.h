#pragma once

#include <glm/glm.hpp>

#include "Texture.h"

class SpriteRenderer {
private:
	Texture mTexture;
	glm::vec4 mColor;
public:
	SpriteRenderer(std::string& texturePath);
	SpriteRenderer(std::string& texturePath, glm::vec4 color);
	~SpriteRenderer();

	void SetColor(glm::vec4& nColor);

	const Texture& GetTexture() const;
	const glm::vec4& GetColor() const;
};