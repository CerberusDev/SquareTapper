// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "SquareTapper.h"

std::string GetLevelKey(const int LevelDisplayName)
{
	std::stringstream StringStreamLevelKey;
	StringStreamLevelKey << "Level" << LevelDisplayName;
	return StringStreamLevelKey.str();
}