#include <algorithm>

#include "widget_container.hpp"

Widget * WidgetContainer::GetWidget(std::string id)
{
	return children_[indexes_[id]].get();
}

void WidgetContainer::UpdateRect()
{
	for (const auto& child : children_)
	{
		auto r = child->GetRect();
		rect_.Append(r);
	}
}

void WidgetContainer::Render() const
{
	for (const auto& child : children_) {
		if (visible_)
			child->Render();
	}
}

void WidgetContainer::MousePressed(float x, float y, WidgetContainer * root)
{
	for (auto child = children_.rbegin(); child != children_.rend(); ++child)
	{
		if (!visible_) continue;

		if ((*child)->GetRect().Contain(x, y))
		{
			(*child)->MousePressed(x, y, root);

			if ((*child)->mouse_pressed_)
			{
				auto handled = (*child)->mouse_pressed_(root);
				if (handled) break;
			}
		}
	}
}

void WidgetContainer::MouseReleased(float x, float y, WidgetContainer * root)
{
	for (auto child = children_.rbegin(); child != children_.rend(); ++child)
	{
		if (!visible_) continue;

		if ((*child)->GetRect().Contain(x, y))
		{
			(*child)->MouseReleased(x, y, root);

			if ((*child)->mouse_released_)
			{
				auto handled = (*child)->mouse_released_(root);
				if (handled) break;
			}
		}
	}
}

void WidgetContainer::MouseMoved(float x, float y, WidgetContainer * root)
{
	for (auto child = children_.rbegin(); child != children_.rend(); ++child)
	{
		if (!visible_) continue;

		bool enter_handled = false;
		bool leave_handled = false;

		(*child)->MouseMoved(x, y, root);

		if ((*child)->GetRect().Contain(x, y))
		{
			if (!(*child)->hovered_)
			{
				(*child)->MouseEnter(x, y, root);
				(*child)->hovered_ = true;

				if ((*child)->mouse_enter_)
				{
					enter_handled = (*child)->mouse_enter_(root);
					if (enter_handled) break;
				}
			}
		}
		else
		{
			if ((*child)->hovered_)
			{
				(*child)->MouseLeave(x, y, root);
				(*child)->hovered_ = false;

				if ((*child)->mouse_leave_)
				{
					leave_handled = (*child)->mouse_leave_(root);
					if (leave_handled) break;
				}
			}
		}
	}
}

void WidgetContainer::Sort() 
{
	std::sort(children_.begin(), children_.end(), [](const auto& l, const auto& r) { return (*l).order_ < (*r).order_; });
	
	indexes_.clear();

	for (size_t i = 0; i < children_.size(); ++i) {
		indexes_[children_[i]->id_] = i;
	}
}
