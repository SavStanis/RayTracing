#pragma once
#include"vector3.h"
#include "image.h"

class RayTracer
{
public:
	RayTracer();
	~RayTracer();

	static image* imageMaker(int hight, int width);
	static void renderMethod(vector3 cameraPos, vector3 cameraDir, int hight, int width, float fieldOfView = 60);
};

