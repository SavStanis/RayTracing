#include "vector3.h"
#include <iostream>
#include <math.h>


vector3::vector3(float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
}
float vector3::length()
{
	return (float)sqrt(X*X + Y * Y + Z * Z);
}

vector3 vector3::norm()
{
	float l = length();
	return vector3(X / l, Y / l, Z / l);
}
vector3 vector3::operator +(vector3 right)
{
	return vector3(this->X + right.X, this->Y + right.Y, this->Z + right.Z);
}
vector3 vector3::operator -(vector3 right)
{
	return vector3(this->X - right.X, this->Y - right.Y, this->Z - right.Z);
}

vector3 vector3::crossProduct(vector3 right)
{
	return vector3(
		this->Y * right.Z - this->Z * right.Y,
		this->Z * right.X - this->X * right.Z,
		this->X * right.Y - this->Y * right.X);
}
float vector3::dotProduct(vector3 right)
{
	return this->X * right.X + this->Y * right.Y + this->Z * right.Z;
}

void vector3::showVector()
{
	std::cout << "\n( " << X << " , " << Y << " , " << Z << " )\n";
}

vector3 vector3::operator *(float l)
{
	return vector3(this->X * l, this->Y * l, this->Z * l);
}