﻿#pragma once

#include <functional>
#include <string>

#include "hgesprite.h"

struct Rect {
	float x, y, w, h;

	bool Contain(float px, float py)
	{
		if (px > x && px < x + w && py > y && py < y + h)
			return true;

		return false;
	}
	void Append(const Rect& r)
	{
		if (x > r.x) x = r.x;
		if (y > r.y) y = r.y;
		if (x + w < r.x + r.w) w = r.x + r.w - x;
		if (y + h < r.y + r.h) h = r.y + r.h - y;
	}
};

class WidgetContainer;

class Widget 
{
	friend class WidgetContainer;
public:
	using MouseCallback = std::function<bool(WidgetContainer*)>;

	Widget(const std::string& id, size_t order = 0, WidgetContainer* parent = nullptr);
	
	void OnMousePressed(MouseCallback callback);
	void OnMouseReleased(MouseCallback callback);
	void OnMouseEnter(MouseCallback callback);
	void OnMouseLeave(MouseCallback callback);

	virtual void MousePressed(float x, float y, WidgetContainer* root) {}
	virtual void MouseReleased(float x, float y, WidgetContainer* root) {}
	virtual void MouseMoved(float x, float y, WidgetContainer* root) {}
	virtual void MouseEnter(float x, float y, WidgetContainer* root) {}
	virtual void MouseLeave(float x, float y, WidgetContainer* root) {}

	virtual void Sort() {}

	virtual void Render() const = 0;

	Rect GetRect() const;
	void SetPos(float x, float y);
	void SetSize(float w, float h);

	void SetOrder(int order, bool sort = true);
	int  GetOrder() const;
	void Show();
	void Hide();

	bool IsVisible() const;

protected:
	std::string      id_;
	size_t           order_ = 0;
	Rect             rect_;
	bool             visible_ = true;
	bool             hovered_ = false;
	WidgetContainer* parent_  = nullptr;

	MouseCallback mouse_pressed_  = [](WidgetContainer*) {return false; };
	MouseCallback mouse_released_ = [](WidgetContainer*) {return false; };
	MouseCallback mouse_enter_    = [](WidgetContainer*) {return false; };
	MouseCallback mouse_leave_    = [](WidgetContainer*) {return false; };
};