#include "Solid.h"

#include "Transform.h"
#include "AABB.h"
#include "Sprite.h"

// TODO: This constructor has to reworked eventually to add more customisation
Solid::Solid(Transform* nTransform) {
	SetTransform(nTransform);
	Transform* transform = GetTransform();

	AABB* collider = new AABB(*transform, transform, glm::vec2(100.0f));

	Shader* shader = new Shader("src/shaders/Basic.glsl");
	Texture* texture = new Texture("res/textures/Pixel.png");
	Sprite* sprite = new Sprite(shader, texture, glm::vec3(1.0f, 0.0f, 1.0f), *transform, transform);

	AddComponent(collider);
	AddComponent(sprite);

	collider->SetParent(transform);
	sprite->SetParent(transform);
}
Solid::~Solid() {}

void Solid::Update(float deltaTime) {
	GameObject::Update(deltaTime);
}