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

bool cube::ThereIsIntersectionBetweenRayAndTriangle(vector3 rayOrigin, vector3 rayVector, Triangle inTriangle)
{

	vector3 vertex0 = inTriangle.a;
	vector3 vertex1 = inTriangle.b;
	vector3 vertex2 = inTriangle.c;
	vector3 edge1 = vertex1 - vertex0;
	vector3 edge2 = vertex2 - vertex0;
	vector3 h = rayVector.crossProduct(edge2);

	float a = edge1.dotProduct(h);
	float EPSILON = 1e-5f;

	if (a > -EPSILON && a < EPSILON)
	{
		return false;
	}
	float f = 1 / a;
	vector3 s = rayOrigin - vertex0;
	float u = f * s.dotProduct(h);
	if (u < 0.0 || u > 1.0)
	{
		return false;
	}
	vector3 q = s.crossProduct(edge1);
	float v = f * rayVector.dotProduct(q);
	if (v < 0.0 || u + v > 1.0)
	{
		return false;
	}

	// At this stage we can compute t to find out where the intersection point is on the line.
	float t = f * edge2.dotProduct(q);
	return t > EPSILON;
}

bool cube::IntersectionBetweetRayAndCube(vector3 rayOrigin, vector3 rayVector)
{
	bool isIntersection = false;
	for (Triangle i : sides)
	{
		isIntersection = ThereIsIntersectionBetweenRayAndTriangle(rayOrigin, rayVector, i);
	}
	return isIntersection;
}