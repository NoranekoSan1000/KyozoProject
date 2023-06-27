#include<DxLib.h>

int Title_img;
int DifficultyLv_img[4];

int easy_text_img;
int normal_text_img;
int hard_text_img;
int helldiva_text_img;		//enum Difficulty‚ğ—p‚¢‚é
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

void ImageInit(void)// ‰æ‘œ‚Ì‰Šú‰»
{
	DifficultyLv_img[0] = LoadGraph("image/easy.png");
	DifficultyLv_img[1] = LoadGraph("image/normal.png");
	DifficultyLv_img[2] = LoadGraph("image/hard.png");
	DifficultyLv_img[3] = LoadGraph("image/helldiva.png");

	easy_text_img = LoadGraph("image/easy_text.png");
	normal_text_img = LoadGraph("image/normal_text.png");
	hard_text_img = LoadGraph("image/hard_text.png");
	helldiva_text_img = LoadGraph("image/helldiva_text.png");
	score_img = LoadGraph("image/score.png");
	for (int i = 0; i < 10; i++) 
	{
		char fileName[30]; // “K“–‚È’·‚³‚Ì•¶š—ñ
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