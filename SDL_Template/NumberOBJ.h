#ifndef __NUMBEROBJ_H
#define __NUMBEROBJ_H
#include "AnimatedGLTexture.h"
#include "Timer.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "GameEntity.h"

using namespace SDLFramework;

class NumberOBJ : public GameEntity {
private:
	Timer* mTimer;
	AudioManager* mAudio;
	InputManager* mInput;

	Texture* mNumBox;
	Texture* mNumText;

	AnimatedGLTexture* mTestAnim;

	int mSocketNum;
	int mLastNum;

	int mNumValue;
	std::string mNumString;

public:
	NumberOBJ(int num);
	~NumberOBJ();

	void OnSpawn();
	void InitTexture();

	void SetSocketNum(int num) { mSocketNum = num; }
	void SetLastNum(int num) { mLastNum = num; }
	void SetNumValue(int num) { mNumValue = num; }

	int GetSocketNum() { return mSocketNum; }
	int GetLastNum() { return mLastNum; }
	int GetNumValue() { return mNumValue; }

	void Update() override;
	void Render() override;
};
#endif
