#include "PlayScreen.h"
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <thread>
#include <chrono>

PlayScreen::PlayScreen() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();
	mInput = InputManager::Instance();

	mScoreText = new GLTexture("SCORE: ", "gwibble/GWIBBLE_.ttf", 32, { 255, 255, 255 });
	mScoreText->Parent(this);
	mScoreText->Position(Vector2(350, 100));
	mScoreText->Scale(Vector2(1.5, 1.5));

	mHighScoreText = new GLTexture("HIGH SCORE: ", "gwibble/GWIBBLE_.ttf", 32, { 255, 255, 255 });
	mHighScoreText->Parent(this);
	mHighScoreText->Position(Vector2(355, 170));
	mHighScoreText->Scale(Vector2(1.5, 1.5));

	std::fstream dataIn;
	dataIn.open("SaveData.txt", std::ios::in);
	if (dataIn.is_open()) {
		std::getline(dataIn, mHighScore);
		dataIn.close();
	}

	mHighScoreNum = new GLTexture(mHighScore, "gwibble/GWIBBLE_.ttf", 32, { 255, 255, 255 });
	mHighScoreNum->Parent(this);
	mHighScoreNum->Position(Vector2(355, 205));
	mHighScoreNum->Scale(Vector2(1.5, 1.5));

	mScoreBoard = new Scoreboard({255, 255, 255});
	mScoreBoard->Position(Vector2(400, 135));
	mScoreBoard->Score(0);
	mScore = 0;

	mCanMove = false;
	mGameOver = false;
	mGameWon = false;
	mMuteSwitch = -1;
	mMute = false;

	mMuteIcon = new GLTexture("Mute.png");
	mMuteIcon->Parent(this);
	mMuteIcon->Position(Vector2(1700, 880));
	mMuteIcon->Scale(Vector2(0.1, 0.1));

	mSoundIcon = new GLTexture("UnMute.png");
	mSoundIcon->Parent(this);
	mSoundIcon->Position(Vector2(1700, 880));
	mSoundIcon->Scale(Vector2(0.1, 0.1));

	mBackground = new GLTexture("PlayScreenBackground.png");
	mBackground->Parent(this);
	mBackground->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);

	mSand = new GLTexture("Sand.png");
	mSand->Parent(this);
	mSand->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.45f);

	InitSockets();
	
	RanNumSpawn();

	Mix_MasterVolume(50);
	Mix_VolumeMusic(30);
	mAudio->PlayMusic("MUS/Happy-Days.mp3", -1);

}

PlayScreen::~PlayScreen() {

	mTimer = nullptr;
	mAudio = nullptr;

	delete mScoreText;
	mScoreText = nullptr;

	delete mHighScoreText;
	mHighScoreText = nullptr;

	delete mHighScoreNum;
	mHighScoreNum = nullptr;

	delete mScoreBoard;
	mScoreBoard = nullptr;

	delete mBackground;
	mBackground = nullptr;

	delete mSand;
	mSand = nullptr;

	delete mMuteIcon;
	mMuteIcon = nullptr;

	delete mSoundIcon;
	mSoundIcon = nullptr;

	for (int i = 0; i < ROW_SIZE; ++i) {
		for (int j = 0; j < ROW_SIZE; ++j) {
			delete mNumbers[i][j];
			mNumbers[i][j] = nullptr;
		}
	}	

	for (int i = 0; i < ROW_SIZE; ++i) {
		for (int j = 0; j < ROW_SIZE; ++j) {
			delete mSockets[i][j];
			mSockets[i][j] = nullptr;
		}
	}

	mAudio->PauseMusic();
}

