#pragma once

#include "Transform.h"

struct AABB {
    glm::vec3 position;
    glm::vec2 size;

    AABB(glm::vec3 nPosition, glm::vec2 nSize) {
        position = nPosition;
        size = nSize;
    }
};

class AABB {
private:
	Transform mTransform;
public:
	AABB(Transform transform);
	~AABB();

	void Update(float deltaTime);
};