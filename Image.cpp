#include<DxLib.h>

int Title_img;
int PlayerShot01_img;
int PlayerShot02_img;
int EnemyShot01_img;
int player_img;
int gameFrame_img;

void ImageInit(void)// ‰æ‘œ‚Ì‰Šú‰»
{
	Title_img = LoadGraph("image/title.png");
	PlayerShot01_img = LoadGraph("image/PlayerShot.png");
	PlayerShot02_img = LoadGraph("image/PlayerShot2.png");
	EnemyShot01_img = LoadGraph("image/EnemyShot01.png");
	player_img = LoadGraph("image/player.png");
	gameFrame_img = LoadGraph("image/gameFrame.png");
}