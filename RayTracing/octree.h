#pragma once
#include "Triangle.h"
#include <vector>
#include "octNode.h"
#include "cube.h"

class octree
{
	float maxSize;
	float minSize;
	octNode* head;
public:
	octree(float max, std::vector<Triangle> allTriangles);
	~octree();
};

