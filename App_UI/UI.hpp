#pragma once
#include "../Variables/Variables.hpp"
#include "../Notify/Notify.hpp"

#define WND_SIZEX GetSystemMetrics(SM_CXSCREEN) 
#define WND_SIZEY GetSystemMetrics(SM_CYSCREEN)

namespace Render
{
	void App();
	void UI();
}