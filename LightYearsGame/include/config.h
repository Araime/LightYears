#pragma once
#include <string>

std::string GetResourceDir()
{
#ifdef NDEBUG // release build
	return "assets/";
#else
	return "D:/Programming/VS prj/LightYears/LightYearsGame/assets/";
#endif
}
