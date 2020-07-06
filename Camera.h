#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	Camera(float _cameraSpeed, float _sensitivity);
	~Camera();

	void goForwards();
	void goBackwards();
	void goLeft();
	void goRight();
	void goUp();
	void goDown();
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);

	glm::vec3 getCameraPosVector();

	void updateDirection();
	glm::mat4 generateViewMatrix();

private:
	glm::vec3 direction;
	glm::vec3 cameraPos, cameraFront, cameraUp;
	float yaw, pitch;
	float lastX, lastY;
	bool firstMouse;
	float cameraSpeed, sensitivity;
};

