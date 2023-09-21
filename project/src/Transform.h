#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

class Transform {
private:
	glm::mat4 mTransform;
	glm::vec3 mPosition;
	glm::vec3 mScale;
	
	void Init(glm::mat4 nTransform, glm::vec3 nPosition, glm::vec3 nScale);

public:
	Transform();
	Transform(Transform& nTransform);
	Transform(glm::mat4 nTransform, glm::vec3 nPosition, glm::vec3 nScale);

	void Translate();

	glm::mat4* GetTransform();
	void SetTransform(glm::mat4 newTransform);
	glm::vec3* GetPosition();
	void SetPosition(glm::vec3 newPosition);
	glm::vec3* GetScale();
	void SetScale(glm::vec3 newScale);
};