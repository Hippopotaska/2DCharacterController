#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(std::string& texturePath) 
	: mTexture(texturePath) {}
SpriteRenderer::SpriteRenderer(std::string& texturePath, glm::vec4 color) 
	: mTexture(texturePath), mColor(color) {}

SpriteRenderer::~SpriteRenderer() {}

void SpriteRenderer::SetColor(glm::vec4& nColor) {
	mColor = nColor;
}

const Texture& SpriteRenderer::GetTexture() const {
	return mTexture;
}

const glm::vec4& SpriteRenderer::GetColor() const {
	return mColor;
}