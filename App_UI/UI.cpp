#include "UI.hpp"
#include <iostream>
#define MAX_RGB 255.0
#define HELPMARKERDESC(str) ImGui::SameLine(); ImGui::TextColored(ImColor(0, 130, 15, 255), "[ ? ]"); if (ImGui::IsItemHovered()) ImGui::SetTooltip(str)
#define HELPMARKERDISC(str) ImGui::SameLine(); ImGui::TextColored(ImColor(0, 130, 15, 255), "[ * ]"); if (ImGui::IsItemHovered()) ImGui::SetTooltip(str)
#pragma warning(disable: 26812 26815)

// Data
static ID3D11Device* g_pd3dDevice = NULL;
static ID3D11DeviceContext* g_pd3dDeviceContext = NULL;
static IDXGISwapChain* g_pSwapChain = NULL;
static ID3D11RenderTargetView* g_mainRenderTargetView = NULL;
static ID3D11ShaderResourceView* splashScreen = nullptr;
static HWND hwnd = nullptr;
static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

static ImFont* FA = 0;
static ImFont* Header = 0;
static ImFont* Body = 0;
static ImFont* Body2 = 0;
static ImGuiWindowFlags windowFlagsChild = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoScrollWithMouse;

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool CreateDeviceD3D(HWND hWnd)
{
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}
void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
}
void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
    pBackBuffer->Release();
}
void CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
}
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
            CreateRenderTarget();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    case WM_DPICHANGED:
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DpiEnableScaleViewports)
        {
            //const int dpi = HIWORD(wParam);
            //printf("WM_DPICHANGED to %d (%.0f%%)\n", dpi, (float)dpi / 96.0f * 100.0f);
            const RECT* suggested_rect = (RECT*)lParam;
            ::SetWindowPos(hWnd, NULL, suggested_rect->left, suggested_rect->top, suggested_rect->right - suggested_rect->left, suggested_rect->bottom - suggested_rect->top, SWP_NOZORDER | SWP_NOACTIVATE);
        }
        break;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

