#pragma once

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

struct Transform {
	glm::mat4 transform;
	glm::vec3 position;
	glm::vec3 scale;

	Transform(glm::mat4 nTransform, glm::vec3 nPosition, glm::vec3 nScale) {
		transform = nTransform;
		position = nPosition;
		scale = nScale;
	}
};