void PlayScreen::Update() {
	mScoreText->Update();
	mHighScoreText->Update();
	mHighScoreNum->Update();
	mScoreBoard->Update();
	mBackground->Update();
	mSand->Update();
	mMuteIcon->Update();
	mSoundIcon->Update();

	//displayBoard();

	for (int i = 0; i < ROW_SIZE; ++i) {
		for (int j = 0; j < ROW_SIZE; ++j) {
			if (mNumbers[i][j] != nullptr) {
				mNumbers[i][j]->Update();
				if (mBoard[i][j] == 2048) {
					mGameWon = true;
				}
			}

		}
	}

	for (int i = 0; i < ROW_SIZE; ++i) {
		for (int j = 0; j < ROW_SIZE; ++j) {
			mSockets[i][j]->Update();

		}
	}

	Controls();

	for (int i = 0; i < ROW_SIZE; ++i) {
		for (int j = 0; j < ROW_SIZE; ++j) {
			if (mBoard[j][i] != 0 && mSockets[i][j]->GetFull() == false){
				mNumbers[j][i] = new NumberOBJ(mBoard[j][i]);
				mNumbers[j][i]->Parent(this);
				mNumbers[j][i]->Position(mSockets[i][j]->Position());
				mSockets[i][j]->SetFull(true);
				//std::cout << "SPAWNED NUMBER" << std::endl;
				
			}
			else if (mNumbers[j][i] != nullptr) {
				if (mBoard[j][i] != mNumbers[j][i]->GetLastNum()) {
					delete mNumbers[j][i];
					mNumbers[j][i] = nullptr;
					
					//std::cout << "DELETED NUMBER - TO BE REPLACED" << std::endl;
					mNumbers[j][i] = new NumberOBJ(mBoard[j][i]);
					mNumbers[j][i]->Parent(this);
					mNumbers[j][i]->Position(mSockets[i][j]->Position());
					//std::cout << "REPLACING NUMBER" << std::endl;
					
				}
			}
			if (mBoard[j][i] == 0 && mSockets[i][j]->GetFull() == true){
				delete mNumbers[j][i];
				mNumbers[j][i] = nullptr;
				mSockets[i][j]->SetFull(false);
				//std::cout << "DELETED NUMBER" << std::endl;
			}
		}
	}	
	//std::cout << mScore << std::endl;
	if (mGameOver) { 
			
		//std::cout << "GAME OVER!!!!" << std::endl; 
	}	

	int HSint = stoi(mHighScore);
	if (HSint < mScore) {
		std::ofstream dataOut;
		dataOut.open("SaveData.txt", std::ios::out);
		if (dataOut.is_open()) {
			dataOut << mScore << " ";
			dataOut.close();
		}
	}
}

void PlayScreen::Render() {
	mBackground->Render();
	mSand->Render();

	for (int i = 0; i < ROW_SIZE; ++i) {
		for (int j = 0; j < ROW_SIZE; ++j) {
			if (mNumbers[i][j] != nullptr) {
				mNumbers[i][j]->Render();
			}
		}
	}

	for (int i = 0; i < ROW_SIZE; ++i) {
		for (int j = 0; j < ROW_SIZE; ++j) {
			mSockets[i][j]->Render();
			
		}
	}

	if (mMute) { mMuteIcon->Render(); }
	else { mSoundIcon->Render(); }
	mHighScoreText->Render();
	mHighScoreNum->Render();
	mScoreText->Render();
	mScoreBoard->Render();
}

void PlayScreen::InitSockets() {
	for (int i = 0; i < ROW_SIZE; ++i) {
		for (int j = 0; j < ROW_SIZE; ++j) {
			mSockets[i][j] = new Socket();
			mSockets[i][j]->Parent(this);
			mSockets[i][j]->Scale(Vector2(0.57f, 0.57f));
			mSockets[i][j]->SetSocketNum(i*j);
		}
	}
	//Position Sockets
	for (int i = 0; i < 4; ++i) {
		mSockets[i][0]->Position(650.0f + (205 * (i % 4)), 200.0f);
	}
	for (int i = 0; i < 4; ++i) {
		mSockets[i][1]->Position(650.0f + (205 * (i % 4)), 200.0f + (185 * 1));
	}
	for (int i = 0; i < 4; ++i) {
		mSockets[i][2]->Position(650.0f + (205 * (i % 4)), 200.0f + (185 * 2));
	}
	for (int i = 0; i < 4; ++i) {
		mSockets[i][3]->Position(650.0f + (205 * (i % 4)), 200.0f + (185 * 3));
	}
}

void PlayScreen::RanNumSpawn() {
	srand(time(NULL));
	std::vector<std::pair<int, int>> emptyNumbs;

	for (int i = 0; i < ROW_SIZE; ++i) {
		for (int j = 0; j < ROW_SIZE; ++j) {
			if (mBoard[i][j] == 0) {
				emptyNumbs.push_back({i,j});
			}
		}
	}

	if (emptyNumbs.empty()) {
		mGameOver = true;
		return;		
	}

	int randomPos = rand() % emptyNumbs.size();
	mBoard[emptyNumbs[randomPos].first][emptyNumbs[randomPos].second] = 2;
	mAudio->PlaySFX("SFX/Pop.wav");
}

