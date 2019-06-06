#include "cube.h"

cube::cube(vector3 x, vector3 y, vector3 z, vector3 k, vector3 x1, vector3 y1, vector3 z1, vector3 k1)
{
	this->x1 = x;
	this->x2 = y;
	this->x3 = z;
	this->x4 = k;

	this->x5 = x1;
	this->x6 = y1;
	this->x7 = z1;
	this->x8 = k1;
	sides.push_back(Triangle(x7, x6, x8));
	sides.push_back(Triangle(x5, x6, x8));

	sides.push_back(Triangle(x1, x5, x8));
	sides.push_back(Triangle(x1, x4, x8));

	sides.push_back(Triangle(x5, x2, x6));
	sides.push_back(Triangle(x5, x2, x1));

	sides.push_back(Triangle(x7, x2, x3));
	sides.push_back(Triangle(x7, x2, x6));

	sides.push_back(Triangle(x3, x7, x8));
	sides.push_back(Triangle(x3, x4, x8));

	sides.push_back(Triangle(x3, x2, x4));
	sides.push_back(Triangle(x1, x2, x4));
}