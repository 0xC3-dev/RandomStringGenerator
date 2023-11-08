#pragma once
#include "../Includes/Includes.hpp"

namespace RSG
{
	extern int iScreenSizeX;
	extern int iScreenSizeY;
	extern int iWindowSizeX;
	extern int iWindowSizeY;
	extern int iNotifyPosX;
	extern int iNotifyPosY;
	extern int iStringLength;
	extern int iStringAmount;
	extern int iStringType;
	extern std::vector <std::string> sGeneratedStrArray;
	extern bool bGenerateStrings;
	extern bool bDisplayStrings;
	extern bool bCopyToClipboard;
	extern bool bCopyToClipboardNotify;
	extern bool bOldSliderDesign;

	extern std::string RandStr(DWORD length, int stringType);

	extern void CalcCenterScreen();

	extern void WinMinimize(LPCSTR handle);

	extern void WinClose();

	extern void Quit();
}