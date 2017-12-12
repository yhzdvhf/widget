#pragma once

#include "widget.hpp"

class WidgetContainer;

class Button : public Widget
{
	friend WidgetContainer;

	bool pressed_ = false;
	bool hovered_ = false;
	hgeSprite* spr_;
	hgeSprite* spr_pressed_;
	hgeSprite* spr_hovered_;

	Button(const std::string& id, size_t order = 0, WidgetContainer* parent = nullptr);

public:
	void SetTexture(HTEXTURE tex, float x, float y, float w, float h);
	void SetPressedTexture(HTEXTURE tex, float x, float y, float w, float h);
	void SetHoveredTexture(HTEXTURE tex, float x, float y, float w, float h);

	void MousePressed(float x, float y, WidgetContainer* root) override;
	void MouseReleased(float x, float y, WidgetContainer* root) override;
	void MouseEnter(float x, float y, WidgetContainer* root) override;
	void MouseLeave(float x, float y, WidgetContainer* root) override;

	void Render() const override;
};