#pragma once
#include <string>

std::string GetResourceDir()
{
#ifdef NDEBUG // release build
	return "assets/";
#else
	return "U:/programming/VS projects/LightYears/LightYearsGame/assets/";
#endif
}
