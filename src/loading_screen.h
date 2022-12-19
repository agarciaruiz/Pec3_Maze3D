#ifndef LOADING_SCREEN_H
#define LOADING_SCREEN_H
#include "screen.hpp"

class LoadingScreen : public Screen 
{
private:
public:
	void LoadingScreen::Init() override;
	void LoadingScreen::Update() override;
	void LoadingScreen::Draw() override;
	void LoadingScreen::Unload();
};

#endif // !LOADING_SCREEN_H
