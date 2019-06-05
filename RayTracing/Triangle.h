#pragma once
#include "vector3.h"

class Triangle
{
public:
	vector3 a;
	vector3 b;
	vector3 c;
	vector3 center;

	Triangle(vector3 a_, vector3 b_, vector3 c_);

	bool operator==(Triangle second);
	vector3 nVectorFinder();

};