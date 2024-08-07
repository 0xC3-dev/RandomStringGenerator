﻿/*
*   UPDATE Change Log:
*
*	Update #1 : 11/07/23 | Updated Codebase. Combined UI_Layout.hpp into UI.cpp. Also added Includes.hpp so all headers are cleaned up. Also satisfied all warnings with the exception of the WinMain param warnings.
* 
*   Update #2 : 11/07/23 | Also fixed an issue with ImGui::LogToClipboard copying the Notify message to the clipboard as well. Replaced it with an ImGui::LogBegin() and ImGui::LogFinish().
* 
*   Update #3 : 11/07/23 | Changed Sub System type from Console to Windows so the Console App does not show regardless if your on Windows 10 or 11.
* 
*   Update #4 : 11/07/23 | Finally added version info to the application.
* 
*   Update #5 : 11/07/23 | Added tooltip for Slider Design button.
* 
*   Update #6 : 06/27/24 | Cleaned up codebase. Included D3D11 SDK in the project.
*/

#include "RSG_Main.hpp"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nShowCmd);
    Console::SetConsoleInfo();
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Render::App, nullptr, 0, nullptr);
    while (true)
    {
        Utils::GenerateStrings();
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}