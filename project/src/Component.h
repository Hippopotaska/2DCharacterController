#pragma once

#include "Transform.h"

class Component {
private:
	Transform* mParent = nullptr;
	Transform mTransform = Transform();

public:
	Component(Transform nTransform, Transform* nParent);

	~Component();

	virtual void Update(float deltaTime);

	glm::vec3 GetPosition();
	void SetPosition(glm::vec3 newPos);
	Transform GetTransform();

	Transform* GetParent();
	void SetParent(Transform* newParent);
};