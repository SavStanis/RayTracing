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
	void findIntersections(vector3 rayOrigin, vector3 rayVector, std::vector<Triangle> &result);
	~octree();
};

