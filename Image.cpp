#include<DxLib.h>

int PlayerShot_img;
int EnemyShot01_img;
int player_img;
int gameFrame_img;

void ImageInit(void)// ‰æ‘œ‚Ì‰Šú‰»
{
	PlayerShot_img = LoadGraph("image/PlayerShot.png");
	EnemyShot01_img = LoadGraph("image/EnemyShot01.png");
	player_img = LoadGraph("image/player.png");
	gameFrame_img = LoadGraph("image/gameFrame.png");
}