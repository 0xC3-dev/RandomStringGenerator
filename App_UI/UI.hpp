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

namespace ImGui
{
	void SCP(float xPos, float yPos);

	void SCPX(float xPos);

	void SCPY(float yPos);

	void Line(int newId);

	void Linevertical();

	void CenterText(const char* text, int lineId, BOOL separator, BOOL newLine);

	void CenterTextHeader(const char* text, int lineId, BOOL separator, BOOL newLine);

	void CenterTextBody(const char* text, int lineId, BOOL separator, BOOL newLine);

	void CenterTextEx(const char* text, float width, int lineId, BOOL separator);

	void TextNL(const char* text, BOOL newLine);

	void TextSL(const char* text, BOOL sameLine, BOOL newLine);

	void TextSCP(const char* text, ImVec2 pos, BOOL newLine);

	void TextBodyNL(const char* text, BOOL newLine);

	void CheckBoxSCP(const char* featureName, bool* featureBool, ImVec2 pos);

	void CheckBoxNL(const char* featureName, bool* featureBool, BOOL newLine);

	void ButtonSL(const char* buttonName, bool* featureBool, float xPos, ImVec2 size, BOOL newLine);

	void ButtonSCPX(const char* buttonName, bool* featureBool, float xPos, ImVec2 size, BOOL newLine);

	void ButtonSCP(const char* buttonName, bool* featureBool, ImVec2 pos, ImVec2 size, BOOL newLine);

	void ButtonNL(const char* buttonName, bool* featureBool, ImVec2 size, BOOL newLine);

	void ButtonPageNL(const char* buttonName, int* page, int pageNumber, ImVec2 size, BOOL newLine);

	void ButtonCenterNL(const char* buttonName, bool* featureBool, ImVec2 size, BOOL newLine);

	void ButtonSwitchSCP(const char* buttonName, bool* featureBool, ImVec2 pos, ImVec2 size, BOOL newLine);

	void InputIntNL(const char* featureName, int* featureInt, float xPos, float size, int min, int max, BOOL sameLine, BOOL newLine);

	void SliderIntSCP(const char* featureName, int* featureInt, int min, int max, ImVec2 pos, float size, BOOL sameLine, BOOL newLine);

	void SliderIntCustomSCP(const char* featureName, int* featureInt, int min, int max, float size, float xPos, BOOL sameLine, BOOL newLine);

	void StringTypeComboBox(const char* featureName, float xPos, float size, BOOL newLine);

	void ToggleNL(const char* toggleName, bool* featureBool, BOOL newLine);

	bool Spinner(const char* label, float radius, float thickness, const ImU32& color);

	float GetX();

	float GetY();

	void UITheme();

	void PushStyleColorCustom(ImColor textColor);

	void CloseMinimizeButtons();

	void MainUISetup();
}