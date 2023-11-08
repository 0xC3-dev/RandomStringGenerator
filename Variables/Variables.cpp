#include "Variables.hpp"

namespace RSG
{
	int iScreenSizeX = NULL;
	int iScreenSizeY = NULL;
	int iWindowSizeX = 400;
	int iWindowSizeY = 600;
	int iNotifyPosX = NULL;
	int iNotifyPosY = NULL;
	int iStringLength = NULL;
	int iStringAmount = NULL;
	int iStringType = 1337;
	std::vector <std::string> sGeneratedStrArray{};
	bool bGenerateStrings = false;
	bool bDisplayStrings = false;
	bool bCopyToClipboard = false;
	bool bCopyToClipboardNotify = false;
	bool bOldSliderDesign = false;

	std::string sAllChars{ "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$&-_=+;:.?" };
	std::string sAllNormalChars{ "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890" };
	std::string sLowercaseNumbersChars{ "abcdefghijklmnopqrstuvwxyz1234567890" };
	std::string sLowercaseChars{ "abcdefghijklmnopqrstuvwxyz" };
	std::string sUppercaseNumbersChars{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890" };
	std::string sUppercaseChars{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
	std::string sNumbersChars{ "1234567890" };
	std::random_device rd;
	std::mt19937 generator(rd());
	std::string RandStr(DWORD length, int stringType)
	{
		if (stringType == 0)
		{
			const DWORD char_size = (DWORD)sAllChars.size();
			std::uniform_int_distribution<> random_int(0, char_size - 1);
			std::string output;
			for (DWORD i = 0; i < length; ++i)
				output.push_back(sAllChars[random_int(generator)]);
			return output;
		}
		else if (stringType == 1)
		{
			const DWORD char_size = (DWORD)sAllNormalChars.size();
			std::uniform_int_distribution<> random_int(0, char_size - 1);
			std::string output;
			for (DWORD i = 0; i < length; ++i)
				output.push_back(sAllNormalChars[random_int(generator)]);
			return output;
		}
		else if (stringType == 2)
		{
			const DWORD char_size = (DWORD)sLowercaseNumbersChars.size();
			std::uniform_int_distribution<> random_int(0, char_size - 1);
			std::string output;
			for (DWORD i = 0; i < length; ++i)
				output.push_back(sLowercaseNumbersChars[random_int(generator)]);
			return output;
		}
		else if (stringType == 3)
		{
			const DWORD char_size = (DWORD)sLowercaseChars.size();
			std::uniform_int_distribution<> random_int(0, char_size - 1);
			std::string output;
			for (DWORD i = 0; i < length; ++i)
				output.push_back(sLowercaseChars[random_int(generator)]);
			return output;
		}
		else if (stringType == 4)
		{
			const DWORD char_size = (DWORD)sUppercaseNumbersChars.size();
			std::uniform_int_distribution<> random_int(0, char_size - 1);
			std::string output;
			for (DWORD i = 0; i < length; ++i)
				output.push_back(sUppercaseNumbersChars[random_int(generator)]);
			return output;
		}
		else if (stringType == 5)
		{
			const DWORD char_size = (DWORD)sUppercaseChars.size();
			std::uniform_int_distribution<> random_int(0, char_size - 1);
			std::string output;
			for (DWORD i = 0; i < length; ++i)
				output.push_back(sUppercaseChars[random_int(generator)]);
			return output;
		}
		else if (stringType == 6)
		{
			const DWORD char_size = (DWORD)sNumbersChars.size();
			std::uniform_int_distribution<> random_int(0, char_size - 1);
			std::string output;
			for (DWORD i = 0; i < length; ++i)
				output.push_back(sNumbersChars[random_int(generator)]);
			return output;
		}
		else
		{
			return "Something went wrong...";
		}
	}

	void CalcCenterScreen()
	{
		int iScreenDiffX = RSG::iScreenSizeX - iWindowSizeX;
		int iScreenDiffY = RSG::iScreenSizeY - iWindowSizeY;
		RSG::iScreenSizeX = iScreenDiffX / 2;
		RSG::iScreenSizeY = iScreenDiffY / 2;
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
		if (GetAsyncKeyState(VK_HOME) & 1)
		{
			exit(0);
		}
	}
}