void PlayScreen::Controls() {
	
	if (mInput->KeyPressed(SDL_SCANCODE_S)) {
		for (int j = 0; j < ROW_SIZE; ++j) {
			std::vector<int> col;
			for (int i = 0; i < ROW_SIZE; ++i) {
				col.push_back(mBoard[i][j]);
			}
			MoveNumbs(col);
			CombineNumbs(col);
			MoveNumbs(col);
			for (int i = 0; i < ROW_SIZE; ++i) {
				mBoard[i][j] = col[i];
			}
		}
		RanNumSpawn();
		AddScore(2);
		
	}
	else if (mInput->KeyPressed(SDL_SCANCODE_W)) {
		for (int j = 0; j < ROW_SIZE; ++j) {
			std::vector<int> col;
			for (int i = ROW_SIZE - 1; i >= 0; --i) {
				col.push_back(mBoard[i][j]);
			}
			MoveNumbs(col);
			CombineNumbs(col);
			MoveNumbs(col);
			for (int i = ROW_SIZE - 1; i >= 0; --i) {
				mBoard[i][j] = col[ROW_SIZE - 1 - i];
			}
		}
		RanNumSpawn();
		AddScore(2);
		
	}
	else if (mInput->KeyPressed(SDL_SCANCODE_A)) {
		for (int i = 0; i < ROW_SIZE; ++i) {
			MoveLeft(mBoard[i]);
			CombineNumbs(mBoard[i]);
			MoveLeft(mBoard[i]);
		}
		RanNumSpawn();
		AddScore(2);
		
	}
	else if (mInput->KeyPressed(SDL_SCANCODE_D)) {
		for (int i = 0; i < ROW_SIZE; ++i) {
			MoveRight(mBoard[i]);
			CombineNumbs(mBoard[i]);
			MoveRight(mBoard[i]);
		}
		RanNumSpawn();
		AddScore(2);
		
	}
	
	if (mInput->KeyPressed(SDL_SCANCODE_M)) {
		mMuteSwitch *= -1;
	}
	switch (mMuteSwitch) {
	case 1:
		mMute = true;
		Mix_VolumeMusic(0);
		break;
	case -1:
		mMute = false;
		Mix_VolumeMusic(30);
		break;
	}
}

void PlayScreen::MoveNumbs(std::vector<int>& row) {
	for (int i = ROW_SIZE - 1; i > 0; --i) {
		if (row[i] == 0) {
			for (int j = i - 1; j >= 0; --j) {
				if (row[j] != 0) {
					row[i] = row[j];
					row[j] = 0;
					break;
				}
			}
		}
	}
}

void PlayScreen::CombineNumbs(std::vector<int>& row) {
	for (int i = 0; i < ROW_SIZE - 1; ++i) {
		if (row[i] == row[i + 1]) {
			row[i] *= 2;
			row[i + 1] = 0;
			AddScore(row[i]);
		}
	}
}

void PlayScreen::displayBoard() {
	std::cout << "---------------------" << std::endl;
	for (int i = 0; i < ROW_SIZE; ++i) {
		for (int j = 0; j < ROW_SIZE; ++j) {
			if (mBoard[i][j] == 0)
				std::cout << std::setw(4) << ".";
			else
				std::cout << std::setw(4) << mBoard[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << "---------------------" << std::endl;
}

void PlayScreen::MoveLeft(std::vector<int>& row) {
	for (int i = 0; i < ROW_SIZE - 1; ++i) {
		if (row[i] == 0) {
			for (int j = i + 1; j < ROW_SIZE; ++j) {
				if (row[j] != 0) {
					row[i] = row[j];
					row[j] = 0;
					break;
				}
			}
		}
	}
}

void PlayScreen::MoveRight(std::vector<int>& row) {
	for (int i = ROW_SIZE - 1; i > 0; --i) {
		if (row[i] == 0) {
			for (int j = i - 1; j >= 0; --j) {
				if (row[j] != 0) {
					row[i] = row[j];
					row[j] = 0;
					break;
				}
			}
		}
	}
}

void PlayScreen::AddScore(int points) {
	mScore += points;
	mScoreBoard->Score(mScore);
}
