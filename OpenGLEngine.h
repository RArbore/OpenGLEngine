#include <iostream>
#include <sstream>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <algorithm>
#include "Camera.h"
#include "Shader.h"
#include "VAOInfo.h"
#include "Model.h"

class OpenGLEngine {

public:

	std::vector<float> vertices;

	glm::vec3 lightPos;

	int runRenderer();

};