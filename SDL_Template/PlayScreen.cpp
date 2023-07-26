#include "PlayScreen.h"
#include <iomanip>
#include <cstdlib>



PlayScreen::PlayScreen() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();
	mInput = InputManager::Instance();

	mCanMove = false;
	mGameOver = false;

	InitSockets();
	
	RanNumSpawn();
}

PlayScreen::~PlayScreen() {
	mTimer = nullptr;
	mAudio = nullptr;

	for (auto b : mNumbers) {
		delete b;
	}

	for (auto b : mSockets) {
		delete b;
	}
}

void PlayScreen::Update() {
	displayBoard();

	for (int i = 0; i < ROW_SIZE; ++i) {
		for (int j = 0; j < ROW_SIZE; ++j) {
			if (mNumbers[i][j] != nullptr) {
				mNumbers[i][j]->Update();
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
				std::cout << "SPAWNED NUMBER" << std::endl;
			}
			else if (mNumbers[j][i] != nullptr) {
				if (mBoard[j][i] != mNumbers[j][i]->GetLastNum()) {
					delete mNumbers[j][i];
					mNumbers[j][i] = nullptr;
					std::cout << "DELETED NUMBER - TO BE REPLACED" << std::endl;
					mNumbers[j][i] = new NumberOBJ(mBoard[j][i]);
					mNumbers[j][i]->Parent(this);
					mNumbers[j][i]->Position(mSockets[i][j]->Position());
					std::cout << "REPLACING NUMBER" << std::endl;
				}
			}
			if (mBoard[j][i] == 0 && mSockets[i][j]->GetFull() == true){
				delete mNumbers[j][i];
				mNumbers[j][i] = nullptr;
				mSockets[i][j]->SetFull(false);
				std::cout << "DELETED NUMBER" << std::endl;
			}
		}
	}	
}

void PlayScreen::Render() {

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
}

void PlayScreen::InitSockets() {
	for (int i = 0; i < ROW_SIZE; ++i) {
		for (int j = 0; j < ROW_SIZE; ++j) {
			mSockets[i][j] = new Socket();
			mSockets[i][j]->Parent(this);
			mSockets[i][j]->Scale(Vector2(0.5f, 0.5f));
			mSockets[i][j]->SetSocketNum(i*j);
		}
	}
	//Position Sockets
	for (int i = 0; i < 4; ++i) {
		mSockets[i][0]->Position(600.0f + (200 * (i % 4)), 200.0f);
	}
	for (int i = 0; i < 4; ++i) {
		mSockets[i][1]->Position(600.0f + (200 * (i % 4)), 200.0f + (185 * 1));
	}
	for (int i = 0; i < 4; ++i) {
		mSockets[i][2]->Position(600.0f + (200 * (i % 4)), 200.0f + (185 * 2));
	}
	for (int i = 0; i < 4; ++i) {
		mSockets[i][3]->Position(600.0f + (200 * (i % 4)), 200.0f + (185 * 3));
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
	}
	else if (mInput->KeyPressed(SDL_SCANCODE_A)) {
		for (int i = 0; i < ROW_SIZE; ++i) {
			MoveLeft(mBoard[i]);
			CombineNumbs(mBoard[i]);
			MoveLeft(mBoard[i]);
		}
		RanNumSpawn();
	}
	else if (mInput->KeyPressed(SDL_SCANCODE_D)) {
		for (int i = 0; i < ROW_SIZE; ++i) {
			MoveRight(mBoard[i]);
			CombineNumbs(mBoard[i]);
			MoveRight(mBoard[i]);
		}
		RanNumSpawn();
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
