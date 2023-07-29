#include "NumberOBJ.h"

NumberOBJ::NumberOBJ(int num) {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();
	mInput = InputManager::Instance();

	

	mNumValue = num;
	mNumString = std::to_string(mNumValue);
	mLastNum = mNumValue;

	InitTexture();

	mNumText = new GLTexture(mNumString, "GWIBBLE_.ttf", 32, { 0, 128, 128 });
	mNumText->Parent(mNumBox);
	mNumText->Position(Vec2_Zero);
	mNumText->Scale(Vector2(4, 4));

	mShadow = new GLTexture("Shadow.png");
	mShadow->Parent(this);
	mShadow->Position(Vector2(0, 28));
	mShadow->Scale(Vector2(0.05, 0.05));
}

NumberOBJ::~NumberOBJ() {
	mTimer = nullptr;
	mAudio = nullptr;

	delete mNumBox;
	mNumBox = nullptr;

	delete mNumText;
	mNumText = nullptr;

	delete mShadow;
	mShadow = nullptr;
}

void NumberOBJ::Update() {
	OnSpawn();
	mNumBox->Update();
	mNumText->Update();
	mShadow->Update();
}

void NumberOBJ::Render() {
	mShadow->Render();
	mNumBox->Render();
	mNumText->Render();
}

void NumberOBJ::OnSpawn() {
	if (mNumBox->Scale().x >= 0.4 && mNumBox->Scale().y >= 0.4) {
		mNumBox->Scale(Vector2(0.4, 0.4));
		mShadow->Scale(Vector2(0.4, 0.4));
	} 
	else {
		mNumBox->Scale(Vector2(mNumBox->Scale().x + 0.05, mNumBox->Scale().y + 0.05));
		mShadow->Scale(Vector2(mShadow->Scale().x + 0.05, mShadow->Scale().y + 0.05));
	}
}

void NumberOBJ::InitTexture() {
	if (mNumValue == 2) { mNumBox = new GLTexture("Dog.png"); }
	else if (mNumValue == 4) { mNumBox = new GLTexture("Frog.png"); }
	else if (mNumValue == 8) { mNumBox = new GLTexture("Duck.png"); }
	else if (mNumValue == 16) { mNumBox = new GLTexture("Bunny.png"); }
	else if (mNumValue == 32) { mNumBox = new GLTexture("Penguin.png"); }
	else if (mNumValue == 64) { mNumBox = new GLTexture("Piggy.png"); }
	else if (mNumValue == 128) { mNumBox = new GLTexture("Cow.png"); }
	else if (mNumValue == 256) { mNumBox = new GLTexture("Panda.png"); }
	else if (mNumValue == 512) { mNumBox = new GLTexture("Zebra.png"); }
	else if (mNumValue == 1024) { mNumBox = new GLTexture("Lion.png"); }
	else if (mNumValue == 2048) { mNumBox = new GLTexture("Snake.png"); }
	else { mNumBox = new GLTexture("Dog.png"); }
	mNumBox->Parent(this);
	mNumBox->Position(Vec2_Zero);
	mNumBox->Scale(Vector2(0.05, 0.05));
}