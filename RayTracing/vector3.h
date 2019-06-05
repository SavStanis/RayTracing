#pragma once
class vector3
{
public:
	float X;
	float Y;
	float Z;
	
	vector3(float x = 0, float y = 0, float z = 0);
	float length();
	void showVector();

	vector3 norm();
	vector3 operator +(vector3 right);
	vector3 operator *(float l);
	vector3 operator -(vector3 right);
	bool operator==(vector3 right);
	
	vector3 crossProduct(vector3 right);
	float dotProduct(vector3 right);

	//acos betweet vectors
	float acosV(vector3 second);

	static float distance(vector3 right, vector3 left);
};

