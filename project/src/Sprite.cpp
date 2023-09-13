#include "Sprite.h"

Sprite::Sprite(Transform nTransform, std::string shaderSrc) 
	: mTransform(nTransform), mTexture(nullptr), mShader(nullptr) {
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

	mVertexBuffer = new VertexBuffer(positions, 4 * 4 * sizeof(float));
	
	mIndexBuffer = new IndexBuffer(indices, 6);

	mLayout = new VertexBufferLayout();
	mLayout->Push(GL_FLOAT, 2);
	mLayout->Push(GL_FLOAT, 2);

	mVertexArray = new VertexArray();
	mVertexArray->AddBuffer(*mVertexBuffer, *mLayout);

	mShader = new Shader(shaderSrc);
	mShader->Bind();
	mShader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

	mShader->Unbind();
	mVertexArray->Unbind();
	mVertexBuffer->Unbind();
	mIndexBuffer->Unbind();
}
Sprite::~Sprite() {}

void Sprite::Draw() {
		//https://stackoverflow.com/questions/29925106/how-to-access-a-singleton-from-other-classes-c
		Renderer::GetInstance()->Draw(*mVertexArray, *mIndexBuffer, *mShader, mTransform.transform);
}

void Sprite::SetTexture(std::string textureSrc) {
	mTexture = new Texture(textureSrc);
	mTexture->Bind();
	mShader->SetUniform1i("u_Texture", 0);
}

void Sprite::SetPosition(glm::vec3 newPosition) {
	mTransform.position = newPosition;
}
glm::vec3 Sprite::GetPosition() {
	return mTransform.position;
}