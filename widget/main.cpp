#include <iostream>

#include "hge.h"
#include "hgesprite.h"
#include "hgefont.h"

#include "app.hpp"
#include "gui.hpp"
#include "image.hpp"
#include "button.hpp"

class Game : public App
{
	hgeFont*   fnt;
	HTEXTURE   tex_img, tex_btn;

	Gui gui;
public:
	Game(std::string title, int width, int height):App(title, width, height){}

	bool Init() override
	{
		fnt = new hgeFont("../assets/font1.fnt");
		tex_img = Hge->Texture_Load("../assets/Lena.jpg");
		tex_btn = Hge->Texture_Load("../assets/Button.png");

		gui.Apply([&](WidgetContainer* root) 
		{
			auto img = root->AddWidget<Image>("Image_1", 0);
			img->SetTexture(tex_img, 0, 0, 512, 512);
			img->SetPos(128, 128);
			img->SetSize(128, 128);
			img->OnMouseEnter([](WidgetContainer* root) {
				auto w = root->GetWidget("Image_2");
				w->Show();
				return true;
			});
			img->OnMouseLeave([](WidgetContainer* root) {
				root->GetWidget("Image_2")->Hide();
				return true;
			});

			img = root->AddWidget<Image>("Image_2", 1);
			img->SetTexture(tex_img, 0, 0, 512, 512);
			img->SetPos(256, 128);
			img->SetSize(128, 128);
			img->Hide();

			auto btn = root->AddWidget<Button>("Button", 2);
			btn->SetPressedTexture(tex_btn, 0, 0, 512, 64);
			btn->SetHoveredTexture(tex_btn, 0, 64, 512, 64);
			btn->SetTexture(tex_btn, 0, 128, 512, 64);
			btn->SetPos(128, 256);
			btn->SetSize(256, 64);
			btn->OnMousePressed([](WidgetContainer* root) {
				auto widget = root->GetWidget("Group");
				
				if (widget->IsVisible()) widget->Hide();
				else widget->Show();

				return true;
			});

			auto group = root->AddWidget<WidgetContainer>("Group", 1);
			group->Hide();
			img = group->AddWidget<Image>("Group.Image", 0);
			img->SetTexture(tex_img, 0, 0, 512, 512);
			img->SetPos(384, 128);
			img->SetSize(192, 192);
			
			btn = group->AddWidget<Button>("Group.Button", 1);
			btn->SetPressedTexture(tex_btn, 0, 0, 512, 64);
			btn->SetHoveredTexture(tex_btn, 0, 64, 512, 64);
			btn->SetTexture(tex_btn, 0, 128, 512, 64);
			btn->SetPos(384, 256);
			btn->SetSize(256, 64);
			btn->OnMousePressed([self=btn](WidgetContainer* root) {
				auto grp = (WidgetContainer*)root->GetWidget("Group");
				auto img = grp->GetWidget("Group.Image");

				if (self->GetOrder() == 1) {
					self->SetOrder(0, false);
					img->SetOrder(1);
				}
				else {
					self->SetOrder(1, false);
					img->SetOrder(0);
				}

				return true;
			});
		});
		
		return true;
	}
	void Done() override
	{
		delete fnt;
		Hge->Texture_Free(tex_img);
		Hge->Texture_Free(tex_btn);
	}

	void Update(float dt) override{}
	void Render() override 
	{
		Hge->Gfx_BeginScene();
		Hge->Gfx_Clear(0);
		fnt->printf(5, 5, HGETEXT_LEFT, "dt:%.3f\nFPS:%d (constant)", Hge->Timer_GetDelta(), Hge->Timer_GetFPS());
		gui.Render();
		Hge->Gfx_EndScene();
	}

	void MouseMoved(float x, float y) override
	{
		gui.MouseMoved(x, y);
	}
	void MousePressed(float x, float y) override
	{
		gui.MousePressed(x, y);
	}
	void MouseReleased(float x, float y) override
	{
		gui.MouseReleased(x, y);
	}
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	std::unique_ptr<App> app = std::make_unique<Game>("Test widgets", 800, 600);
	exec(app.get());
}
