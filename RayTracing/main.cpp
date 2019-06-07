#include <iostream>
#include "vector3.h"
#include "RayTracer.h"

int main()
{
	//for square
	//vector3 a(0, 0, -3);
	//a.showVector();
	//vector3 b(0, 0, 1);
	//vector3 light(-2, -1, -4);
	//b.showVector();

	//for gomer
	//vector3 a(-5, 2, -2);
	//a.showVector();
	//vector3 b(1, 0, 0);
	//vector3 light(-2, -1, -4);
	//b.showVector();

	//for plane
	vector3 a(-15, 6, -1);
	a.showVector();
	vector3 b(1, 0, 0);
	vector3 light(-2, -1, -4);
	b.showVector();

	RayTracer::renderMethod("plane.obj", a, b, light, 400, 400, 70);
	system("pause");
	return 0;
}