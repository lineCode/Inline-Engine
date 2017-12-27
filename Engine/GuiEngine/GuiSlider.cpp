#pragma once
#include "GuiSlider.hpp"
#include "GuiEngine.hpp"

using namespace inl::gui;

GuiSlider::GuiSlider(GuiEngine* guiEngine)
:Gui(guiEngine), value(0), minValue(0), maxValue(1), sliderWidth(5), bSliding(false)
{
	slider = AddGui();
	slider->SetBgIdleColor(ColorI(130, 130, 130, 255));
	slider->SetBgHoverColor(slider->GetBgIdleColor());

	OnTransformChanged += [](Gui* self_, TransformEvent& e)
	{
		GuiSlider* self = self_->AsSlider();
		self->SlideToValue();
	};

	OnCursorEntered += [](Gui* self_, CursorEvent& evt)
	{
		GuiSlider* self = self_->AsSlider();
		self->slider->SetBgActiveColor(self->slider->GetBgIdleColor() + ColorI(65, 65, 65, 0));
	};

	OnCursorLeft += [](Gui* self_, CursorEvent& evt)
	{
		GuiSlider* self = self_->AsSlider();
		self->slider->SetBgActiveColorToIdle();
	};

	// Start drag
	OnCursorPressed += [](Gui* self_, CursorEvent& evt)
	{
		GuiSlider* self = self_->AsSlider();
		self->bSliding = true;
		self->SlideToCursor();
	};

	// Dragging
	guiEngine->OnCursorMoved += [this](CursorEvent& evt)
	{
		if (bSliding)
			SlideToCursor();
	};

	// Stop draw
	guiEngine->OnCursorReleased += [this](CursorEvent& evt)
	{
		bSliding = false;
	};

	SlideToValue();
}

void GuiSlider::SlideToValue(float value)
{
	float normedPercent = value / (maxValue - minValue);
	SlideToNormedPercent(normedPercent);
}

void GuiSlider::SlideToNormedPercent(float normedPercent)
{
	slider->SetSize(sliderWidth, GetHeight());
	slider->SetPos(GetPosX() + normedPercent * (GetWidth() - slider->GetWidth()), GetPosY());
}

void GuiSlider::SlideToCursor()
{
	// Ha cursor sliderHalfWidth() - n�l van akkor 0, ha GetWidth() - sliderHalfWidth() - n�l akkor meg egy
	float normalizedPercent = (GetCursorPosContentSpaceX() - slider->GetHalfWidth()) / (GetWidth() - slider->GetWidth());
	normalizedPercent = Clamp01(normalizedPercent);
	SlideToNormedPercent(normalizedPercent);
}

void GuiSlider::SetValue(float val)
{
	value = Clamp(val, minValue, maxValue);
	SlideToValue(value);
	OnValueChanged(this, val);
}

void GuiSlider::SetMinValue(float val)
{
	minValue = val;
	val = Clamp(val, minValue, maxValue);
	SetValue(val);
}

void GuiSlider::SetMaxValue(float val)
{
	maxValue = val;
	val = Clamp(val, minValue, maxValue);
	SetValue(val);
}