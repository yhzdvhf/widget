#include "image.hpp"

Image::Image(const std::string & id, size_t order, WidgetContainer * parent)
	:Widget(id, order, parent) {}

void Image::SetTexture(HTEXTURE tex, float x, float y, float w, float h)
{
	spr_ = new hgeSprite(tex, x, y, w, h);
}

void Image::Render() const
{
	if (!visible_)
		return;

	spr_->RenderStretch(rect_.x, rect_.y, rect_.x + rect_.w, rect_.y + rect_.h);
}
