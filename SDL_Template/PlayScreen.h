#ifndef __PLAYSCREEN_H
#define __PLAYSCREEN_H
#include "Timer.h"
#include "AudioManager.h"
#include "NumberOBJ.h"
#include "Sockets.h"
#include <algorithm>

class PlayScreen : public GameEntity {
private:
	Timer* mTimer;
	AudioManager* mAudio;
	InputManager* mInput;


	Vector2 mCurrentSocket;
	bool mCanMove;

	static const int ROW_SIZE = 4;
	std::vector<std::vector<int>> mBoard{ ROW_SIZE, std::vector<int>(ROW_SIZE, 0) };

	Socket* mSockets[ROW_SIZE][ROW_SIZE];
	NumberOBJ* mNumbers[ROW_SIZE][ROW_SIZE];

	bool mGameOver;

public:
	PlayScreen();
	~PlayScreen();

	void Controls();

	void InitSockets();
	void RanNumSpawn();

	void MoveNumbs(std::vector<int>& row);
	void CombineNumbs(std::vector<int>& row);
	void displayBoard();

	void MoveRight(std::vector<int>& row);
	void MoveLeft(std::vector<int>& row);

	void Update() override;
	void Render() override;
};
#endif

