#pragma once

#include <iostream>
#include <tuple>
#include <vector>
#include <glad/glad.h>

class VAOInfo {
public:
	VAOInfo(int _numAttributes);
	void addAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);

	std::vector<std::tuple<GLuint, GLint, GLenum, GLboolean, GLsizei, const void*>> attributes; // tuple contains arguments of glVertexAttribPointer
};