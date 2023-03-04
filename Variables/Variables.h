#pragma once
#include <string>
#include <vector>
#include <random>
#include <Windows.h>
#include "../imgui/imgui.h"

namespace RSG
{
	extern ImVec2 screenSize;
	extern int iScreenSizeX;
	extern int iScreenSizeY;
	extern int iWindowSizeX;
	extern int iWindowSizeY;
	extern int iStringLength;
	extern int iStringAmount;
	extern int iStringType;
	extern std::vector <std::string> sGeneratedStrArray;
	extern bool bGenerateStrings;
	extern bool bDisplayStrings;
	extern bool bCopyToClipboard;

	extern std::string RandStr(size_t length, int stringType);

	extern void CalcCenterScreen();

	extern void WinMinimize(LPCSTR handle);

	extern void WinClose();

	extern void Quit();
}