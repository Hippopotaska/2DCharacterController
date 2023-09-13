#pragma once

#include <glm/glm.hpp>

class Camera {
private:
	glm::mat4 mProjectionMatrix;
	glm::mat4 mViewMatrix;
	glm::mat4 mProjectionViewMatrix;

	glm::vec3 mPosition;

	inline static Camera* mInstance = nullptr;

	Camera();

public:
	void Init(float left, float right, float bottom, float top);
	static Camera* GetInstance();

	const glm::vec3& GetPosition() const { return mPosition; }
	const glm::mat4& GetProjectionMatrix() const { return mProjectionMatrix; }
	const glm::mat4& GetViewMatrix() const { return mViewMatrix; }
	const glm::mat4& GetProjectionViewMatrix() const { return mProjectionViewMatrix; }

	void SetPosition(const glm::vec3& position) { mPosition = position; RecalculateViewMatrix(); }

	Camera(Camera& other) = delete;
	void operator=(const Camera&) = delete;
private:
	void RecalculateViewMatrix();
};