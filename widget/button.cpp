#include "button.hpp"

Button::Button(const std::string & id, size_t order, WidgetContainer * parent)
	:Widget(id, order, parent) {}

void Button::SetTexture(HTEXTURE tex, float x, float y, float w, float h)
{
	spr_ = new hgeSprite(tex, x, y, w, h);
}

void Button::SetPressedTexture(HTEXTURE tex, float x, float y, float w, float h)
{
	spr_pressed_ = new hgeSprite(tex, x, y, w, h);
}

void Button::SetHoveredTexture(HTEXTURE tex, float x, float y, float w, float h)
{
	spr_hovered_ = new hgeSprite(tex, x, y, w, h);
}

void Button::MousePressed(float x, float y, WidgetContainer * root)
{
	pressed_ = true;
}

void Button::MouseReleased(float x, float y, WidgetContainer * root)
{
	pressed_ = false;
}

void Button::MouseEnter(float x, float y, WidgetContainer * root)
{
	hovered_ = true;
}

void Button::MouseLeave(float x, float y, WidgetContainer * root)
{
	hovered_ = false;
	pressed_ = false;
}

void Button::Render() const
{
	if (!visible_)
		return;

	if (pressed_)
		spr_pressed_->RenderStretch(rect_.x, rect_.y, rect_.x + rect_.w, rect_.y + rect_.h);
	else if (hovered_)
		spr_hovered_->RenderStretch(rect_.x, rect_.y, rect_.x + rect_.w, rect_.y + rect_.h);
	else
		spr_->RenderStretch(rect_.x, rect_.y, rect_.x + rect_.w, rect_.y + rect_.h);
}
