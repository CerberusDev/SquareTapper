// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "SquareTapper.h"

std::string GetLevelRecordKey(const int LevelDisplayName)
{
	std::stringstream StringStreamLevelKey;
	StringStreamLevelKey << "LevelRecord" << LevelDisplayName;
	return StringStreamLevelKey.str();
}

