#pragma once
#include "../imgui/imgui_internal.h"
#include <string>
#include <vector>
#include <random>
#include <functional>
#include "../Fonts/Roboto-Bold.h"
#include "../Fonts/FontAwesome5/font_awesome_5.h"
#include "../Fonts/FontAwesome6/font_awesome_6.h"
#include "../Fonts/Awesome.h"
#include "../Fonts/Awesome_Light.h"

#define MAX_RGB 255.0
#define HELPMARKERDESC(str) ImGui::SameLine(); ImGui::TextColored(ImColor(0, 130, 15, 255), "[ ? ]"); if (ImGui::IsItemHovered()) ImGui::SetTooltip(str)
#define HELPMARKERDISC(str) ImGui::SameLine(); ImGui::TextColored(ImColor(0, 130, 15, 255), "[ * ]"); if (ImGui::IsItemHovered()) ImGui::SetTooltip(str)
#pragma warning(disable: 26812 26815)

ImFont* FA;
ImFont* Header;
ImFont* Body;
ImFont* Body2;
ImGuiWindowFlags windowFlagsChild = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoScrollWithMouse;

namespace ImGui
{
	void SCP(int x, int y)
	{
		ImGui::SetCursorPos(ImVec2(x, y));
	}

	void SCPX(int x)
	{
		ImGui::SetCursorPosX(x);
	}

	void SCPY(int y)
	{
		ImGui::SetCursorPosY(y);
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

	void ButtonSL(const char* buttonName, bool* featureBool, int pos, ImVec2 size, BOOL newLine)
	{
		ImGui::SCPX(pos);
		if (ImGui::Button(buttonName, size))
		{
			*featureBool = true;
		}
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ButtonSCPX(const char* buttonName, bool* featureBool, int pos, ImVec2 size, BOOL newLine)
	{
		ImGui::SCPX(pos);
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
		if (ImGui::Button(buttonName, size))
		{
			*featureBool = true;
		}
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

	void InputIntNL(const char* featureName, int* featureInt, int pos, int size, int min, int max, BOOL sameLine, BOOL newLine)
	{
		ImGui::SCPX(pos);
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

	void SliderIntSCP(const char* featureName, int* featureInt, int min, int max, ImVec2 pos, int size, BOOL sameLine, BOOL newLine)
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

	void StringTypeComboBox(const char* featureName, int pos, int size, BOOL newLine)
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
		ImGui::SCPX(pos);
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

	bool Spinner(const char* label, float radius, int thickness, const ImU32& color) {
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

		int num_segments = 30;
		int start = abs(ImSin(g.Time * 1.8f) * (num_segments - 5));

		const float a_min = IM_PI * 2.0f * ((float)start) / (float)num_segments;
		const float a_max = IM_PI * 2.0f * ((float)num_segments - 3) / (float)num_segments;

		const ImVec2 centre = ImVec2(pos.x + radius, pos.y + radius + style.FramePadding.y);

		for (int i = 0; i < num_segments; i++) {
			const float a = a_min + ((float)i / (float)num_segments) * (a_max - a_min);
			window->DrawList->PathLineTo(ImVec2(centre.x + ImCos(a + g.Time * 8) * radius,
				centre.y + ImSin(a + g.Time * 8) * radius));
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
		Style->Colors[ImGuiCol_Border] = ImColor(18, 18, 18); // ImColor(36, 36, 36); // ImColor(255, 255, 255);
		Style->Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
		Style->Colors[ImGuiCol_FrameBg] = ImColor(18, 18, 18);
		Style->Colors[ImGuiCol_FrameBgHovered] = ImColor(18, 18, 18);
		Style->Colors[ImGuiCol_FrameBgActive] = ImColor(18, 18, 18);
		Style->Colors[ImGuiCol_SliderGrab] = ImColor(255, 0, 255);
		Style->Colors[ImGuiCol_SliderGrabActive] = ImColor(255, 0, 255);
		Style->Colors[ImGuiCol_ScrollbarBg] = ImColor(0, 0, 0, 0);
		Style->Colors[ImGuiCol_ScrollbarGrab] = ImColor(0, 0, 0, 0);
		Style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(0, 0, 0, 0);
		Style->Colors[ImGuiCol_ScrollbarGrabActive] = ImColor(0, 0, 0, 0);
		Style->Colors[ImGuiCol_Button] = ImColor(0, 112, 224);
		Style->Colors[ImGuiCol_ButtonHovered] = ImColor(0, 112, 224);
		Style->Colors[ImGuiCol_ButtonActive] = ImColor(0, 112, 224, 175);
		Style->Colors[ImGuiCol_Separator] = ImColor(180, 180, 180);
		Style->Colors[ImGuiCol_SeparatorActive] = ImColor(180, 180, 180);
		Style->Colors[ImGuiCol_CheckMark] = ImColor(255, 0, 255, 255);
		Style->Colors[ImGuiCol_Header] = ImColor(0, 112, 224, 255);
		Style->Colors[ImGuiCol_HeaderHovered] = ImColor(0, 112, 224, 225);
		Style->Colors[ImGuiCol_HeaderActive] = ImColor(0, 112, 224, 175);
		Style->Colors[ImGuiCol_TextSelectedBg] = ImColor(60, 60, 60);
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
		if (ImGui::BeginChild("MainChildWindow", ImVec2(RSG::iWindowSizeX, RSG::iWindowSizeY), true, windowFlagsChild)) // Window Size = 400 x 600
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
				ImGui::StringTypeComboBox("##StringTypeComboBox", ImGui::GetX() / 2 - 137.5, 275, TRUE);
				ImGui::NewLine();
				ImGui::SCPX(55);
				ImGui::TextSL("String Length", TRUE, FALSE);
				ImGui::SCPX(235);
				ImGui::TextNL("String Amount", TRUE);
				ImGui::InputIntNL("##StringLengthInput", &RSG::iStringLength, 55, 82, 0, 40, TRUE, FALSE);
				ImGui::InputIntNL("##StringAmountInput", &RSG::iStringAmount, 238, 82, 0, 12, FALSE, TRUE);
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
							ImGui::LogToClipboard();
							Notify::Message("  -  String(s) now copied to clipboard  -  ");
							RSG::bCopyToClipboard = false;
						}
						for (int i = 0; i < RSG::sGeneratedStrArray.size(); i++)
						{
							ImGui::CenterText(RSG::sGeneratedStrArray[i].c_str(), 0, FALSE, FALSE);
						}
					}
				} ImGui::EndChild();
			} ImGui::EndChild();
		} ImGui::EndChild();
	}
}