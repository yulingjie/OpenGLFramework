#ifndef __CAMERA_H__
#define __CAMERA_H__
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

class Camera
{
public:
	Camera();
	void SetCameraPos(const glm::vec3 &cameraPos) {
		mCameraPos = cameraPos;
	}
	~Camera()
	{

	}

	void LookAt(const glm::vec3 & cameraTarget, const glm::vec3& up);
private:
	glm::vec3 mCameraTarget;
	glm::vec3 mCameraPos;
	glm::vec3 mUp;
};

#endif 
