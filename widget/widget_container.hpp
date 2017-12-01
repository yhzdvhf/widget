#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "widget.hpp"

class Gui;

class WidgetContainer : public Widget
{
public:
	WidgetContainer(const std::string& id, size_t order = 0, WidgetContainer* parent = nullptr)
		:Widget(id, order, parent) {}

	template <class T, typename = std::enable_if_t<std::is_base_of<Widget, T>::value>>
	T* AddWidget(const std::string& id, size_t order = 0)
	{
		children_.push_back(std::make_unique<T>(id, order, this));
		indexes_[id] = children_.size() - 1;

		return static_cast<T*>(children_.back().get());
	}
	Widget* GetWidget(std::string id);

	void UpdateRect();

	void Render() const override;

	void MousePressed(float x, float y, WidgetContainer* root) override;
	void MouseReleased(float x, float y, WidgetContainer* root) override;
	void MouseMoved(float x, float y, WidgetContainer* root) override;

	void Sort();
private:
	friend class Gui;

	std::vector<std::unique_ptr<Widget>> children_;
	std::unordered_map<std::string, int> indexes_;
};