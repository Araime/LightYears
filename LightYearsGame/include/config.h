#pragma once
#include <string>

std::string GetResourceDir()
{
#ifdef NDEBUG // release build
	return "assets/";
#else
	return "D:/Programming/vs prj/LightYears/LightYearsGame/assets/";
#endif
}
