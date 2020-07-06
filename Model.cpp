#include "Model.h"

Model::Model(std::vector<float>& _vertices, VAOInfo& _vaoinfo, Shader& _shader) : vertices(_vertices), vaoinfo(_vaoinfo), shader(_shader)
{
	VAO = VBO = 0;
	this->create();
}

Model::~Model() {}

void Model::create() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * 4, &vertices.front(), GL_STATIC_DRAW);

	GLuint index; GLint size; GLenum type; GLboolean normalized; GLsizei stride; const void* pointer;

	for (auto& attrib : vaoinfo.attributes) {
		std::tie(index, size, type, normalized, stride, pointer) = attrib;
		glVertexAttribPointer(index, size, type, normalized, stride, pointer);
		glEnableVertexAttribArray(index);
	}
}

void Model::draw(GLenum mode, GLsizei verticesPerShape) {
	shader.use();
	glBindVertexArray(VAO);
	glDrawArrays(mode, 0, vertices.size() / verticesPerShape);
	//glBindVertexArray(0);
	//glUseProgram(0);
}

void Model::cleanUp() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}