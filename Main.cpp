#include "OpenGLEngine.h"

int main() {

	OpenGLEngine renderer;

	renderer.lightPos.x = -1.0f;
	renderer.lightPos.y = 4.0f;
	renderer.lightPos.z = -1.0f;

	renderer.runRenderer();

	return 0;
}