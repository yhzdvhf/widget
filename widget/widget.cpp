#include "widget.hpp"
#include "widget_container.hpp"

Widget::Widget(const std::string & id, size_t order, WidgetContainer * parent)
	: id_(id), order_(order), parent_(parent) {}

void Widget::SetOrder(int order, bool sort) {
	order_ = order;

	if (sort && parent_)
		parent_->Sort();// will be called automatically at the end of Gui::Apply()
}

int Widget::GetOrder() const {
	return order_;
}

void Widget::OnMousePressed(MouseCallback callback) {
	mouse_pressed_ = callback;
}

void Widget::OnMouseReleased(MouseCallback callback) {
	mouse_released_ = callback;
}

void Widget::OnMouseEnter(MouseCallback callback) {
	mouse_enter_ = callback;
}

void Widget::OnMouseLeave(MouseCallback callback) {
	mouse_leave_ = callback;
}

Rect Widget::GetRect() const {
	return rect_;
}

void Widget::SetPos(float x, float y) {
	rect_.x = x;
	rect_.y = y;

	if (parent_) parent_->UpdateRect();
}

void Widget::SetSize(float w, float h) {
	rect_.w = w;
	rect_.h = h;

	if (parent_) parent_->UpdateRect();
}

void Widget::Show() { visible_ = true; }

void Widget::Hide() { visible_ = false; }

bool Widget::IsVisible() const { return visible_; }
