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
	std::string is, js, ks, gs;
	std::string i, j, k, g;	//tmp vars for polygons
	std::vector<Triangle> Triangles;

	std::string tmp;
	input >> tmp;
	while (!input.eof())
	{
		gs = "null";
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
			if (!input.eof())
			{
				input >> gs;
				g = findFirstField(gs);
			}
			i = findFirstField(is);
			j = findFirstField(js);
			k = findFirstField(ks);


			if (!isNumber(g) && gs != "null")
			{
				Triangles.push_back(Triangle(vertex[std::stoi(i)], vertex[std::stoi(j)], vertex[std::stoi(k)]));
				tmp = gs;
			}
			else
			{
				Triangles.push_back(Triangle(vertex[std::stoi(i)], vertex[std::stoi(j)], vertex[std::stoi(k)]));
				Triangles.push_back(Triangle(vertex[std::stoi(i)], vertex[std::stoi(g)], vertex[std::stoi(k)]));
				if (!input.eof())
					input >> tmp;
			}
		}
		else
		{
			input >> tmp;
		}
	}
	return Triangles;
}

std::string objReader::findFirstField(std::string s)
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
	return tmp;
}

bool objReader::isNumber(std::string s)
{
	for (char i : s)
	{
		if (!isdigit(i))
			return false;
	}
	return true;
}