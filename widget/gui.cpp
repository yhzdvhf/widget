#include "gui.hpp"

Gui::Gui() :root("Root", 0) {}

void Gui::Apply(std::function<void(WidgetContainer*)> callback)
{
	callback(&root);
	root.Sort();
}

void Gui::MouseMoved(float x, float y)
{
	root.MouseMoved(x, y, &root);
}

void Gui::MousePressed(float x, float y)
{
	root.MousePressed(x, y, &root);
}

void Gui::MouseReleased(float x, float y)
{
	root.MouseReleased(x, y, &root);
}

void Gui::Render()
{
	root.Render();
}
