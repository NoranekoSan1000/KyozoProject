#include<DxLib.h>

int Title_img;
int DifficultyLv_img[4];
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
	DifficultyLv_img[0] = LoadGraph("image/easy.png");
	DifficultyLv_img[1] = LoadGraph("image/normal.png");
	DifficultyLv_img[2] = LoadGraph("image/hard.png");
	DifficultyLv_img[3] = LoadGraph("image/helldiva.png");

	NumberText_img[0] = LoadGraph("image/Number/0.png");
	NumberText_img[1] = LoadGraph("image/Number/1.png");
	NumberText_img[2] = LoadGraph("image/Number/2.png");
	NumberText_img[3] = LoadGraph("image/Number/3.png");
	NumberText_img[4] = LoadGraph("image/Number/4.png");
	NumberText_img[5] = LoadGraph("image/Number/5.png");
	NumberText_img[6] = LoadGraph("image/Number/6.png");
	NumberText_img[7] = LoadGraph("image/Number/7.png");
	NumberText_img[8] = LoadGraph("image/Number/8.png");
	NumberText_img[9] = LoadGraph("image/Number/9.png");

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