#ifndef __LOSESCREEN_H
#define __LOSESCREEN_H
#include "AnimatedGLTexture.h"
#include "InputManager.h"
#include "Scoreboard.h"

using namespace SDLFramework;

class LoseScreen : public GameEntity {

private:
	Timer* mTimer;
	InputManager* mInput;

	Texture* mBackground;
	std::string mText;
	Texture* mGameOverText;
	Texture* mScoreText;
	Texture* mHighScoreText;
	Texture* mScoreNum;
	Texture* mHighScoreNum;
	Texture* mEnter;

	int mScore;
	std::string mHighScore;

	int mStartBlink;
	int mBlinkTimer;

public:
	LoseScreen(std::string text, int score, std::string highscore);
	~LoseScreen();

	void SetHighScore(std::string score) { mHighScore = score; }

	void Update() override;
	void Render() override;
};
#endif
