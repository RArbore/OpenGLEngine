#include "Camera.h"

Camera::Camera(float _cameraSpeed, float _sensitivity) {
	cameraPos = glm::vec3(0.0f, 5.0f, 0.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	yaw = 0.0f;
	pitch = 0.0f;

	firstMouse = false;

	cameraSpeed = _cameraSpeed;
	sensitivity = _sensitivity;
}

Camera::~Camera() {}

void Camera::goForwards() {
	cameraPos += cameraSpeed * cameraFront;
}

void Camera::goBackwards() {
	cameraPos -= cameraSpeed * cameraFront;
}

void Camera::goLeft() {
	cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void Camera::goRight() {
	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void Camera::goUp() {
	cameraPos += cameraSpeed * cameraUp;
}

void Camera::goDown() {
	cameraPos -= cameraSpeed * cameraUp;
}

void Camera::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float deltaX = xpos - lastX;
	float deltaY = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	deltaX *= sensitivity;
	deltaY *= sensitivity;

	yaw += deltaX;
	pitch += deltaY;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
}

glm::vec3 Camera::getCameraPosVector() {
	return cameraPos;
}

void Camera::updateDirection() {
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw));
	direction.y = 0.0f;
	direction.z = sin(glm::radians(yaw));
	cameraFront = glm::normalize(direction);
}

glm::mat4 Camera::generateViewMatrix() {
	glm::mat4 view = glm::mat4(1.0f);
	
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction = glm::normalize(direction);

	view = glm::lookAt(cameraPos, cameraPos + direction, cameraUp);
	return view;
}