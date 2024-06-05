#include "Camera.h"


Camera::Camera(glm::vec3 position, glm::vec3 rotate, float speed, float sensitivity, float zoom, float aspect, float near, float far) :
	position(position), rotate(rotate), speed(speed), sensitivity(sensitivity), zoom(zoom), aspect(aspect), near(near), far(far)
{
	updatePositionData();
	updateRotateData();
}

Camera::~Camera()
{
}

glm::vec3 Camera::getPosition()
{
	return position;
}

glm::mat4 Camera::getProjection()
{
	aspect = (float)Window::getWidth() / (float)Window::getHeight();
	return glm::perspective(glm::radians(zoom), aspect, near, far);
}

glm::mat4 Camera::getView()
{
	return glm::lookAt(position, position + front, up);
}

void Camera::toPosition(glm::vec3 position, float time)
{
	this->position += front * position.z * time;
	this->position += right * position.x * time;
	this->position += up * position.y * time;
	updatePositionData();
}

void Camera::toRotate(glm::vec3 rotate, float time)
{
	this->rotate += rotate * time;
	updateRotateData();
}

void Camera::updatePositionData()
{
}

void Camera::updateRotateData()
{
	glm::mat4 rotation = glm::mat4(1.0f);
	rotation = glm::rotate(rotation, glm::radians(rotate.z), glm::vec3(0, 0, 1));
	rotation = glm::rotate(rotation, glm::radians(rotate.y), glm::vec3(0, 1, 0));
	rotation = glm::rotate(rotation, glm::radians(rotate.x), glm::vec3(1, 0, 0));
	front = glm::vec3(rotation * glm::vec4(0, 0, -1, 1));
	right = glm::vec3(rotation * glm::vec4(1, 0, 0, 1));
	up = glm::vec3(rotation * glm::vec4(0, 1, 0, 1));
}