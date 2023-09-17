#include "Solid.h"

Solid::Solid(Transform nTransform, AABB nCollider, Sprite nSprite) 
	: mTransform(nTransform), mCollider(nCollider), mSprite(nSprite) {}
Solid::~Solid() {}

void Solid::Update(float deltaTime) {
	mSprite.DrawSprite();
}

Transform Solid::GetTransform() {
	return mTransform;
}
AABB Solid::GetCollider() {
	return mCollider;
}