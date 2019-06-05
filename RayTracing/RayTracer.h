#pragma once
#include"vector3.h"
#include "image.h"
#include "Triangle.h"
#include "BMPWriter.h"

class RayTracer
{
	static image* imageMaker(int hight, int width);
	static bool ThereIsIntersectionBetweenRayAndTriangle(vector3 rayOrigin, vector3 rayVector, Triangle inTriangle);

public:
	RayTracer();
	~RayTracer();

	static void renderMethod(vector3 cameraPos, vector3 cameraDir, int hight, int width, float fieldOfView = 60);
};

