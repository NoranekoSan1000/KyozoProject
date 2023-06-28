#include "GameData.h"

int Title_img;
int DifficultyLv_img[4];
int DifficultyText_img[4];

int score_img;
int NumberText_img[10];
int backgroundFront_img;
int backgroundBack_img;

int power_img;
int PlayerShot01_img;
int PlayerShot02_img;
int EnemyShot01_img;
int player_img;
int gameFrame_img;

void ImageInit(void)// âÊëúÇÃèâä˙âª
{
	DifficultyLv_img[Easy] = LoadGraph("image/easy.png");
	DifficultyLv_img[Normal] = LoadGraph("image/normal.png");
	DifficultyLv_img[Hard] = LoadGraph("image/hard.png");
	DifficultyLv_img[HellDiva] = LoadGraph("image/helldiva.png");

	DifficultyText_img[Easy] = LoadGraph("image/easy_text.png");
	DifficultyText_img[Normal] = LoadGraph("image/normal_text.png");
	DifficultyText_img[Hard] = LoadGraph("image/hard_text.png");
	DifficultyText_img[HellDiva] = LoadGraph("image/helldiva_text.png");

	score_img = LoadGraph("image/score.png");
	for (int i = 0; i < 10; i++) 
	{
		char fileName[30]; // ìKìñÇ»í∑Ç≥ÇÃï∂éöóÒ
		sprintf_s(fileName, "image/Number/%d.png", i);
		NumberText_img[i] = LoadGraph(fileName);
	}

	Title_img = LoadGraph("image/title.png");
	backgroundFront_img = LoadGraph("image/background.png");
	backgroundBack_img = LoadGraph("image/background_back.png");

	power_img = LoadGraph("image/power.png");
	PlayerShot01_img = LoadGraph("image/PlayerShot.png");
	PlayerShot02_img = LoadGraph("image/PlayerShot2.png");
	EnemyShot01_img = LoadGraph("image/EnemyShot01.png");
	player_img = LoadGraph("image/player.png");
	gameFrame_img = LoadGraph("image/gameFrame.png");
}