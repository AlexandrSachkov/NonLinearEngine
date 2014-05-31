#ifndef NLRE_STATIC_
#define NLRE_STATIC_

#include "stdafx.h"

class NLREStatic
{
public:
	static std::wstring getDirectoryFromPath(std::wstring path);
	static std::string getDirectoryFromPath(std::string path);
};

#endif