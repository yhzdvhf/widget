#pragma once

#include <functional>

#include "widget_container.hpp"

class Gui
{
	WidgetContainer root;
public:
	Gui();

	void Apply(std::function<void(WidgetContainer*)> callback);

	void MouseMoved(float x, float y);
	void MousePressed(float x, float y);
	void MouseReleased(float x, float y);

	void Render();
};