#include "OpenGLEngine.h"
#include <vector>
#include <tuple>
#include <stdlib.h>
#include "SimplexNoise.h"
#include "MarchingCubesTable.hpp""
#include <thread>

const int mapWidth = 200;
const int mapHeight = 22;
const int mapDepth = 200;

std::vector<std::vector<std::vector<float>>> generateSurface() {
	SimplexNoise noise;

	std::vector<std::vector<float>> heightMap;

	for (float x = 0; x < mapWidth; x++) {
		heightMap.push_back(std::vector<float>());
		for (float z = 0; z < mapWidth; z++) {
			heightMap.at(x).push_back(noise.noise(x / 100.0f, z / 100.0f) * 10 + 10);
		}
	}

	std::vector<std::vector<std::vector<float>>> ret;

	for (float x = 0; x < mapWidth; x++) {
		ret.push_back(std::vector<std::vector<float>>());
		for (float y = 0; y < mapHeight; y++) {
			ret.at(x).push_back(std::vector<float>());
			for (float z = 0; z < mapDepth; z++) {
				if (y < heightMap.at(x).at(z)) ret.at(x).at(y).push_back(1);
				else ret.at(x).at(y).push_back(0);
			}
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

void cubeMarch(float cutoff, int x, int y, int z, std::vector<std::vector<std::vector<float>>> *surface, std::vector<std::vector<std::tuple<float, float, float>>> *cubeTuples) {
	std::tuple<float, float, float, float> cubeVertices[8];
	int offsets[] = {0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0};
	int numAbove = 0;
	for (int p = 0; p < 8; p++) {
		float value = surface->at(x + offsets[p * 3]).at(y + offsets[p * 3 + 1]).at(z + offsets[p * 3 + 2]);
		std::tuple<float, float, float, float> point = { 
			x + offsets[p * 3], 
			y + offsets[p * 3 + 1], 
			z + offsets[p * 3 + 2], 
			value
		};
		cubeVertices[p] = point;
		if (value >= cutoff) numAbove++;
	}
	if (numAbove == 0 || numAbove == 8) {
		return;
	}
	std::tuple<float, float, float> edgeVertices[12];
	int edgePoints[] = {0, 1, 1, 2, 2, 3, 3, 0, 4, 5, 5, 6, 6, 7, 7, 4, 0, 4, 1, 5, 2, 6, 3, 7};
	for (int e = 0; e < 12; e++) {
		int p1 = edgePoints[e * 2];
		int p2 = edgePoints[e * 2 + 1];
		float value1 = std::get<3>(cubeVertices[p1]);
		float value2 = std::get<3>(cubeVertices[p2]);
		float p2amp = 1 - (cutoff - value1) / (value2 - value1);
		float p1amp = 1 - p2amp;
		std::tuple<float, float, float> edge = {
			(std::get<0>(cubeVertices[p2]) * p2amp + std::get<0>(cubeVertices[p1]) * p1amp),
			(std::get<1>(cubeVertices[p2]) * p2amp + std::get<1>(cubeVertices[p1]) * p1amp),
			(std::get<2>(cubeVertices[p2]) * p2amp + std::get<2>(cubeVertices[p1]) * p1amp)
		};
		edgeVertices[e] = edge;
	}
	int code = 0;
	for (int i = 0; i < 8; i++) {
		if (std::get<3>(cubeVertices[i]) >= cutoff) code += pow(2, i);
	}
	std::vector<int> triTableRead;
	for (int i = 0; i < 16; i++) {
		int read = MarchingCubesTable::triTable[code][i];
		if (read == -1) break;
		triTableRead.push_back(read);
	}
	std::vector<std::tuple<float, float, float>> tuples;
	for (int v = 0; v < triTableRead.size() / 3; v++) {
		std::tuple<float, float, float> p1 = edgeVertices[triTableRead.at(v * 3)];
		std::tuple<float, float, float> p2 = edgeVertices[triTableRead.at(v * 3 + 1)];
		std::tuple<float, float, float> p3 = edgeVertices[triTableRead.at(v * 3 + 2)];
		std::tuple<float, float, float> color = { 1.0f, 1.0f, 1.0f };
		std::tuple<float, float, float> norm = getNorm(p1, p2, p3);
		std::tuple<float, float, float> to_push[] = { p1, color, norm, p2, color, norm, p3, color, norm };
		tuples.insert(tuples.end(), std::begin(to_push), std::end(to_push));
	}
	cubeTuples->push_back(tuples);
}

int main() {

	OpenGLEngine renderer;

	renderer.lightPos.x = -1.0f;
	renderer.lightPos.y = 4.0f;
	renderer.lightPos.z = -1.0f;

	std::vector<std::vector<std::vector<float>>> surface = generateSurface();

	std::vector<std::vector<std::tuple<float, float, float>>> cubeTuples;

	std::vector<std::thread> threads;
	
	for (int x = 0; x < mapWidth - 1; x++) {
		for (int y = 0; y < mapHeight - 1; y++) {
			for (int z = 0; z < mapDepth - 1; z++) {

				cubeMarch(0.4, x, y, z, &surface, &cubeTuples);

			}
		}
	}

	for (auto tuples : cubeTuples) {
		addTuplesToVertices(&renderer.vertices, tuples);
	}

	std::cout << renderer.vertices.size() << std::endl;

	renderer.runRenderer();
	

	return 0;
}