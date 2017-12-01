#include "app.hpp"

#include <functional>

#include "hge.h"
#include "hgesprite.h"
#include "hgefont.h"

App* g_app = nullptr;
bool g_need_shutdown = false;

bool FrameFunc()
{
	if (g_need_shutdown) return true;

	//update
	g_app->Update(g_app->Hge->Timer_GetDelta());

	//dispatch events
	float x = 0.0f, y = 0.0f;
	static float old_x = 0.0f, old_y = 0.0f;
	static bool pressed = false;

	g_app->Hge->Input_GetMousePos(&x, &y);

	if (g_app->Hge->Input_GetKeyState(HGEK_LBUTTON))
	{
		if (!pressed)
		{
			pressed = true;
			g_app->MousePressed(x, y);
		}
	}
	else
	{
		if (pressed)
		{
			pressed = false;
			g_app->MouseReleased(x, y);
		}
	}

	if (old_x != x || old_y != y) g_app->MouseMoved(x, y);

	old_x = x;
	old_y = y;

	return false;
}

App::App(std::string title, int width, int height)
{
	title_ = title;
	width_ = width;
	height_ = height;

	Hge = hgeCreate(HGE_VERSION);

	g_app = this;

	Hge->System_SetState(HGE_LOGFILE, "widgets.log");
	Hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	Hge->System_SetState(HGE_RENDERFUNC, []() {g_app->Render(); return false; });
	Hge->System_SetState(HGE_TITLE, g_app->GetTitle().c_str());
	Hge->System_SetState(HGE_FPS, 60);
	Hge->System_SetState(HGE_WINDOWED, true);
	Hge->System_SetState(HGE_SCREENWIDTH, g_app->GetWidth());
	Hge->System_SetState(HGE_SCREENHEIGHT, g_app->GetHeight());
	Hge->System_SetState(HGE_SCREENBPP, 32);
	Hge->System_SetState(HGE_HIDEMOUSE, false);
}

std::string App::GetTitle()
{
	return title_;
}

int App::GetWidth()
{
	return width_;
}

int App::GetHeight()
{
	return height_;
}

void App::Shutdown()
{
	g_need_shutdown = true;
}

void exec(App* app)
{
	if (g_app->Hge->System_Initiate() && g_app->Init())
		g_app->Hge->System_Start();

	g_app->Done();

	g_app->Hge->System_Shutdown();
	g_app->Hge->Release();
}