// Create App Window.
void Render::App()
{
    RSG::iScreenSizeX = WND_SIZEX;
    RSG::iScreenSizeY = WND_SIZEY;
	RSG::iNotifyPosX = WND_SIZEX;
	RSG::iNotifyPosY = WND_SIZEY;

    RSG::CalcCenterScreen();

    // Create application window
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, "RSG", NULL };
    RegisterClassEx(&wc);
    hwnd = CreateWindow(wc.lpszClassName, "RSG", WS_POPUP | WS_OVERLAPPED, 0, 0, 0, 0, NULL, NULL, wc.hInstance, NULL);

    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        UnregisterClass(wc.lpszClassName, wc.hInstance);
        return;
    }

    ShowWindow(hwnd, FALSE);
    UpdateWindow(hwnd);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.IniFilename = NULL;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

    static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
    ImFontConfig icons_config; icons_config.MergeMode = true; icons_config.PixelSnapH = true;

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui::StyleColorsDark();
    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(Roboto_compressed_data, Roboto_compressed_size, 16.f, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
    Header = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(Roboto_compressed_data, Roboto_compressed_size, 26.f, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
    Body = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(Roboto_compressed_data, Roboto_compressed_size, 18.f, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
    Body2 = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(Roboto_compressed_data, Roboto_compressed_size, 14.f, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
    FA = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(awesome_light_compressed_data, awesome_light_compressed_size, 18.0f, &icons_config, icons_ranges);

    notify::init();

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        }
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        {
            Render::UI();
            if (GetAsyncKeyState(VK_HOME))
            {
                RSG::WinClose();
            }
        }
        ImGui::EndFrame();
        ImGui::Render();

        // Rendering
        ImGui::Render();
        const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        g_pSwapChain->Present(1, 0); // Present with vsync
        //g_pSwapChain->Present(0, 0); // Present without vsync
    }

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    DestroyWindow(hwnd);
    UnregisterClass(wc.lpszClassName, wc.hInstance);

    return;
}

// Helper Functions to make ImGui easier/quicker to use.
namespace ImGui
{
	void SCP(float xPos, float yPos)
	{
		ImGui::SetCursorPos(ImVec2(xPos, yPos));
	}

	void SCPX(float xPos)
	{
		ImGui::SetCursorPosX(xPos);
	}

	void SCPY(float yPos)
	{
		ImGui::SetCursorPosY(yPos);
	}

	void Line(int newId)
	{
		std::string id = ("ImGui_Sauce_line_" + std::to_string(newId));
		ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
		{
			ImGui::BeginChild(id.c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 1), false);
			ImGui::Separator();
			ImGui::EndChild();
		}
		ImGui::PopStyleColor();
	}

	void Linevertical()
	{
		ImGui::SameLine();
		ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
		ImGui::SameLine();
	}

	void CenterText(const char* text, int lineId, BOOL separator, BOOL newLine)
	{
		if (text == nullptr)
			return;

		ImGui::Spacing();
		ImGui::SameLine((ImGui::GetContentRegionAvail().x / 2) - (ImGui::CalcTextSize(text).x / 2));
		ImGui::Text(text);
		ImGui::Spacing();

		if (separator)
		{
			ImGui::NewLine();
			Line(lineId);
		}

		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void CenterTextHeader(const char* text, int lineId, BOOL separator, BOOL newLine)
	{
		if (text == nullptr)
			return;

		ImGui::Spacing();
		ImGui::PushFont(Header);
		ImGui::SameLine((ImGui::GetContentRegionAvail().x / 2) - (ImGui::CalcTextSize(text).x / 2));
		ImGui::Text(text);
		ImGui::PopFont();
		ImGui::Spacing();

		if (separator)
		{
			ImGui::NewLine();
			Line(lineId);
		}

		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void CenterTextBody(const char* text, int lineId, BOOL separator, BOOL newLine)
	{
		if (text == nullptr)
			return;

		ImGui::Spacing();
		ImGui::PushFont(Body);
		ImGui::SameLine((ImGui::GetContentRegionAvail().x / 2) - (ImGui::CalcTextSize(text).x / 2));
		ImGui::Text(text);
		ImGui::PopFont();
		ImGui::Spacing();

		if (separator)
		{
			ImGui::NewLine();
			Line(lineId);
		}

		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void CenterTextEx(const char* text, float width, int lineId, BOOL separator)
	{
		if (text == nullptr)
			return;

		ImGui::Spacing();
		ImGui::SameLine((width / 2) - (ImGui::CalcTextSize(text).x / 2));
		ImGui::Text(text);
		ImGui::Spacing();

		if (separator)
			Line(lineId);
	}

	void TextNL(const char* text, BOOL newLine)
	{
		ImGui::Text(text);

		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void TextSL(const char* text, BOOL sameLine, BOOL newLine)
	{
		ImGui::Text(text);

		if (sameLine)
		{
			ImGui::SameLine();
		}

		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void TextSCP(const char* text, ImVec2 pos, BOOL newLine)
	{
		ImGui::SCP(pos.x, pos.y);
		ImGui::Text(text);

		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void TextBodyNL(const char* text, BOOL newLine)
	{
		ImGui::PushFont(Body);
		ImGui::Text(text);
		ImGui::PopFont();

		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void CheckBoxSCP(const char* featureName, bool* featureBool, ImVec2 pos)
	{
		ImGui::SCP(pos.x, pos.y);
		ImGui::Checkbox(featureName, featureBool);
	}

	void CheckBoxNL(const char* featureName, bool* featureBool, BOOL newLine)
	{
		ImGui::Checkbox(featureName, featureBool);
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ButtonSL(const char* buttonName, bool* featureBool, float xPos, ImVec2 size, BOOL newLine)
	{
		ImGui::SCPX(xPos);
		if (ImGui::Button(buttonName, size))
		{
			*featureBool = true;
		}
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ButtonSCPX(const char* buttonName, bool* featureBool, float xPos, ImVec2 size, BOOL newLine)
	{
		ImGui::SCPX(xPos);
		if (ImGui::Button(buttonName, size))
		{
			*featureBool = true;
		}
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ButtonSCP(const char* buttonName, bool* featureBool, ImVec2 pos, ImVec2 size, BOOL newLine)
	{
		ImGui::SCP(pos.x, pos.y);
		ImGui::PushFont(FA);
		if (ImGui::Button(buttonName, size))
		{
			*featureBool = !*featureBool;
		}
		ImGui::PopFont();
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ButtonNL(const char* buttonName, bool* featureBool, ImVec2 size, BOOL newLine)
	{
		if (ImGui::Button(buttonName, size))
		{
			*featureBool = true;
		}
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ButtonPageNL(const char* buttonName, int* page, int pageNumber, ImVec2 size, BOOL newLine)
	{
		if (ImGui::Button(buttonName, size))
		{
			*page = pageNumber;
		}
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ButtonCenterNL(const char* buttonName, bool* featureBool, ImVec2 size, BOOL newLine)
	{
		ImGui::Spacing();
		ImGui::SameLine((ImGui::GetContentRegionAvail().x / 2) - (ImGui::CalcTextSize(buttonName).x / 2));
		if (ImGui::Button(buttonName, size))
		{
			*featureBool = true;
		}
		ImGui::PopFont();
		ImGui::Spacing();
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ButtonSwitchSCP(const char* buttonName, bool* featureBool, ImVec2 pos, ImVec2 size, BOOL newLine)
	{
		ImGui::SCP(pos.x, pos.y);
		if (ImGui::Button(buttonName, size))
		{
			*featureBool = !*featureBool;
		}
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void InputIntNL(const char* featureName, int* featureInt, float xPos, float size, int min, int max, BOOL sameLine, BOOL newLine)
	{
		ImGui::SCPX(xPos);
		ImGui::PushItemWidth(size);
		if (ImGui::InputInt(featureName, featureInt))
		{
			if (*featureInt < min)
			{
				*featureInt = min;
			}
			if (*featureInt > max)
			{
				*featureInt = max;
			}
		}
		ImGui::PopItemWidth();
		if (sameLine)
		{
			ImGui::SameLine();
		}
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void SliderIntSCP(const char* featureName, int* featureInt, int min, int max, ImVec2 pos, float size, BOOL sameLine, BOOL newLine)
	{
		ImGui::SCP(pos.x, pos.y);
		ImGui::PushItemWidth(size);
		ImGui::SliderInt(featureName, featureInt, min, max);
		ImGui::PopItemWidth();
		if (sameLine)
		{
			ImGui::SameLine();
		}
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void SliderIntCustomSCP(const char* featureName, int* featureInt, int min, int max, float size, float xPos, BOOL sameLine, BOOL newLine)
	{
		ImGui::SCPX(xPos);
		ImGui::PushItemWidth(size);
		ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(64, 64, 64, 255)));
		ImGui::SliderIntCustom(featureName, featureInt, min, max);
		ImGui::PopStyleColor();
		ImGui::PopItemWidth();
		if (sameLine)
		{
			ImGui::SameLine();
		}
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void StringTypeComboBox(const char* featureName, float xPos, float size, BOOL newLine)
	{
		const char* comboList[] = {
			" All Chars ( Ex. abcABC123!$% )",
			" No Special Chars ( Ex. abcABC123 )",
			" Lowercase w/ Numbers ( Ex. abc123 )",
			" Lowercase w/o Numbers ( Ex. abc )",
			" Uppercase w/ Numbers ( Ex. ABC123 )",
			" Uppercase w/o Numbers ( Ex. ABC )",
			" Numbers Only ( Ex. 123 )"
		};
		static const char* currentItem = " Select String Type";
		ImGui::SCPX(xPos);
		ImGui::PushItemWidth(size);
		if (ImGui::BeginCombo(featureName, currentItem))
		{
			for (int n = 0; n < IM_ARRAYSIZE(comboList); n++)
			{
				bool bIsSelected = (currentItem == comboList[n]);
				if (ImGui::Selectable(comboList[n], bIsSelected))
					currentItem = comboList[n];
				if (ImGui::IsItemClicked(bIsSelected))
				{
					ImGui::SetItemDefaultFocus();
					if (n == 0)
					{
						RSG::iStringType = 0;
					}
					if (n == 1)
					{
						RSG::iStringType = 1;
					}
					if (n == 2)
					{
						RSG::iStringType = 2;
					}
					if (n == 3)
					{
						RSG::iStringType = 3;
					}
					if (n == 4)
					{
						RSG::iStringType = 4;
					}
					if (n == 5)
					{
						RSG::iStringType = 5;
					}
					if (n == 6)
					{
						RSG::iStringType = 6;
					}
				}
			}
			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ToggleNL(const char* toggleName, bool* featureBool, BOOL newLine)
	{
		ImVec2 p = ImGui::GetCursorScreenPos();
		ImDrawList* draw_list = ImGui::GetWindowDrawList();

		float height = ImGui::GetFrameHeight();
		float width = height * 1.55f;
		float radius = height * 0.50f;

		ImGui::InvisibleButton(toggleName, ImVec2(width, height));
		if (ImGui::IsItemClicked())
			*featureBool = !*featureBool;

		float t = *featureBool ? 1.0f : 0.0f;

		ImGuiContext& g = *GImGui;
		float ANIM_SPEED = 0.08f;
		if (g.LastActiveId == g.CurrentWindow->GetID(toggleName))// && g.LastActiveIdTimer < ANIM_SPEED)
		{
			float t_anim = ImSaturate(g.LastActiveIdTimer / ANIM_SPEED);
			t = *featureBool ? (t_anim) : (1.0f - t_anim);
		}

		ImU32 col_bg;
		if (ImGui::IsItemHovered())
			col_bg = ImGui::GetColorU32(ImLerp(ImVec4(0.78f, 0.78f, 0.78f, 0.40f), ImVec4(ImColor(255, 0, 255, 200)), t)); // ImColor(255, 0, 255, 255) // 0.64f, 0.83f, 0.34f, 1.0f
		else
			col_bg = ImGui::GetColorU32(ImLerp(ImVec4(0.85f, 0.85f, 0.85f, 0.60f), ImVec4(ImColor(255, 0, 255, 255)), t)); // ImColor(255, 0, 255, 255) // 0.56f, 0.83f, 0.26f, 1.0f

		draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
		draw_list->AddCircleFilled(ImVec2(p.x + radius + t * (width - radius * 2.0f), p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));

		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	bool Spinner(const char* label, float radius, float thickness, const ImU32& color) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size((radius) * 2, (radius + style.FramePadding.y) * 2);

		const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
		ImGui::ItemSize(bb, style.FramePadding.y);
		if (!ImGui::ItemAdd(bb, id))
			return false;

		// Render
		window->DrawList->PathClear();

		float num_segments = 30.f;
		float start = abs(ImSin((float)g.Time * 1.8f) * (num_segments - 5.f));

		const float a_min = IM_PI * 2.0f * (start) / num_segments;
		const float a_max = IM_PI * 2.0f * (num_segments - 3.f) / num_segments;

		const ImVec2 centre = ImVec2(pos.x + radius, pos.y + radius + style.FramePadding.y);

		for (float i = 0; i < num_segments; i++) {
			const float a = a_min + (i / num_segments) * (a_max - a_min);
			window->DrawList->PathLineTo(ImVec2(centre.x + ImCos(a + (float)g.Time * 8) * radius,
				centre.y + ImSin(a + (float)g.Time * 8) * radius));
		}

		window->DrawList->PathStroke(color, false, thickness);
	}

	float GetX()
	{
		return ImGui::GetContentRegionAvail().x;
	}

	float GetY()
	{
		return ImGui::GetContentRegionAvail().y;
	}

	void UITheme()
	{
		ImGui::SetColorEditOptions(ImGuiColorEditFlags_Float | ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_PickerHueWheel);
		ImGuiStyle* Style = &ImGui::GetStyle();
		Style->WindowBorderSize = 0;
		Style->FrameBorderSize = 0;
		Style->WindowRounding = 4;
		Style->ChildRounding = 2;
		Style->ChildBorderSize = 2;
		Style->FrameRounding = 0;
		Style->ScrollbarSize = 2;
		Style->WindowPadding = ImVec2(0, 0);
		Style->FramePadding = ImVec2(0, 0);
		Style->ItemSpacing = ImVec2(0, 0);
		Style->ItemInnerSpacing = ImVec2(0, 0);
		Style->IndentSpacing = 0;
		Style->DisplayWindowPadding = ImVec2(0, 0);
		Style->Colors[ImGuiCol_WindowBg] = ImColor(18, 18, 18);
		Style->Colors[ImGuiCol_ChildBg] = ImColor(18, 18, 18);
		Style->Colors[ImGuiCol_Border] = ImColor(18, 18, 18);
		Style->Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
		Style->Colors[ImGuiCol_FrameBg] = ImColor(18, 18, 18);
		Style->Colors[ImGuiCol_FrameBgHovered] = ImColor(18, 18, 18);
		Style->Colors[ImGuiCol_FrameBgActive] = ImColor(18, 18, 18);
		Style->Colors[ImGuiCol_SliderGrab] = ImColor(0, 112, 224);
		Style->Colors[ImGuiCol_SliderGrabActive] = ImColor(0, 112, 224);
		Style->Colors[ImGuiCol_ScrollbarBg] = ImColor(0, 0, 0, 0);
		Style->Colors[ImGuiCol_ScrollbarGrab] = ImColor(0, 0, 0, 0);
		Style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(0, 0, 0, 0);
		Style->Colors[ImGuiCol_ScrollbarGrabActive] = ImColor(0, 0, 0, 0);
		Style->Colors[ImGuiCol_Button] = ImColor(0, 112, 224, 255);
		Style->Colors[ImGuiCol_ButtonHovered] = ImColor(0, 112, 224, 175);
		Style->Colors[ImGuiCol_ButtonActive] = ImColor(0, 112, 224, 125);
		Style->Colors[ImGuiCol_Separator] = ImColor(180, 180, 180);
		Style->Colors[ImGuiCol_SeparatorActive] = ImColor(180, 180, 180);
		Style->Colors[ImGuiCol_CheckMark] = ImColor(0, 112, 224, 255);
		Style->Colors[ImGuiCol_Header] = ImColor(0, 112, 224, 255);
		Style->Colors[ImGuiCol_HeaderHovered] = ImColor(0, 112, 224, 225);
		Style->Colors[ImGuiCol_HeaderActive] = ImColor(0, 112, 224, 175);
		Style->Colors[ImGuiCol_NavHighlight] = ImColor(0, 112, 224, 255);
		Style->Colors[ImGuiCol_NavWindowingHighlight] = ImColor(0, 112, 224, 175);
		Style->Colors[ImGuiCol_NavWindowingDimBg] = ImColor(0, 112, 224, 125);
	}

	void PushStyleColorCustom(ImColor textColor)
	{
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 0.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.f, 0.f, 0.f, 0.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.f, 0.f, 0.f, 0.f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(textColor));
	}

	void CloseMinimizeButtons()
	{
		ImGui::SCP(335, 0);
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(18, 18, 18, 255)));
		if (ImGui::BeginChild("CloseMinimizeWindow", ImVec2(55, 20), true, windowFlagsChild))
		{
			// Minimize and Close Button.
			ImGui::SCP(5, -5);
			ImGui::PushFont(FA);
			ImGui::PushStyleColorCustom(ImColor(255, 255, 255, 255));
			if (ImGui::Button(ICON_FA_WINDOW_MINIMIZE, ImVec2(25, 20)))
			{
				RSG::WinMinimize("RSG");
			}
			if (ImGui::IsItemHovered())
			{
				ImGui::SCP(5, -5);
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(252, 186, 3, 255)));
				if (ImGui::Button(ICON_FA_WINDOW_MINIMIZE, ImVec2(25, 20)))
				{
					RSG::WinMinimize("RSG");
				}
				ImGui::PopStyleColor();
			}
			ImGui::SCP(30, 2);
			if (ImGui::Button(ICON_FA_TIMES, ImVec2(25, 20)))
			{
				RSG::WinClose();
			}
			if (ImGui::IsItemHovered())
			{
				ImGui::SCP(30, 2);
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 0, 0, 255)));
				if (ImGui::Button(ICON_FA_TIMES, ImVec2(25, 20)))
				{
					RSG::WinClose();
				}
				ImGui::PopStyleColor();
			}
			ImGui::PopStyleColor(4);
			ImGui::PopFont();
		} ImGui::PopStyleColor(); ImGui::EndChild();
	}

	void MainUISetup()
	{
		// Main Child Window to Store All other Childs in.
		ImGui::SCP(0, 0);
		if (ImGui::BeginChild("MainChildWindow", ImVec2((float)RSG::iWindowSizeX, (float)RSG::iWindowSizeY), true, windowFlagsChild)) // Window Size = 400 x 600
		{
			// Top Header Window.
			ImGui::SCP(0, 0);
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(28, 28, 28, 255)));
			if (ImGui::BeginChild("TopHeaderWindow", ImVec2(400, 50), true, windowFlagsChild))
			{
				// Render Close and Minimize Buttons.
				ImGui::CloseMinimizeButtons();

				// Main App Header.
				ImGui::SCPY(15);
				ImGui::PushFont(Header);
				ImGui::CenterText("Random String Generator", 0, FALSE, FALSE);
				ImGui::PopFont();
			} ImGui::PopStyleColor(); ImGui::EndChild();

			// Generatation Settings Window.
			ImGui::SCP(10, 60);
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(28, 28, 28, 255)));
			if (ImGui::BeginChild("GenerationSettingsWindow", ImVec2(380, 225), true, windowFlagsChild))
			{
				// Generate Strings Window Header.
				ImGui::SCP(ImGui::GetX() / 2 - 100, 15);
				ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(18, 18, 18, 255)));
				if (ImGui::BeginChild("GenRandStrHeaderBg", ImVec2(200, 20), true, windowFlagsChild))
				{
					ImGui::PushFont(Body);
					ImGui::CenterText("Generate Random Strings", 0, FALSE, FALSE);
					ImGui::PopFont();
				} ImGui::PopStyleColor(); ImGui::EndChild();

				// Generate Strings Settings.
				ImGui::SCPY(60);
				ImGui::StringTypeComboBox("##StringTypeComboBox", ImGui::GetX() / 2 - 137.5f, 275, TRUE);
				ImGui::NewLine();
				ImGui::SCPX(55);
				ImGui::TextSL("String Length", TRUE, FALSE);
				ImGui::SCPX(235);
				ImGui::TextNL("String Amount", TRUE);
				if (!RSG::bOldSliderDesign)
				{
					ImGui::SliderIntCustomSCP("##StringLength", &RSG::iStringLength, 0, 40, 92, 50, TRUE, FALSE);
					ImGui::SliderIntCustomSCP("##StringAmount", &RSG::iStringAmount, 0, 12, 92, 230, FALSE, TRUE);
				}
				else
				{
					ImGui::InputIntNL("##StringLengthInput", &RSG::iStringLength, 55, 82, 0, 40, TRUE, FALSE);
					ImGui::InputIntNL("##StringAmountInput", &RSG::iStringAmount, 238, 82, 0, 12, FALSE, TRUE);
				}
				ImGui::NewLine();
				ImGui::ButtonSCPX("GENERATE", &RSG::bGenerateStrings, ImGui::GetX() / 2 - 50, ImVec2(100, 20), FALSE);
			} ImGui::PopStyleColor(); ImGui::EndChild();

			// Generated String(s) Window.
			ImGui::SCP(10, 295);
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(28, 28, 28, 255)));
			if (ImGui::BeginChild("GeneratedStringsWindow", ImVec2(380, 292), true, windowFlagsChild))
			{
				// Generated Strings Window Header.
				ImGui::SCP(ImGui::GetX() / 2 - 100, 15);
				ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(18, 18, 18, 255)));
				if (ImGui::BeginChild("GeneratedStrHeaderBg", ImVec2(200, 20), true, windowFlagsChild))
				{
					ImGui::PushFont(Body);
					ImGui::CenterText("Generated String(s)", 0, FALSE, FALSE);
					ImGui::PopFont();
				} ImGui::PopStyleColor(); ImGui::EndChild();

				// Copy Button.
				if (!RSG::bDisplayStrings)
				{
					RSG::bCopyToClipboard = false;
				}

				ImGui::ButtonSCP(ICON_FA_GRIP_LINES, &RSG::bOldSliderDesign, ImVec2(20, 30), ImVec2(50, 20), FALSE);
				ImGui::ButtonSCP("COPY", &RSG::bCopyToClipboard, ImVec2(310, 30), ImVec2(50, 20), FALSE);

				// Display Strings Window.
				ImGui::SCP(10, 60);
				ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(18, 18, 18, 255)));
				if (ImGui::BeginChild("DisplayStringsWindow", ImVec2(360, 220), true, windowFlagsChild))
				{
					ImGui::SCPY(13);
					if (RSG::bDisplayStrings)
					{
						if (RSG::bCopyToClipboard)
						{
							ImGui::LogBegin(ImGuiLogType_Clipboard, -1);
							RSG::bCopyToClipboardNotify = true;
							RSG::bCopyToClipboard = false;
						}
						for (int i = 0; i < RSG::sGeneratedStrArray.size(); i++)
						{
							ImGui::CenterText(RSG::sGeneratedStrArray[i].c_str(), 0, FALSE, FALSE);
						}
						if (RSG::bCopyToClipboardNotify)
						{
							ImGui::LogFinish();
							Notify::Message("  -  String(s) now copied to clipboard  -  ");
							RSG::bCopyToClipboardNotify = false;
						}
					}
				} ImGui::PopStyleColor(); ImGui::EndChild();
			} ImGui::PopStyleColor(); ImGui::EndChild();
		} ImGui::EndChild();
	}
}

// Render App UI.
void Render::UI()
{
    ImGui::UITheme();

    ImGui::SetNextWindowPos(ImVec2((float)RSG::iScreenSizeX, (float)RSG::iScreenSizeY), ImGuiCond_Once);

    ImGui::Begin("RSG", 0, windowFlagsChild);

    ImGui::MainUISetup();

    notify::render();

    ImGui::End();
}