#include "stdafx.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Kaiser
{
	Camera::Camera(const glm::mat4& projection, const glm::mat4& view) : mProjection(projection), mView(view), mPosition(0)
	{
		RecalculateViewMatrix();
	}
	Camera::Camera(const float dFov, const float width, const float height, const float nearP, const float farP)
		:mProjection(glm::perspectiveFov(glm::radians(dFov), width, height, farP, nearP))
	{
		RecalculateViewMatrix();
	}
	void Camera::RecalculateViewMatrix()
	{

		glm::mat4 trans = glm::translate(glm::mat4(1.0f), mPosition) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(mRotation.x), glm::vec3(1, 0, 0)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(mRotation.y), glm::vec3(0, 1, 0)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(mRotation.z), glm::vec3(0, 0, 1));

		mView = glm::inverse(trans);
		mViewProjection = mProjection * mView;
		
	}
}