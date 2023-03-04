#pragma once
#include "../App_UI/UI.h"

namespace Console
{
	void SetConsoleInfo()
	{
		ShowWindow(GetConsoleWindow(), FALSE);
	}
}

namespace Utils
{
	void GenerateStrings()
	{
		if (RSG::bGenerateStrings)
		{
			if (RSG::iStringType != 1337)
			{
				if (RSG::iStringAmount == 0 || RSG::iStringLength == 0)
				{
					Notify::Message("  - Please enter a string amount and length  -  ");
				}
				else if (RSG::iStringAmount > 0 && RSG::iStringLength > 0)
				{
					if (RSG::sGeneratedStrArray.size() > 0)
					{
						RSG::sGeneratedStrArray.clear();
					}
					for (int i = 0; i < RSG::iStringAmount; i++)
					{
						RSG::sGeneratedStrArray.push_back(RSG::RandStr(RSG::iStringLength, RSG::iStringType));
					}
				}
				RSG::bDisplayStrings = true;
			}
			else
			{
				Notify::Message("  -  Please select a string type from the drop down  -  ");
			}
			RSG::bGenerateStrings = false;
		}
	}
}