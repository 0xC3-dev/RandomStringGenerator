#include "RSG_Main.h"

int main()
{
    Console::SetConsoleInfo();
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Render::App, nullptr, 0, nullptr);
    while (true)
    {
        Utils::GenerateStrings();
        Sleep(5);
    }
}