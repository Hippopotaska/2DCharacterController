#pragma once

#include <glm/glm.hpp>

class Transform {
private:
	glm::mat4 mTransform;
	glm::vec3 mPosition;
public:
	Transform();
	Transform(glm::vec3 position);
	~Transform();

	const glm::vec3& GetPosition() const;
	void SetPosition(glm::vec3& newPos);
};