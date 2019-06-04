#pragma once
class vector3
{
public:
	float X;
	float Y;
	float Z;
	
	vector3(float x, float y, float z);
	float length();
	void showVector();

	vector3 norm();
	vector3 operator +(vector3 right);
	vector3 operator -(vector3 right);
	
	vector3 crossProduct(vector3 right);
	float dotProduct(vector3 right);
};

