#include "VAOInfo.h"

VAOInfo::VAOInfo(int _numAttributes) {
	attributes.resize(_numAttributes);
}

void VAOInfo::addAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) {
	if (index >= attributes.size()) {
		std::cout << "Could not assign vertex attribute pointer: index out of bounds." << std::endl;
		return;
	}
	attributes[index] = std::make_tuple(index, size, type, normalized, stride, pointer);
}

