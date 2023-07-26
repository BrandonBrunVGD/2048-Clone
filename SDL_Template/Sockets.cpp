#include "Sockets.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

Socket::Socket() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mFull = false;

	mSocket = new GLTexture("ProfileSelector.png");
	mSocket->Parent(this);
	mSocket->Position(Vec2_Zero);
	//mSocket->Scale(Vector2(0.5f, 0.5f));

	Visible(true);
}

Socket::~Socket() {
	mTimer = nullptr;
	mInput = nullptr;
	mAudio = nullptr;

	delete mSocket;
	mSocket = nullptr;
}

void Socket::Visible(bool visible) {
	mVisible = visible;
}

void Socket::Update() {
	if (Active()) {
		mSocket->Update();	
	}
}

void Socket::Render() {
	mSocket->Render();

	PhysEntity::Render();
}

void Socket::Hit(PhysEntity* other) {
	
}