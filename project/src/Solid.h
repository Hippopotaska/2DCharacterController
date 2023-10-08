#pragma once

#include "GameObject.h"

class Solid : public GameObject {
public:
	// TODO: This constructor has to reworked eventually to add more customisation
	Solid(glm::vec3 pos, glm::vec3 scale);
	~Solid();

	void Update(float deltaTime) override;
};