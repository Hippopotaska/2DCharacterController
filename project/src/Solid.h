#pragma once

#include "GameObject.h"

class Solid : public GameObject {
public:
	// TODO: This constructor has to reworked eventually to add more customisation
	Solid(Transform* nTransform);
	~Solid();

	void Update(float deltaTime) override;
};