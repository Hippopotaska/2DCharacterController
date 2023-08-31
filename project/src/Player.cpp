#include "Player.h"

Player::Player(Transform transform, AABB collider, float moveSpeed) 
	: mTransform(transform), mCollider(collider), mMoveSpeed(moveSpeed) {}
Player::~Player() {

}