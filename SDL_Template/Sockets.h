#ifndef __SOCKETS_H
#define __SOCKETS_H
#include "AnimatedGLTexture.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "PhysEntity.h"

using namespace SDLFramework;

class Socket : public PhysEntity {
private:
	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	Texture* mSocket;


	bool mFull;

	int mSocketNum;

	bool mVisible;

private:

public:
	Socket();
	~Socket();

	void Visible(bool visible);

	// Inherited from PhysEntity

	void Hit(PhysEntity* other) override;
	bool WasHit();

	void Update() override;
	void Render() override;

	void SetSocketNum(int num) { mSocketNum = num; }
	void SetFull(bool full) { mFull = full; }

	int GetSocketNum() { return mSocketNum; }
	bool GetFull() { return mFull; }
};
#endif
