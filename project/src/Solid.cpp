#include "Solid.h"

#include "Transform.h"
#include "AABB.h"
#include "Sprite.h"

// TODO: This constructor has to reworked eventually to add more customisation
Solid::Solid(glm::vec3 pos, glm::vec3 scale) {
	transform = new Transform(glm::mat4(1.0f), pos, scale);

	AABB* collider = new AABB(*transform, transform, glm::vec2(100.0f, 100.0f), true);

	Shader* shader = new Shader("src/shaders/Basic.glsl");
	Texture* texture = new Texture("res/textures/Pixel.png");
	Sprite* sprite = new Sprite(shader, texture, glm::vec3(217, 217, 217), *transform, transform);

	AddComponent(collider);
	AddComponent(sprite);

	collider->SetParent(transform);
	sprite->SetParent(transform);
}
Solid::~Solid() {}

void Solid::Update(float deltaTime) {
	GameObject::Update(deltaTime);
}