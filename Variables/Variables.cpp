#include "Variables.h"

namespace RSG
{
	ImVec2 screenSize = { 0, 0 };
	int iScreenSizeX = NULL;
	int iScreenSizeY = NULL;
	int iWindowSizeX = 400;
	int iWindowSizeY = 600;
	int iStringLength = NULL;
	int iStringAmount = NULL;
	int iStringType = 1337;
	std::vector <std::string> sGeneratedStrArray{};
	bool bGenerateStrings = false;
	bool bDisplayStrings = false;
	bool bCopyToClipboard = false;

	std::string sAllChars{ "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$&-_=+;:.?" };
	std::string sAllNormalChars{ "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890" };
	std::string sLowercaseNumbersChars{ "abcdefghijklmnopqrstuvwxyz1234567890" };
	std::string sLowercaseChars{ "abcdefghijklmnopqrstuvwxyz" };
	std::string sUppercaseNumbersChars{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890" };
	std::string sUppercaseChars{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
	std::string sNumbersChars{ "1234567890" };
	std::random_device rd;
	std::mt19937 generator(rd());
	std::string RandStr(size_t length, int stringType)
	{
		if (stringType == 0)
		{
			const size_t char_size = sAllChars.size();
			std::uniform_int_distribution<> random_int(0, char_size - 1);
			std::string output;
			for (size_t i = 0; i < length; ++i)
				output.push_back(sAllChars[random_int(generator)]);
			return output;
		}
		else if (stringType == 1)
		{
			const size_t char_size = sAllNormalChars.size();
			std::uniform_int_distribution<> random_int(0, char_size - 1);
			std::string output;
			for (size_t i = 0; i < length; ++i)
				output.push_back(sAllNormalChars[random_int(generator)]);
			return output;
		}
		else if (stringType == 2)
		{
			const size_t char_size = sLowercaseNumbersChars.size();
			std::uniform_int_distribution<> random_int(0, char_size - 1);
			std::string output;
			for (size_t i = 0; i < length; ++i)
				output.push_back(sLowercaseNumbersChars[random_int(generator)]);
			return output;
		}
		else if (stringType == 3)
		{
			const size_t char_size = sLowercaseChars.size();
			std::uniform_int_distribution<> random_int(0, char_size - 1);
			std::string output;
			for (size_t i = 0; i < length; ++i)
				output.push_back(sLowercaseChars[random_int(generator)]);
			return output;
		}
		else if (stringType == 4)
		{
			const size_t char_size = sUppercaseNumbersChars.size();
			std::uniform_int_distribution<> random_int(0, char_size - 1);
			std::string output;
			for (size_t i = 0; i < length; ++i)
				output.push_back(sUppercaseNumbersChars[random_int(generator)]);
			return output;
		}
		else if (stringType == 5)
		{
			const size_t char_size = sUppercaseChars.size();
			std::uniform_int_distribution<> random_int(0, char_size - 1);
			std::string output;
			for (size_t i = 0; i < length; ++i)
				output.push_back(sUppercaseChars[random_int(generator)]);
			return output;
		}
		else if (stringType == 6)
		{
			const size_t char_size = sNumbersChars.size();
			std::uniform_int_distribution<> random_int(0, char_size - 1);
			std::string output;
			for (size_t i = 0; i < length; ++i)
				output.push_back(sNumbersChars[random_int(generator)]);
			return output;
		}
	}

	void CalcCenterScreen()
	{
		float iScreenDiffX = screenSize.x - iWindowSizeX;
		float iScreenDiffY = screenSize.y - iWindowSizeY;
		screenSize.x = iScreenDiffX / 2;
		screenSize.y = iScreenDiffY / 2;
	}

	void WinMinimize(LPCSTR handle)
	{
		LPCSTR window = handle;
		HWND hWnd = FindWindow(NULL, window);
		ShowWindow(hWnd, SW_MINIMIZE);
	}

	void WinClose()
	{
		exit(0);
	}

	void Quit()
	{
		if (GetAsyncKeyState(VK_HOME))
		{
			exit(0);
		}
	}
}