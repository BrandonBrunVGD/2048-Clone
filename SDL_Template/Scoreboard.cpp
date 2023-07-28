#include "Scoreboard.h"

Scoreboard::Scoreboard() 
	: Scoreboard({230, 230, 230}) {
}

Scoreboard::Scoreboard(SDL_Color color) {
	mColor = color;
	Score(0);
}

Scoreboard::~Scoreboard() {
	ClearBoard();
}

void Scoreboard::Score(int score) {
	ClearBoard();

	if (score == 0) {
		for (int i = 0; i < 1; i++) {
			mScore.push_back(new GLTexture("0", "gwibble/GWIBBLE_.ttf", 32, mColor));
			mScore[i]->Parent(this);
			mScore[i]->Position(Vector2(-32.0f * i, 0.0f));
			mScore[i]->Scale(Vector2(1.5, 1.5));
		}
	}
	else {
		std::string str = std::to_string(score);
		unsigned lastIndex = (unsigned)str.length() - 1;

		for (unsigned i = 0; i <= lastIndex; i++) {
			mScore.push_back(new GLTexture(str.substr(i, 1), "gwibble/GWIBBLE_.ttf", 32, mColor));
			mScore[i]->Parent(this);
			mScore[i]->Position(Vector2(-32.0f * (lastIndex - i), 0.0f));
			mScore[i]->Scale(Vector2(1.5, 1.5));
		}
	}
}

void Scoreboard::Render() {
	for (auto digit : mScore) {
		digit->Render();
	}
}

void Scoreboard::ClearBoard() {
	for (auto s : mScore) {
		delete s;
	}

	mScore.clear();
}
