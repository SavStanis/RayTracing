#include "RayTracer.h"

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

void RayTracer::renderMethod(const char* pathToFile, vector3 cameraPos, vector3 cameraDir, vector3 lightPos, int hight, int width, float fieldOfView)
{

	const double PI = 3.141592653589793238463;

	image* resultImage = imageMaker(hight, width);

	//camera is always directed on (x, 0, z) from (-x, 0, -z) 
	vector3 cameraP = cameraPos;
	vector3 cameraD = cameraDir.norm();

	vector3 centerOfScreen = cameraP + cameraD;
	
	//max value of x or y or z 
	float max = 0;

	std::vector<Triangle> Triangles = objReader::reader(pathToFile, max);

	octree tmpTree(max, Triangles);

	float fovInRad = fieldOfView / (float)180 * PI;

	for(int x = 0; x < width; x++)
	{
		for (int y = 0; y < hight; y++)
		{
			vector3 rayDirection = rayDirectionFinder(hight, width, cameraD, cameraP, centerOfScreen, x, y, fovInRad);
			float minDist = INFINITY;
			bool isTrigReal = false;
			Triangle minTrig = Triangles[0];

			for (Triangle i : Triangles)
			{
				if (ThereIsIntersectionBetweenRayAndTriangle(cameraP, rayDirection, i))
				{
					isTrigReal = true;
					float distance = vector3::distance(cameraP, i.center);
					if (distance < minDist)
					{
						minTrig = i;
						minDist = distance;
					}
				}
			}

			if (isTrigReal)
			{
				vector3 shadowRay = lightPos - minTrig.center;
				bool isShadow = false;
				for (Triangle i : Triangles)
				{
					if (ThereIsIntersectionBetweenRayAndTriangle(lightPos, shadowRay, i))
					{
						float distance = vector3::distance(lightPos, i.center);
						if (distance < minDist && !(i == minTrig))
						{
							isShadow = true;
							break;
						}
					}
				}
				vector3 normTriangle = minTrig.nVectorFinder();
				float angle = normTriangle.acosV(shadowRay);

				if (angle > PI / 2)
					angle = PI - angle;
				if (isShadow)
				{
					resultImage->pixelMatrix[y][x].redComponent = 125 - 100 * cos(angle);
					resultImage->pixelMatrix[y][x].greenComponent = 125 - 100 * cos(angle);
					resultImage->pixelMatrix[y][x].blueComponent = 125 - 100 * cos(angle);
				}
				else
				{
					resultImage->pixelMatrix[y][x].redComponent = 125 + 100 * cos(angle);
					resultImage->pixelMatrix[y][x].greenComponent = 125 + 100 * cos(angle);
					resultImage->pixelMatrix[y][x].blueComponent = 125 + 100 * cos(angle);
				}
			}
		}
	}

	BMPWriter::writeBMPFile("Output.bmp", resultImage);
}


bool RayTracer::ThereIsIntersectionBetweenRayAndTriangle(vector3 rayOrigin, vector3 rayVector, Triangle inTriangle)
{
	vector3 vertex0 = inTriangle.a;
	vector3 vertex1 = inTriangle.b;
	vector3 vertex2 = inTriangle.c;
	vector3 edge1 = vertex1 - vertex0;
	vector3 edge2 = vertex2 - vertex0;
	vector3 h = rayVector.crossProduct(edge2);

	float a = edge1.dotProduct(h);
	float EPSILON = 1e-5f;
	
	if (a > -EPSILON && a < EPSILON)
	{
		return false;
	}
	float f = 1 / a;
	vector3 s = rayOrigin - vertex0;
	float u = f * s.dotProduct(h);
	if (u < 0.0 || u > 1.0)
	{
		return false;
	}
	vector3 q = s.crossProduct(edge1);
	float v = f * rayVector.dotProduct(q);
	if (v < 0.0 || u + v > 1.0)
	{
		return false;
	}

	// At this stage we can compute t to find out where the intersection point is on the line.
	float t = f * edge2.dotProduct(q);
	return t > EPSILON;
}

vector3 RayTracer::rayDirectionFinder(int hight, int width, vector3 cameraD, vector3 cameraP, vector3 centerOfScreen, int x, int y, float fovInRad)
{
	const double PI = 3.141592653589793238463;

	float yNorm = - (y - hight / 2) / (float)hight;
	float widthNorm = (x - width / 2) / (float)width;
	float realPlaneHeight = (float)(1 * tan(fovInRad));
	float realPlaneWidth = (float)width * realPlaneHeight / (float)hight;

	vector3 normYZ(1, 0, 0);

	//angle between Ox and cameraD
	float angle = cameraD.acosV(normYZ);
	if (angle > PI / 2)
		angle = PI - angle;

	float normZ = widthNorm * cos(angle);
	float realPlaneZ = realPlaneWidth * cos(angle);

	float normX = widthNorm * sin(angle);
	float realPlaneX = realPlaneWidth * sin(angle);

	vector3 XYZVector(normX * realPlaneX / 2, yNorm * realPlaneHeight / 2, normZ * realPlaneZ / 2);

	vector3 positionOnPlane = centerOfScreen + XYZVector;
	return positionOnPlane - cameraP;
}