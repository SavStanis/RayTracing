#pragma once
#include "Triangle.h"
#include <vector>
#include "cube.h"

class octNode
{
	cube spaceCube;
public:
	bool list = true;
	std::vector<Triangle> triangles;
	octNode** doughterNodes = new octNode*[8];

	octNode(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
	void rebuild(float min);
};

