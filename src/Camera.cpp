#include "Camera.h"
#include <glm/ext.hpp>
Camera::Camera()
{

}
Camera::~Camera()
{

}
void Camera::LookAt(const glm::vec3 & cameraTarget, const glm::vec3& up)
{
	mCameraTarget = cameraTarget;
	mUp = up;
	glm::mat4x4 V = glm::lookAt(mCameraPos, mCameraTarget, mUp);

	
}
