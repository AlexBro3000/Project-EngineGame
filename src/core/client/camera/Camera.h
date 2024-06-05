#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../../utils/DefiningTypes.hpp"
#include "../../../system/window/Window.h"

// ��������� ������
const float SPEED       = 1.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM        = 80.0f;
// ��������� ��������
const float ASPECT      = (float)Window::getWidth() / (float)Window::getHeight();
const float NEAR        = 0.1f;
const float FAR         = 100.0f;


class Camera
{
private:
	// ������� ������  (������������ ����� ��������)
	glm::vec3	position;
	// ������� ������
	glm::vec3	rotate;

	// ������� ������������� ������
    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;

	// ��������� ������
    float speed;
    float sensitivity;
	float zoom;

    // ��������� ��������
    float aspect;
    float near;
    float far;


public:
	Camera(
		glm::vec3 position, glm::vec3 rotate,
		float speed = SPEED, float sensitivity = SENSITIVITY, float zoom = ZOOM, float aspect = ASPECT, float near = NEAR, float far = FAR
	);
	~Camera();

	glm::vec3 getPosition();

	// ��������� ������� ��������
	glm::mat4 getProjection();
	// ��������� ������� ����
	glm::mat4 getView();

	void Camera::toPosition(glm::vec3 position, float time = 1.0f);
	void Camera::toRotate(glm::vec3 rotate, float time = 1.0f);

private:
	void updatePositionData();
	void updateRotateData();
};