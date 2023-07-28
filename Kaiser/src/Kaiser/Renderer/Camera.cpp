#include "stdafx.h"
#include "Camera.h"

#include "Kaiser/Core/Input.h"
#include "Kaiser/Core/Time.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glfw/glfw3.h>
#include <glm/gtc/quaternion.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#define M_PI 3.14159f

namespace Kaiser
{
	Camera::Camera(const glm::mat4& projectionMatrix)
		: m_ProjectionMatrix(projectionMatrix)
	{


		m_Position = { -100, 100, 100 };
		m_Rotation = glm::vec3(90.0f, 0.0f, 0.0f);

		m_FocalPoint = glm::vec3(0.0f);
		m_Distance = glm::distance(m_Position, m_FocalPoint);

		m_Yaw = 3.0f * (float)M_PI / 4.0f;
		m_Pitch = M_PI / 4.0f;
	}

	void Camera::Focus()
	{
	}

	std::pair<float, float> Camera::PanSpeed() const
	{
		float x = std::min(m_ViewportWidth / 1000.0f, 2.4f); // max = 2.4f
		float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

		float y = std::min(m_ViewportHeight / 1000.0f, 2.4f); // max = 2.4f
		float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

		return { xFactor, yFactor };
	}

	float Camera::RotationSpeed() const
	{
		return 0.8f;
	}

	float Camera::ZoomSpeed() const
	{
		//float distance = m_Distance * 0.2f;
		//distance = std::max(distance, 0.0f);
		//float speed = distance * distance;
		//speed = std::min(speed, 100.0f); // max speed = 100

		float speed = 5.0f * Time::DeltaTime();
		return speed;
	}

	void Camera::OnUpdate()
	{
		float speed = 30.0f;
		//if (Input::IsKeyPressed(KeyCode::LeftAlt))
		{
			const glm::vec2& mouse{ Input::GetMousePosition().x, Input::GetMousePosition().y };
			glm::vec2 delta = mouse - m_InitialMousePosition;
			m_InitialMousePosition = mouse;
			//delta *= speed * Time::DeltaTime();

			if (Input::IsKeyPressed(KeyCode::LeftAlt))
			{

				if (Input::IsMouseButtonPressed(KeyCode::MouseMiddle))
					MousePan(delta * Time::DeltaTime());
				else if (Input::IsMouseButtonPressed(KeyCode::MouseLeft))
					MouseRotate(delta * Time::DeltaTime());
				else if (Input::IsMouseButtonPressed(KeyCode::MouseRight))
					MouseZoom(speed * delta.y * Time::DeltaTime());
			}
			
			// move forward
			if (Input::IsKeyPressed(KeyCode::W))
				MouseZoom(speed * Time::DeltaTime());
			else if (Input::IsKeyPressed(KeyCode::S))
				MouseZoom(-speed * Time::DeltaTime());
			else if (Input::IsKeyPressed(KeyCode::A))
				MousePan({ speed * Time::DeltaTime(), 0.0f });
			else if (Input::IsKeyPressed(KeyCode::D))
				MousePan({ -speed * Time::DeltaTime(), 0 });
			else if (Input::IsKeyPressed(KeyCode::Q))
				MousePan({ 0, -speed * Time::DeltaTime() });
			else if (Input::IsKeyPressed(KeyCode::E))
				MousePan({ 0, speed * Time::DeltaTime() });
		}

		m_Position = CalculatePosition();

		glm::quat orientation = GetOrientation();
		m_Rotation = glm::eulerAngles(orientation) * (180.0f / (float)M_PI);
		m_ViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 1)) * glm::toMat4(glm::conjugate(orientation)) * glm::translate(glm::mat4(1.0f), -m_Position);
		m_ViewMatrix = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(orientation);
		m_ViewMatrix = glm::inverse(m_ViewMatrix);
	}

	void Camera::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(KS_BIND_EVENT_FN(Camera::OnMouseScroll));
	}

	bool Camera::OnMouseScroll(MouseScrolledEvent& e)
	{

		float delta = e.GetYOffset() * 5 ;
		MouseZoom(delta * Time::DeltaTime());
		return false;
	}

	void Camera::MousePan(const glm::vec2& delta)
	{
		//auto [xSpeed, ySpeed] = PanSpeed();
		m_FocalPoint += -GetRightDirection() * delta.x;//* 1.0f * m_Distance;
		m_FocalPoint += GetUpDirection() * delta.y;// *1.0f * m_Distance;
	}

	void Camera::MouseRotate(const glm::vec2& delta)
	{
		float yawSign = GetUpDirection().y < 0 ? -1.0f : 1.0f;
		m_Yaw += yawSign * delta.x;// *RotationSpeed();
		m_Pitch += delta.y;// *RotationSpeed();
	}

	void Camera::MouseZoom(float delta)
	{
		m_Distance -= delta;// *ZoomSpeed();
		if (m_Distance < 1.0f)
		{
			m_FocalPoint += GetForwardDirection() * delta;
			m_Distance = 1.0f;
		}
	}

	glm::vec3 Camera::GetUpDirection()
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	glm::vec3 Camera::GetRightDirection()
	{
		return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
	}

	glm::vec3 Camera::GetForwardDirection()
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
	}

	glm::vec3 Camera::CalculatePosition()
	{
		// calculate the camera's position using the distance from the focal point and yaw and pitch
		return m_FocalPoint - GetForwardDirection() * m_Distance;
	}

	glm::quat Camera::GetOrientation()
	{
		return glm::quat(glm::vec3(-m_Pitch, -m_Yaw, 0.0f));
	}


















	/*Camera::Camera(const glm::mat4& projection, const glm::mat4& view) : mProjection(projection), mView(view), mPosition(0)
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
		
	}*/
}