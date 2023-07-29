#include "ScreenManager.h"
#include <fstream>

ScreenManager * ScreenManager::sInstance = nullptr;

ScreenManager * ScreenManager::Instance() {
	if (sInstance == nullptr) {
		sInstance = new ScreenManager();
	}

	return sInstance;
}

void ScreenManager::Release() {
	delete sInstance;
	sInstance = nullptr;
}

void ScreenManager::Update() {

	switch (mCurrentScreen) {
	case Start:
		CreateStartScreen();

		mStartScreen->Update();
		
		if (mInput->KeyPressed(SDL_SCANCODE_RETURN)) {	
			
			delete mStartScreen;
			mStartScreen = nullptr;

			mPlayLock = false;
			mCurrentScreen = Play;
		
		}
		break;
	case Play:
		CreatePlayScreen();
		mPlayScreen->Update();
	
		if (mPlayScreen->GetGameOver() == true) {	
			CreateLoseScreen("Game Over!", mPlayScreen->GetScore(), mPlayScreen->GetHighScore());
			mLoseScreen->Update();

			if (mInput->KeyPressed(SDL_SCANCODE_RETURN)) {
				
				delete mPlayScreen;
				mPlayScreen = nullptr;

				delete mLoseScreen;
				mLoseScreen = nullptr;

				mLoseLock = false;
				mStartLock = false;
				mCurrentScreen = Start;
			}
		}
		else if (mPlayScreen->GetGameWon() == true) {	
			CreateLoseScreen("You Win!", mPlayScreen->GetScore(), mPlayScreen->GetHighScore());
			mLoseScreen->Update();

			if (mInput->KeyPressed(SDL_SCANCODE_RETURN)) {

				delete mPlayScreen;
				mPlayScreen = nullptr;

				delete mLoseScreen;
				mLoseScreen = nullptr;

				mLoseLock = false;
				mStartLock = false;
				mCurrentScreen = Start;
			}
		}
		break;
	}
}

void ScreenManager::Render() { 


	switch (mCurrentScreen) {
	case Start:
		if (mStartScreen != nullptr) {
			mStartScreen->Render();
		}
		break;
	case Play:
		if (mPlayScreen != nullptr) {
			mPlayScreen->Render();
		
			if (mPlayScreen->GetGameOver() == true || mPlayScreen->GetGameWon() == true) {
				mLoseScreen->Render();
			}
		}
		break;
	}
}

ScreenManager::ScreenManager() {

	mInput = InputManager::Instance();

	mStartLock = false;
	mPlayLock = false;
	mWinLock = false;
	mLoseLock = false;

	mCurrentScreen = Start;
}

ScreenManager::~ScreenManager() {
	mInput = nullptr;

	delete mStartScreen;
	mStartScreen = nullptr;

	delete mPlayScreen;
	mPlayScreen = nullptr;

	delete mLoseScreen;
	mLoseScreen = nullptr;
}

void ScreenManager::CreateStartScreen() {
	if (!mStartLock) {
		mStartScreen = new StartScreen(); 
		mStartLock = true;
		//std::cout << "CREATED START SCREEN" << std::endl;
	}
}

void ScreenManager::CreatePlayScreen() {
	if (!mPlayLock) {		
		mPlayScreen = new PlayScreen(); 
		mPlayLock = true;
		//std::cout << "CREATED PLAY SCREEN" << std::endl;
	}
}

void ScreenManager::CreateLoseScreen(std::string text, int score, std::string highscore) {
	if (!mLoseLock) {	
		mLoseScreen = new LoseScreen(text, score, highscore); 
		mLoseLock = true;
		//std::cout << "CREATED LOSE SCREEN" << std::endl;
	}
}