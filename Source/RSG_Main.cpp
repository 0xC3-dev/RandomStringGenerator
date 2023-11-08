/*
*   UPDATE Change Log:
*
*	Update #1 : 11/07/23 | Updated Codebase. Combined UI_Layout.hpp into UI.cpp. Also added Includes.hpp so all headers are cleaned up. Also satisfied all warnings.
* 
*   Update #2 : 11/07/23 | Also fixed an issue with ImGui::LogToClipboard copying the Notify message to the clipboard as well. Replaced it with an ImGui::LogBegin() and ImGui::LogFinish().
*/

#include "RSG_Main.hpp"

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