#pragma once
#include "vector3.h"
#include <vector>
#include "Triangle.h"

class cube
{
public:
	vector3 x1, x2, x3, x4, x5, x6, x7, x8;
	std::vector<Triangle> sides;
	cube() {}
	cube(vector3 x, vector3 y, vector3 z, vector3 k, vector3 x1, vector3 y1, vector3 z1, vector3 k1);
};