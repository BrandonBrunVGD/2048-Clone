#ifndef __STARTSCREEN_H
#define __STARTSCREEN_H
#include "AnimatedGLTexture.h"
#include "InputManager.h"
#include "Scoreboard.h"

using namespace SDLFramework;

class StartScreen : public GameEntity {

private:
	Timer* mTimer;
	InputManager* mInput;

	Texture* mBackground;
	Texture* mEnterToStart;

	int mStartBlink;
	int mBlinkTimer;

public:
	StartScreen();
	~StartScreen();

	void Update() override;
	void Render() override;
};
#endif