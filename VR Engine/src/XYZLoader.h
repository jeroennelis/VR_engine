#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include "Loader.h"

#define _CRT_SECURE_NO_DEPRECATE


class XYZLoader
{
public:
	XYZLoader();
	~XYZLoader();

	static std::vector<RawModel> LoadXYZModel(const std::string & filePath, Loader &loader);

private:
	static std::vector<std::string> SplitString(const std::string & s, char delim);
};

