#include <iostream>
#include "vector3.h"
#include "RayTracer.h"

int main()
{
	vector3 a(0, 0, -2);
	a.showVector();
	vector3 b(0, 0, 1);
	vector3 light(-2, -1, -4);

	b.showVector();
	RayTracer::renderMethod(a, b, light, 1000, 1000);
	system("pause");
	return 0;
}