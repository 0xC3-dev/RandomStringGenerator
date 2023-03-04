#pragma once
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imgui_impl_dx11.h"
#include "../Variables/Variables.h"
#include "../Notify/Notify.h"
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#define WND_SIZEX GetSystemMetrics(SM_CXSCREEN) 
#define WND_SIZEY GetSystemMetrics(SM_CYSCREEN)

namespace Render
{
	void App();
	void UI();
}