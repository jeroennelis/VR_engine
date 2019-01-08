#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

class StringFunctions
{
public:
	StringFunctions();
	~StringFunctions();

	static size_t Split(const std::string &txt, std::vector<std::string> &strs, char ch);
};

