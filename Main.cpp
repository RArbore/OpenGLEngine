#include "OpenGLEngine.h"
#include <vector>
#include <tuple>
#include <stdlib.h>

std::vector<std::vector<float>> generateSurface() {
	std::vector<std::vector<float>> ret;
	for (int x = 0; x < 200; x++) {
		ret.push_back(std::vector<float>());
		for (int z = 0; z < 200; z++) {
			float random = ((float)(rand() % 100))/100.0f;
			ret.at(x).push_back(1.0f + random);
		}
	}
	return ret;
}

std::tuple<float, float, float> getNorm(std::tuple<float, float, float> p1, std::tuple<float, float, float> p2, std::tuple<float, float, float> p3) {
	std::tuple<float, float, float> A = { std::get<0>(p2) - std::get<0>(p1), std::get<1>(p2) - std::get<1>(p1), std::get<2>(p2) - std::get<2>(p1) };
	std::tuple<float, float, float> B = { std::get<0>(p3) - std::get<0>(p1), std::get<1>(p3) - std::get<1>(p1), std::get<2>(p3) - std::get<2>(p1) };
	std::tuple<float, float, float> ret = {
		std::get<1>(A) * std::get<2>(B) - std::get<2>(A) * std::get<1>(B),
		std::get<2>(A) * std::get<0>(B) - std::get<0>(A) * std::get<2>(B),
		std::get<0>(A) * std::get<1>(B) - std::get<1>(A) * std::get<0>(B)
	};
	return ret;
}

void addTuplesToVertices(std::vector<float> *vertices, std::vector<std::tuple<float, float, float>> tuples) {
	for (auto tuple : tuples) {
		vertices->push_back(std::get<0>(tuple));
		vertices->push_back(std::get<1>(tuple));
		vertices->push_back(std::get<2>(tuple));
	}
}

int main() {

	OpenGLEngine renderer;

	renderer.lightPos.x = -1.0f;
	renderer.lightPos.y = 4.0f;
	renderer.lightPos.z = -1.0f;

	std::vector<std::vector<float>> surface = generateSurface();

	for (int x = 0; x < 199; x++) {
		for (int z = 0; z < 199; z++) {
			std::tuple<float, float, float> p1 = {x, surface.at(x).at(z), z};
			std::tuple<float, float, float> p2 = {x+1, surface.at(x+1).at(z), z};
			std::tuple<float, float, float> p3 = {x, surface.at(x).at(z+1), z+1};
			std::tuple<float, float, float> color = {((float)(rand() % 256))/256.0f, ((float)(rand() % 256))/256.0f, ((float)(rand() % 256))/256.0f};
			std::tuple<float, float, float> norm = getNorm(p1, p2, p3);
			std::vector<std::tuple<float, float, float>> tuples = { p1, color, norm, p2, color, norm, p3, color, norm };
			addTuplesToVertices(&renderer.vertices, tuples);

			p1 = {x+1, surface.at(x+1).at(z), z};
			p2 = {x, surface.at(x).at(z+1), z+1};
			p3 = {x+1, surface.at(x+1).at(z+1), z+1};
			color = {((float)(rand() % 256))/256.0f, ((float)(rand() % 256))/256.0f, ((float)(rand() % 256))/256.0f};
			norm = getNorm(p1, p2, p3);
			tuples = { p1, color, norm, p2, color, norm, p3, color, norm };
			addTuplesToVertices(&renderer.vertices, tuples);
		}
	}

	std::cout << renderer.vertices.size() << std::endl;

	renderer.runRenderer();

	return 0;
}