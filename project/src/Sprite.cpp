#include "Sprite.h"

Sprite::Sprite(Shader* nShader, Texture* nTexture, glm::vec3 nColor, Transform nTransform, Transform* nParent)
	: mShader(nShader), mTexture(nTexture), mColor(nColor), Component(nTransform, nParent) {
	InitSpriteData();
}
Sprite::~Sprite() {}

void Sprite::InitSpriteData() {
	float positions[] = {		// Vertex data
	 -50.0f, -50.0f, 0.0f, 0.0f,
	  50.0f, -50.0f, 1.0f, 0.0f,
	  50.0f,  50.0f, 1.0f, 1.0f,
	 -50.0f,  50.0f, 0.0f, 1.0f
	};

	unsigned int indices[] = {	// Index Buffer
	0, 1, 2,
	2, 3, 0
	};

	unsigned int vao;
	GLCall(glGenVertexArrays(1, &vao));
	GLCall(glBindVertexArray(vao));

	mVertexBuffer.Init(positions, 4 * 4 * sizeof(float));

	mVertexBufferLayout.Push(GL_FLOAT, 2);
	mVertexBufferLayout.Push(GL_FLOAT, 2);

	mVertexArray = new VertexArray();
	mVertexArray->AddBuffer(mVertexBuffer, mVertexBufferLayout);

	mIndexBuffer = new IndexBuffer();
	mIndexBuffer->Init(indices, 6);

	mShader->Bind();
	mShader->SetUniform4f("u_Color", mColor.x / 255, mColor.y / 255, mColor.z / 255, 1.0f);

	mTexture->Bind();
	mShader->SetUniform1i("u_Texture", 0);

	mShader->Unbind();
	mVertexArray->Unbind();
	mVertexBuffer.Unbind();
	mIndexBuffer->Unbind();
}

void Sprite::Update(float deltaTime) {
	DrawSprite();
	Component::Update(deltaTime);
}

void Sprite::DrawSprite() {
	Renderer::GetInstance()->Draw(*this);
}