#include "objReader.h"



objReader::objReader()
{
}


objReader::~objReader()
{
}

std::vector<Triangle> objReader::reader(const char* pathToFile, float &max)
{
	std::fstream input(pathToFile);
	std::vector<vector3> vertex;
	vertex.push_back(vector3(0, 0, 0));
		
	float x, y, z;  //tmp vars for vertexes
	std::string is, js, ks;
	int i, j, k;	//tmp vars for polygons
	std::vector<Triangle> Triangles;

	std::string tmp;
	while (!input.eof())
	{
		input >> tmp;
		if (tmp == "v")
		{
			input >> x;
			if (abs(x) > max)	max = abs(x);
			input >> y;
			if (abs(y) > max)	max = abs(y);
			input >> z;
			if (abs(z) > max)	max = abs(z);
			vertex.push_back(vector3(x, y, z));
		}
		if (tmp == "f")
		{
			input >> is;
			input >> js;
			input >> ks;
			i = findFirstField(is);
			j = findFirstField(js);
			k = findFirstField(ks);
			Triangles.push_back(Triangle(vertex[i], vertex[j], vertex[k]));
		}
	}
	return Triangles;
}

int objReader::findFirstField(std::string s)
{
	std::string tmp = s;
	int counter = 0;
	for (char i : s)
	{
		if (i == '/')
		{
			tmp = tmp.substr(0, counter);
			break;
		}
		counter++;
	}
	return std::stoi(tmp);
}