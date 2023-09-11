#include "Solid.h"

Solid::Solid(Transform nTransform, AABB nCollider) 
	: mTransform(nTransform), mCollider(nCollider) {}
Solid::~Solid() {}

Transform Solid::GetTransform() {
	return mTransform;
}
AABB Solid::GetCollider() {
	return mCollider;
}