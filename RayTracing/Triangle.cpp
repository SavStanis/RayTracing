#include "Triangle.h"

Triangle::Triangle(vector3 a_, vector3 b_, vector3 c_)
{
	a = a_;
	b = b_;
	c = c_;
	center = vector3((a_.X + b_.X + c_.X) / 3, (a_.Y + b_.Y + c_.Y) / 3, (a_.Z + b_.Z + c_.Z) / 3);
}

bool Triangle::operator==(Triangle second)
{
	if (this->a == second.a && this->b == second.b && this->c == second.c)
		return true;
	else
		return false;
}

vector3 Triangle::nVectorFinder()
{
	vector3 first = b - a;
	vector3 second = c - a;
	return first.crossProduct(second).norm();
}