#pragma once

#include <vector>
#include <tuple>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "VAOInfo.h"
#include "Shader.h"

class Model {
public:
	Model(std::vector<float>& _vertices, VAOInfo& _vaoinfo, Shader& _shader);
	~Model();

	void draw(GLenum mode, GLsizei verticesPerShape);

	void cleanUp(); // delete VBO and VAO

private:
	VAOInfo& vaoinfo;
	Shader& shader;
	unsigned int VAO, VBO;
	std::vector<float> vertices;

	void create();
};

