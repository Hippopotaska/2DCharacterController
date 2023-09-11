#pragma once

#include "Component.h"
#include "Transform.h"

class AABB : Component{
private:
	Transform mTransform;

	glm::vec2 mSize;

public:
	AABB(Transform nTransform, glm::vec2 nSize);
	~AABB();

	void Update(float deltaTime) override;

	void SetPosition(glm::vec3 newPos);
	glm::vec3 GetPosition();
	
	float GetWidth();
	float GetHeight();
};