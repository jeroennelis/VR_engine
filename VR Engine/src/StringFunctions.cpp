#include "StringFunctions.h"



StringFunctions::StringFunctions()
{
}


StringFunctions::~StringFunctions()
{
}

size_t StringFunctions::Split(const std::string & txt, std::vector<std::string>& strs, char ch)
{
	size_t pos = txt.find(ch);
	size_t initialPos = 0;
	strs.clear();

	// Decompose statement
	while (pos != std::string::npos) {
		strs.push_back(txt.substr(initialPos, pos - initialPos));
		initialPos = pos + 1;

		pos = txt.find(ch, initialPos);
	}

	// Add the last one
	std::string temp = txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1);
	if(temp != "")
		strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));
	return strs.size();
}