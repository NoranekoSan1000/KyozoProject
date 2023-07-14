#include "GameData.h"

//Title , DifficultySelect
int Title_img;
int DifficultyLv_img[4];
int DifficultyText_img[4];

//StatusViewer
int score_img;
int Life_img;
int Bomb_img;
int LifeText_img;
int BombText_img;
int LevelText_img;
int PowerText_img;
int NumberText_img[10];
int slash_img;
int gameFrame_img;

//BackGround
int StageTitle_img[5];
int background_img[6];

int power_img;
int PlayerShot01_img;
int PlayerShot02_img;
int EnemyShot_img[15];
int Enemy_img[2];
int player_img[3];
int orivia_img[3];

int BombEff_img[3];

void ImageInit(void)// 画像の初期化
{
	Title_img = LoadGraph("image/title.png");
	DifficultyLv_img[Easy] = LoadGraph("image/easy.png");
	DifficultyLv_img[Normal] = LoadGraph("image/normal.png");
	DifficultyLv_img[Hard] = LoadGraph("image/hard.png");
	DifficultyLv_img[HellDiva] = LoadGraph("image/helldiva.png");

	DifficultyText_img[Easy] = LoadGraph("image/easy_text.png");
	DifficultyText_img[Normal] = LoadGraph("image/normal_text.png");
	DifficultyText_img[Hard] = LoadGraph("image/hard_text.png");
	DifficultyText_img[HellDiva] = LoadGraph("image/helldiva_text.png");

	LifeText_img = LoadGraph("image/LifeText.png");
	BombText_img = LoadGraph("image/BombText.png");
	Life_img = LoadGraph("image/life.png");
	Bomb_img = LoadGraph("image/bomb.png");
	LevelText_img = LoadGraph("image/LevelText.png");
	PowerText_img = LoadGraph("image/PowerText.png");
	score_img = LoadGraph("image/score.png");
	for (int i = 0; i < 10; i++) 
	{
		char fileName[30]; // 適当な長さの文字列
		sprintf_s(fileName, "image/Number/%d.png", i);
		NumberText_img[i] = LoadGraph(fileName);
	}
	slash_img = LoadGraph("image/Number/sl.png");
	gameFrame_img = LoadGraph("image/gameFrame.png");

	for (int i = 0; i < 5; i++)
	{
		char fileName[30]; // 適当な長さの文字列
		sprintf_s(fileName, "image/StageTitle%d.png", i+1);
		StageTitle_img[i] = LoadGraph(fileName);
	}
	
	for (int i = 0; i < 6; i++)
	{
		char fileName[30]; // 適当な長さの文字列
		sprintf_s(fileName, "image/BackGround/%d.png", i);
		background_img[i] = LoadGraph(fileName);
	}

	power_img = LoadGraph("image/power.png");
	PlayerShot01_img = LoadGraph("image/PlayerShot.png");
	PlayerShot02_img = LoadGraph("image/PlayerShot2.png");
	for (int i = 0; i < 15; i++)
	{
		char fileName[30]; // 適当な長さの文字列
		sprintf_s(fileName, "image/EnemyShot/%d.png", i);
		EnemyShot_img[i] = LoadGraph(fileName);
	}

	for (int i = 0; i < 2; i++)
	{
		char fileName[30]; // 適当な長さの文字列
		sprintf_s(fileName, "image/Enemy/%d.png", i);
		Enemy_img[i] = LoadGraph(fileName);
	}

	player_img[0] = LoadGraph("image/Player/0.png");
	player_img[1] = LoadGraph("image/Player/1.png");
	player_img[2] = LoadGraph("image/Player/2.png");
	orivia_img[0] = LoadGraph("image/Orivia/0.png");
	orivia_img[1] = LoadGraph("image/Orivia/1.png");
	orivia_img[2] = LoadGraph("image/Orivia/2.png");

	BombEff_img[0] = LoadGraph("image/Bomb1.png");
	BombEff_img[1] = LoadGraph("image/Bomb2.png");
	BombEff_img[2] = LoadGraph("image/Bomb3.png");
}