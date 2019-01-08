#include "XYZLoader.h"
#define _CRT_SECURE_NO_WARNINGS



XYZLoader::XYZLoader()
{
}


XYZLoader::~XYZLoader()
{
}

std::vector<RawModel> XYZLoader::LoadXYZModel(const std::string & filePath, Loader & loader)
{
	std::vector<RawModel> models;
	std::vector<float> vertices(10000000);
	std::vector<float> colours(10000000);

	FILE* file;
	fopen_s(&file, filePath.c_str(), "r");
	if (file ==  NULL) {
		std::cout << "file: " << filePath << "could not be opened!" << std::endl;
		return models;
	}
	
	float x, y, z;
	int r, g, b;
	int segment = 0;
	int i = 0;
	do {
		int nItemsRead = fscanf_s(file, "%f %f %f %d %d %d\n", &x, &y, &z, &r, &g, &b);
		
		if (6 != nItemsRead)
			break;

		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(z);

		colours.push_back((float)r/255);
		colours.push_back((float)g/255);
		colours.push_back((float)b/255);
		//std::cout << x << "\t" << y << "\t" << z << "\t" << r << "\t" << g << "\t" << b << "\t" << std::endl;
		
		i++;
		if ((i % 1048576 == 0) || (segment == 0))
		{
			segment++;
			std::cout << "new segment" << std::endl;
			i = 0;
			models.push_back(loader.LoadPointCloudToVAO(vertices, colours));
			vertices.clear();
			colours.clear();
		}

		/*if (segment == 5)
			break;*/
	
	} while (1);

	
	

	return models;
}

std::vector<std::string> XYZLoader::SplitString(const std::string & s, char delim)
{
	std::vector<std::string> elems;

	const char* cstr = s.c_str();
	unsigned int strLength = (unsigned int)s.length();
	unsigned int start = 0;
	unsigned int end = 0;

	while (end <= strLength)
	{
		while (end <= strLength)
		{
			if (cstr[end] == delim)
				break;
			end++;
		}

		elems.push_back(s.substr(start, end - start));
		start = end + 1;
		end = start;
	}

	return elems;
}

