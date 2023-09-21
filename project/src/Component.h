#pragma once

#include "Transform.h"

class Component {
private:
	Transform* mParent = nullptr;

public:
	Transform transform = Transform();

	Component(Transform nTransform, Transform* nParent);

	~Component();

	virtual void Update(float deltaTime);

	Transform* GetParent();
	void SetParent(Transform* newParent);
};