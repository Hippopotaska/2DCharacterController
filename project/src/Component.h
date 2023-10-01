#pragma once

#include "Transform.h"

class Component {
private:
	Transform* mParent = nullptr;

public:
	Transform transform = Transform();

	Component();
	Component(Transform nTransform, Transform* nParent);

	~Component();

	virtual void Update(float deltaTime);
	virtual void LateUpdate(float deltaTime);

	Transform* GetParent();
	void SetParent(Transform* newParent);
};