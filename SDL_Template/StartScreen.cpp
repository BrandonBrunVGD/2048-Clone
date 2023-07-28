#include "StartScreen.h"

StartScreen::StartScreen() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	mBackground = new GLTexture("StartScreenBackground.png");
	mBackground->Parent(this);
	mBackground->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);
	
	mEnterToStart = new GLTexture("EnterToStart.png");
	mEnterToStart->Parent(mBackground);
	mEnterToStart->Position(Vector2(0, 300));

	mStartBlink = 1;
	mBlinkTimer = 45;
}

StartScreen::~StartScreen() {
	delete mBackground;
	mBackground = nullptr;

	delete mEnterToStart;
	mEnterToStart = nullptr;
}

void StartScreen::Update() {
	mBackground->Update();
	mEnterToStart->Update();
}

void StartScreen::Render() {
	mBackground->Render();
	//mEnterToStart->Render();

	switch (mStartBlink) {
	case 1:
		mBlinkTimer -= 1 * mTimer->DeltaTime();
		if (mBlinkTimer <= 0) { mBlinkTimer = 45; mStartBlink = 2; }
		mEnterToStart->Render();
		break;
	case 2:
		mBlinkTimer -= 1 * mTimer->DeltaTime();
		if (mBlinkTimer <= 0) { mBlinkTimer = 45; mStartBlink = 1; }
		break;
	}
}