#pragma once

#include "Kaiser/Core/Core.h"
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "Kaiser/Core/Events/Event.h"
#include "Kaiser/Core/Events/MouseEvent.h"

namespace Kaiser
{

	//class Camera
	//{
	//public:
	//	Camera() = default;
	//	Camera(const glm::mat4& projection, const glm::mat4& view);
	//	Camera(const float dFov, const float width, const float height, const float nearP, const float farP);
	//	virtual ~Camera() = default;

	//	const glm::mat4& GetProjection() const { return mProjection; }
	//	//const glm::mat4& GetUnReversedProjection() const { return mUnReversedProjection; }
	//	const glm::mat4& GetView() const { return mView; }
	//	const glm::mat4& GetViewProjection() const { return mViewProjection; }
	//	
	//	void SetProjection(const glm::mat4 proj, const glm::mat4 view)
	//	{
	//		mProjection = proj;
	//		mView = view;

	//		mViewProjection = mProjection * mView;
	//	}

	//	void SetPerspectiveProjection(const float radFov, const float width, const float height, const float nearP, const float farP)
	//	{
	//		mProjection = glm::perspectiveFov(radFov, width, height, farP, nearP);
	//		//mUnReversedProjection = glm::perspectiveFov(radFov, width, height, farP, nearP);
	//		mViewProjection = mProjection * mView;
	//		
	//		
	//		
	//	}

	//	void SetOrthoProjection(const float width, const float height, const float nearP, const float farP)
	//	{
	//		mProjection = glm::ortho(-width * 0.5f, width * 0.5f, -height * 0.5f, height * 0.5f,nearP, farP);

	//		mViewProjection = mProjection * mView;
	//	}
	//	
	//	//float GetExposure() const { return mExposure; }
	//	//float& GetExposure() { return mExposure; }

	//	void SetPosition(const glm::vec3& pos) {
	//		mPosition = pos; RecalculateViewMatrix();
	//	}
	//	void SetRotation(const glm::vec3& rot) {
	//		mRotation = rot; RecalculateViewMatrix();
	//	}

	//	void SetRotation(float rot)
	//	{
	//		mRotation = glm::vec3(0, 0, rot); RecalculateViewMatrix();
	//	}

	//	const glm::vec3& GetPosition() const { return mPosition; }
	//	const glm::vec3& GetRotation() const { return mRotation; }
	//	
	//protected:
	//	//float mExposure = 0.8f;
	//	
	//private:

	//	void RecalculateViewMatrix();

	//	glm::mat4 mProjection = glm::mat4(1.0f);
	//	glm::mat4 mView = glm::mat4(1.0f);

	//	glm::mat4 mViewProjection = glm::mat4(1.0f);

	//	glm::vec3 mPosition;
	//	glm::vec3 mRotation = glm::vec3(0, 0, 0);
	//};

	class Camera
	{
	public:
		Camera() = default;
		Camera(const glm::mat4& projectionMatrix);

		void Focus();
		void OnUpdate();
		void OnEvent(Event& e);

		inline float GetDistance() const { return m_Distance; }
		inline void SetDistance(float distance) { m_Distance = distance; }

		inline void SetProjectionMatrix(const glm::mat4& projectionMatrix) { m_ProjectionMatrix = projectionMatrix; }
		inline void SetViewportSize(uint32_t width, uint32_t height) { m_ViewportWidth = width; m_ViewportHeight = height; }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjection() const { return m_ProjectionMatrix * m_ViewMatrix; }

		glm::vec3 GetUpDirection();
		glm::vec3 GetRightDirection();
		glm::vec3 GetForwardDirection();
		const glm::vec3& GetPosition() const { return m_Position; }

		float GetExposure() const { return m_Exposure; }
		float& GetExposure() { return m_Exposure; }
	private:
		bool OnMouseScroll(MouseScrolledEvent& e);

		void MousePan(const glm::vec2& delta);
		void MouseRotate(const glm::vec2& delta);
		void MouseZoom(float delta);

		glm::vec3 CalculatePosition();
		glm::quat GetOrientation();

		std::pair<float, float> PanSpeed() const;
		float RotationSpeed() const;
		float ZoomSpeed() const;
	private:
		glm::mat4 m_ProjectionMatrix, m_ViewMatrix;
		glm::vec3 m_Position, m_Rotation, m_FocalPoint, mWorldPos;

		bool m_Panning, m_Rotating;
		glm::vec2 m_InitialMousePosition;
		glm::vec3 m_InitialFocalPoint, m_InitialRotation;

		float m_Distance;
		float m_Pitch, m_Yaw;

		float m_Exposure = 0.8f;

		uint32_t m_ViewportWidth = 1280, m_ViewportHeight = 720;
	};

}