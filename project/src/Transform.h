#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

struct Transform {
	glm::mat4 transform;
	glm::vec3 position;
	glm::vec3 scale;

	Transform() {
		transform = glm::mat4(1.0f);
		position = glm::vec3(0.0f);
		scale = glm::vec3(1.0f);

		transform = glm::translate(glm::mat4(1.0f), position);
	}

	Transform(glm::mat4 nTransform, glm::vec3 nPosition, glm::vec3 nScale) {
		transform = nTransform;
		position = nPosition;
		scale = nScale;

		transform = glm::translate(glm::mat4(1.0f), position);
	}

	Transform(Transform& nTransform) {
		Transform(nTransform.transform, nTransform.position, nTransform.scale);
	}
};