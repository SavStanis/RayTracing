#pragma once
#include "vector3.h"

struct Triangle
{
	vector3 a;
	vector3 b;
	vector3 c;

	Triangle(vector3 a_, vector3 b_, vector3 c_) : a(a_), b(b_), c(c_)	{}
};