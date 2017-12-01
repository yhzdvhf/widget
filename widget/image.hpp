#pragma once

#include "widget.hpp"

class Image : public Widget
{
	hgeSprite* spr_ = nullptr;
public:
	Image(const std::string& id, size_t order = 0, WidgetContainer* parent = nullptr);

	void SetTexture(HTEXTURE tex, float x, float y, float w, float h);

	void Render() const override;
};