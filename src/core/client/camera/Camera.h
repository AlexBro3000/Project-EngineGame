#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../../utils/DefiningTypes.hpp"
#include "../../../system/window/Window.h"

// Параметры камеры
const float SPEED       = 1.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM        = 80.0f;
// Параметры проекции
const float ASPECT      = (float)Window::getWidth() / (float)Window::getHeight();
const float NEAR        = 0.1f;
const float FAR         = 100.0f;


class Camera
{
private:
	// Позиция камеры  (Относительно точки смещения)
	glm::vec3	position;
	// Поворот камеры
	glm::vec3	rotate;

	// Векторы направлености камеры
    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;

	// Параметры камеры
    float speed;
    float sensitivity;
	float zoom;

    // Параметры проекции
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

	// Получение матрицы проекции
	glm::mat4 getProjection();
	// Получение матрицы вида
	glm::mat4 getView();

	void Camera::toPosition(glm::vec3 position, float time = 1.0f);
	void Camera::toRotate(glm::vec3 rotate, float time = 1.0f);

private:
	void updatePositionData();
	void updateRotateData();
};