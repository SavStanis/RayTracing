#include "octNode.h"

octNode::octNode(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
{
	vector3 x1(maxX, maxY, maxZ);
	vector3 x2(minX, maxY, maxZ);
	vector3 x3(minX, minY, maxZ);
	vector3 x4(maxX, minY, maxZ);

	vector3 x5(maxX, maxY, minZ);
	vector3 x6(minX, maxY, minZ);
	vector3 x7(minX, minY, minZ);
	vector3 x8(maxX, minY, minZ);

	spaceCube = cube(x1, x2, x3, x4, x5, x6, x7, x8);
}

void octNode::rebuild(float min)
{
	float minXnew, maxXnew, minYnew, maxYnew, minZnew, maxZnew;


	// 1, 2, 3, 4 oct
	vector3 center = vector3((spaceCube.x1.X + spaceCube.x2.X)*0.5, (spaceCube.x1.Y + spaceCube.x4.Y)*0.5, (spaceCube.x1.Z + spaceCube.x5.Z)*0.5);

	minXnew = (spaceCube.x1.X + spaceCube.x2.X)*0.5;
	maxXnew = spaceCube.x1.X;
	minYnew = (spaceCube.x1.Y + spaceCube.x4.Y)*0.5;
	maxYnew = spaceCube.x1.Y;
	minZnew = (spaceCube.x1.Z + spaceCube.x5.Z)*0.5;
	maxZnew = spaceCube.x1.Z;

	if (triangles.size() < 100 || (maxXnew - minXnew) < min)
		return;

	doughterNodes[0] = new octNode(minXnew, maxXnew, minYnew, maxYnew, minZnew, maxZnew);

	maxXnew = (spaceCube.x1.X + spaceCube.x2.X)*0.5;
	minXnew = spaceCube.x2.X;
	minYnew = (spaceCube.x1.Y + spaceCube.x4.Y)*0.5;
	maxYnew = spaceCube.x1.Y;
	minZnew = (spaceCube.x1.Z + spaceCube.x5.Z)*0.5;
	maxZnew = spaceCube.x1.Z;

	doughterNodes[1] = new octNode(minXnew, maxXnew, minYnew, maxYnew, minZnew, maxZnew);

	maxXnew = (spaceCube.x1.X + spaceCube.x2.X)*0.5;
	minXnew = spaceCube.x2.X;
	maxYnew = (spaceCube.x2.Y + spaceCube.x3.Y)*0.5;
	minYnew = spaceCube.x3.Y;
	minZnew = (spaceCube.x1.Z + spaceCube.x5.Z)*0.5;
	maxZnew = spaceCube.x1.Z;

	doughterNodes[2] = new octNode(minXnew, maxXnew, minYnew, maxYnew, minZnew, maxZnew);

	minXnew = (spaceCube.x3.X + spaceCube.x4.X)*0.5;
	maxXnew = spaceCube.x4.X;
	maxYnew = (spaceCube.x1.Y + spaceCube.x4.Y)*0.5;
	minYnew = spaceCube.x4.Y;
	minZnew = (spaceCube.x1.Z + spaceCube.x5.Z)*0.5;
	maxZnew = spaceCube.x1.Z;

	doughterNodes[3] = new octNode(minXnew, maxXnew, minYnew, maxYnew, minZnew, maxZnew);

	// 5, 6, 7, 8 oct

	minXnew = (spaceCube.x1.X + spaceCube.x2.X)*0.5;
	maxXnew = spaceCube.x1.X;
	minYnew = (spaceCube.x1.Y + spaceCube.x4.Y)*0.5;
	maxYnew = spaceCube.x1.Y;
	maxZnew = (spaceCube.x1.Z + spaceCube.x5.Z)*0.5;
	minZnew = spaceCube.x5.Z;

	doughterNodes[4] = new octNode(minXnew, maxXnew, minYnew, maxYnew, minZnew, maxZnew);

	maxXnew = (spaceCube.x1.X + spaceCube.x2.X)*0.5;
	minXnew = spaceCube.x2.X;
	minYnew = (spaceCube.x1.Y + spaceCube.x4.Y)*0.5;
	maxYnew = spaceCube.x1.Y;
	maxZnew = (spaceCube.x1.Z + spaceCube.x5.Z)*0.5;
	minZnew = spaceCube.x5.Z;

	doughterNodes[5] = new octNode(minXnew, maxXnew, minYnew, maxYnew, minZnew, maxZnew);

	maxXnew = (spaceCube.x1.X + spaceCube.x2.X)*0.5;
	minXnew = spaceCube.x2.X;
	maxYnew = (spaceCube.x2.Y + spaceCube.x3.Y)*0.5;
	minYnew = spaceCube.x3.Y;
	maxZnew = (spaceCube.x1.Z + spaceCube.x5.Z)*0.5;
	minZnew = spaceCube.x5.Z;

	doughterNodes[6] = new octNode(minXnew, maxXnew, minYnew, maxYnew, minZnew, maxZnew);

	minXnew = (spaceCube.x3.X + spaceCube.x4.X)*0.5;
	maxXnew = spaceCube.x4.X;
	maxYnew = (spaceCube.x1.Y + spaceCube.x4.Y)*0.5;
	minYnew = spaceCube.x4.Y;
	maxZnew = (spaceCube.x1.Z + spaceCube.x5.Z)*0.5;
	minZnew = spaceCube.x5.Z;

	doughterNodes[7] = new octNode(minXnew, maxXnew, minYnew, maxYnew, minZnew, maxZnew);

	std::vector<Triangle> newVectors;

	while(!triangles.empty())
	{
		int counter1 = -1;
		int counter2 = -1;
		int counter3 = -1;

		Triangle i = triangles.back();
		triangles.pop_back();
		
		counter1 = positionFinder(i.a, center);
		counter2 = positionFinder(i.b, center);
		counter3 = positionFinder(i.c, center);

		if (counter1 == counter2 && counter2 == counter3)
			doughterNodes[counter1]->triangles.push_back(i);
		else
			newVectors.push_back(i);
	}

	triangles = newVectors;

	list = false;

	doughterNodes[0]->list = true;
	doughterNodes[0]->rebuild(min);
	doughterNodes[1]->list = true;
	doughterNodes[1]->rebuild(min);
	doughterNodes[2]->list = true;
	doughterNodes[2]->rebuild(min);
	doughterNodes[3]->list = true;
	doughterNodes[3]->rebuild(min);
	doughterNodes[4]->list = true;
	doughterNodes[4]->rebuild(min);
	doughterNodes[5]->list = true;
	doughterNodes[5]->rebuild(min);
	doughterNodes[6]->list = true;
	doughterNodes[6]->rebuild(min);
	doughterNodes[7]->list = true;
	doughterNodes[7]->rebuild(min);
}

void octNode::findIntesections(vector3 rayOrigin, vector3 rayVector, std::vector<Triangle> &result)
{

	for (Triangle i : triangles)
		result.push_back(i);
	if (list)
		return;

	for (int i = 0; i < 8; i++)
	{
		if (doughterNodes[i] && doughterNodes[i]->spaceCube.IntersectionBetweetRayAndCube(rayOrigin, rayVector))
		{
			doughterNodes[i]->findIntesections(rayOrigin, rayVector, result);
		}
	}

}

int octNode::positionFinder(vector3 x, vector3 center)
{
	if (x.Z > center.Z)
	{
		if (x.Y > center.Y)
		{
			if (x.X > center.X)
				return 0;
			else
				return 1;
		}
		else
		{
			if (x.X > center.X)
				return 3;
			else
				return 2;
		}
	}
	else
	{
		if (x.Y > center.Y)
		{
			if (x.X > center.X)
				return 4;
			else
				return 5;
		}
		else
		{
			if (x.X > center.X)
				return 7;
			else
				return 6;
		}
	}
}