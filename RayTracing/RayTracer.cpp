#include "RayTracer.h"
#include <cmath>

RayTracer::RayTracer()
{
}
RayTracer::~RayTracer()
{
}

image* RayTracer::imageMaker(int hight, int width)
{
	image* resultImage = new image();
	resultImage->header.width = width;
	resultImage->header.depth = hight;

	int padding = 0;
	if ((width * sizeof(PIXELDATA)) % 4 != 0)
		padding = 4 - (width * 3) % 4;

	resultImage->header.filesize = sizeof(BMPHEAD) + hight * width * sizeof(PIXELDATA) + padding * hight;
	
	resultImage->pixelMatrix = new PIXELDATA*[hight];
	for (int i = 0; i < hight; i++)
		resultImage->pixelMatrix[i] = new PIXELDATA[width];

	return resultImage;
}

void RayTracer::renderMethod(vector3 cameraPos, vector3 cameraDir, int hight, int width, float fieldOfView)
{

	const double PI = 3.141592653589793238463;

	image* resultImage = imageMaker(hight, width);

	//camera is always directed on (x, 0, z) 
	vector3 cameraP = cameraPos;
	vector3 cameraD = cameraDir.norm();

	vector3 centerOfScreen = cameraP + cameraD;
	
	vector3 normXZ(0, 1, 0);
	vector3 normYZ(1, 0, 0);


	float fovInRad = fieldOfView / (float)180 * PI;

	for(int x = 0; x < width; x++)
	{
		for (int y = 0; y < hight; y++)
		{
			float yNorm = -(y - hight / 2) / (float)hight;
			float widthNorm = (x - width / 2) / (float)width;
			float realPlaneHeight = (float)(1 * tan(fovInRad));
			float realPlaneWidth = (float)width * realPlaneHeight / (float)hight;

			//angle between Ox and cameraD
			float angle = cameraD.acosV(normYZ);

			float normZ = widthNorm * cos(angle);
			float realPlaneZ = realPlaneWidth * cos(angle);

			float normX = widthNorm * sin(angle);
			float realPlaneX = realPlaneWidth * sin(angle);

			vector3 XYZVector(normX * realPlaneX / 2, yNorm * realPlaneHeight / 2, normZ * realPlaneZ / 2);

			vector3 positionOnPlane = centerOfScreen + XYZVector;

			vector3 rayDirection = positionOnPlane - cameraP;
		}
	}

}