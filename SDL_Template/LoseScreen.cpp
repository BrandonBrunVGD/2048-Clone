#include "LoseScreen.h"

LoseScreen::LoseScreen(std::string text, int score, std::string highscore) {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	mScore = score;
	mHighScore = highscore;

	mBackground = new GLTexture("WinLoseBackground.png");
	mBackground->Parent(this);
	mBackground->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);

	mGameOverText = new GLTexture(text, "GWIBBLE_.ttf", 32, { 255, 255, 255 });
	mGameOverText->Parent(this);
	mGameOverText->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.25f);
	mGameOverText->Scale(Vector2(3, 3));

	mScoreText = new GLTexture("SCORE: ", "GWIBBLE_.ttf", 32, { 255, 255, 255 });
	mScoreText->Parent(this);
	mScoreText->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.35f);
	mScoreText->Scale(Vector2(2.5, 2.5));

	mHighScoreText = new GLTexture("HIGH SCORE: ", "GWIBBLE_.ttf", 32, { 255, 255, 255 });
	mHighScoreText->Parent(this);
	mHighScoreText->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);
	mHighScoreText->Scale(Vector2(2.5, 2.5));

	mScoreNum = new GLTexture(std::to_string(mScore), "GWIBBLE_.ttf", 32, { 255, 255, 255 });
	mScoreNum->Parent(this);
	mScoreNum->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.4f);
	mScoreNum->Scale(Vector2(2.5, 2.5));

	mHighScoreNum = new GLTexture(mHighScore, "GWIBBLE_.ttf", 32, { 255, 255, 255 });
	mHighScoreNum->Parent(this);
	mHighScoreNum->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.55f);
	mHighScoreNum->Scale(Vector2(2.5, 2.5));

	mEnter = new GLTexture("ENTER", "GWIBBLE_.ttf", 32, { 255, 255, 255 });
	mEnter->Parent(this);
	mEnter->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.7f);
	mEnter->Scale(Vector2(3, 3));

	mStartBlink = 1;
	mBlinkTimer = 30;
}

LoseScreen::~LoseScreen() {
	delete mBackground;
	mBackground = nullptr;

	delete mGameOverText;
	mGameOverText = nullptr;

	delete mScoreText;
	mScoreText = nullptr;

	delete mHighScoreText;
	mHighScoreText = nullptr;

	delete mScoreNum;
	mScoreNum = nullptr;
	
	delete mHighScoreNum;
	mHighScoreNum = nullptr;

	delete mEnter;
	mEnter = nullptr;
}

void LoseScreen::Update() {
	mBackground->Update();
	mGameOverText->Update();
	mScoreText->Update();
	mHighScoreText->Update();
	mScoreNum->Update();
	mHighScoreNum->Update();
	mEnter->Update();
}

void LoseScreen::Render() {
	mBackground->Render();
	mGameOverText->Render();
	mScoreText->Render();
	mHighScoreText->Render();
	mScoreNum->Render();
	mHighScoreNum->Render();

	switch (mStartBlink) {
	case 1:
		mBlinkTimer -= 1 * mTimer->DeltaTime();
		if (mBlinkTimer <= 0) { mBlinkTimer = 30; mStartBlink = 2; }
		mEnter->Render();
		break;
	case 2:
		mBlinkTimer -= 1 * mTimer->DeltaTime();
		if (mBlinkTimer <= 0) { mBlinkTimer = 30; mStartBlink = 1; }
		break;
	}
}