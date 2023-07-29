#ifndef __SCREENMANAGER_H
#define __SCREENMANAGER_H
#include "StartScreen.h"
#include "PlayScreen.h"
#include "LoseScreen.h"

class ScreenManager {
private:
	static ScreenManager * sInstance;

	enum Screens { Start, Play, Won, Over };
	Screens mCurrentScreen;

	InputManager * mInput;

	StartScreen * mStartScreen;
	PlayScreen * mPlayScreen;
	LoseScreen* mLoseScreen;

	bool mStartLock;
	bool mPlayLock;
	bool mWinLock;
	bool mLoseLock;

public:
	static ScreenManager * Instance();
	static void Release();

	void CreateStartScreen();
	void CreatePlayScreen();
	void CreateLoseScreen(std::string text, int score, std::string highscore);

	void Update();
	void Render();

private:
	ScreenManager();
	~ScreenManager();
};
#endif