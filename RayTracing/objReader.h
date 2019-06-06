#pragma once
#include "Triangle.h"
#include <vector>
#include <fstream>
#include "vector3.h"
#include <string>

class objReader
{
	static int findFirstField(std::string s);
public:
	objReader();
	~objReader();
	static std::vector<Triangle> reader(const char* pathToFile);
};

