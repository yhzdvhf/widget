#pragma once

#include "widget.hpp"

class WidgetContainer;

class Image : public Widget
{
	friend WidgetContainer;

	hgeSprite* spr_ = nullptr;

	Image(const std::string& id, size_t order = 0, WidgetContainer* parent = nullptr);

public:
	void SetTexture(HTEXTURE tex, float x, float y, float w, float h);

	void Render() const override;
};