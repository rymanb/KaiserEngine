#pragma once

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>

namespace Kaiser
{

	class Camera
	{
	public:
		Camera() = default;
		Camera(const glm::mat4& projection, const glm::mat4& view);
		Camera(const float dFov, const float width, const float height, const float nearP, const float farP);
		virtual ~Camera() = default;

		const glm::mat4& GetProjection() const { return mProjection; }
		//const glm::mat4& GetUnReversedProjection() const { return mUnReversedProjection; }
		const glm::mat4& GetView() const { return mView; }
		const glm::mat4& GetViewProjection() const { return mViewProjection; }
		
		void SetProjection(const glm::mat4 proj, const glm::mat4 view)
		{
			mProjection = proj;
			mView = view;

			mViewProjection = mProjection * mView;
		}

		void SetPerspectiveProjection(const float radFov, const float width, const float height, const float nearP, const float farP)
		{
			mProjection = glm::perspectiveFov(radFov, width, height, farP, nearP);
			//mUnReversedProjection = glm::perspectiveFov(radFov, width, height, farP, nearP);
			mViewProjection = mProjection * mView;
			
			
			
		}

		void SetOrthoProjection(const float width, const float height, const float nearP, const float farP)
		{
			mProjection = glm::ortho(-width * 0.5f, width * 0.5f, -height * 0.5f, height * 0.5f,nearP, farP);

			mViewProjection = mProjection * mView;
		}
		
		//float GetExposure() const { return mExposure; }
		//float& GetExposure() { return mExposure; }

		void SetPosition(const glm::vec3& pos) {
			mPosition = pos; RecalculateViewMatrix();
		}
		void SetRotation(const glm::vec3& rot) {
			mRotation = rot; RecalculateViewMatrix();
		}

		void SetRotation(float rot)
		{
			mRotation = glm::vec3(0, 0, rot); RecalculateViewMatrix();
		}

		const glm::vec3& GetPosition() const { return mPosition; }
		const glm::vec3& GetRotation() const { return mRotation; }
		
	protected:
		//float mExposure = 0.8f;
		
	private:

		void RecalculateViewMatrix();

		glm::mat4 mProjection = glm::mat4(1.0f);
		glm::mat4 mView = glm::mat4(1.0f);

		glm::mat4 mViewProjection = glm::mat4(1.0f);

		glm::vec3 mPosition;
		glm::vec3 mRotation = glm::vec3(0, 0, 0);
	};


}