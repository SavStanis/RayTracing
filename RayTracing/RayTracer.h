#pragma once
#include"vector3.h"
#include "image.h"
#include "Triangle.h"
#include "BMPWriter.h"
#include <vector>
#include <cmath>

class RayTracer
{
	static image* imageMaker(int hight, int width);
	static bool ThereIsIntersectionBetweenRayAndTriangle(vector3 rayOrigin, vector3 rayVector, Triangle inTriangle);
	static vector3 rayDirectionFinder(int hight, int width, vector3 cameraD, vector3 cameraP, vector3 centerOfScreen, int x, int y, float fovInRad);

public:
	RayTracer();
	~RayTracer();

	static void renderMethod(vector3 cameraPos, vector3 cameraDir, vector3 lightPos, int hight, int width, float fieldOfView = 80);
};

