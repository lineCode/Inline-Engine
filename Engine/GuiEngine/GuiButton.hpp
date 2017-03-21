#pragma once
#include <BaseLibrary\Common_tmp.hpp>
#include "GuiControl.hpp"
#include "GuiPlane.hpp"
#include "GuiText.hpp"

class GuiButton : public GuiControl
{
public:
	GuiButton();

	void SetBackgroundToColor(Color& baseColor, Color& hoverColor);
	void SetText(const std::wstring& text);
	void SetText(const std::string& text);
	void SetTextAlign(eTextAlign align);

protected:
	GuiPlane* background;
	GuiText*  text;
};

inline GuiButton::GuiButton()
{
	background = AddPlane();
	text = AddText();
}

inline void GuiButton::SetBackgroundToColor(Color& baseColor, Color& hoverColor)
{
	background->SetBaseColor(baseColor);
	background->SetHoverColor(hoverColor);
}

inline void GuiButton::SetText(const std::wstring& text)
{
	this->text->Set(text);
}

inline void GuiButton::SetText(const std::string& text)
{
	this->text->Set(text);
}

inline void GuiButton::SetTextAlign(eTextAlign align)
{
	text->SetAlign(align);
}
