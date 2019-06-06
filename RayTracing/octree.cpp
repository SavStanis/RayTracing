#include "octree.h"



octree::octree(float max, std::vector<Triangle> allTriangles)
{
	minSize = max / 100;
	maxSize = max;
	head = new octNode(-max, max, -max, max, -max, max);
	head->triangles = allTriangles;
	head->rebuild(minSize);
}


octree::~octree()
{

}
