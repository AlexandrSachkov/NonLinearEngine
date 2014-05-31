#include "stdafx.h"
#include "RenderingEngine\NLREMain\NLREStatic.h"

std::wstring NLREStatic::getDirectoryFromPath(std::wstring path)
{
	std::wstring directory;
	const size_t last_slash_idx = path.rfind(L'\\');
	if (std::string::npos != last_slash_idx)
	{
		directory = path.substr(0, last_slash_idx);
	}
	return directory;
}

std::string NLREStatic::getDirectoryFromPath(std::string path)
{
	std::string directory;
	const size_t last_slash_idx = path.rfind('\\');
	if (std::string::npos != last_slash_idx)
	{
		directory = path.substr(0, last_slash_idx);
	}
	return directory;
}