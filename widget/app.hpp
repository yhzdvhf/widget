#pragma once

#include <memory>
#include <string>

#include "hge.h"

class App
{
	std::string title_;
	int width_;
	int height_;
public:
	App(std::string title, int width, int height);

	std::string GetTitle();

	int GetWidth();
	int GetHeight();

	void Shutdown();

	virtual bool Init() = 0;
	virtual void Done() = 0;

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

	virtual void MouseMoved(float x, float y) = 0;
	virtual void MousePressed(float x, float y) = 0;
	virtual void MouseReleased(float x, float y) = 0;
public:
	HGE* Hge = nullptr;
};

void exec(App* app);