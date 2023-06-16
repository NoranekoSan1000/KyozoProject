#include<DxLib.h>

int shot_img;
int player_img;
int gameFrame_img;

void ImageInit(void)// ‰æ‘œ‚Ì‰Šú‰»
{
	shot_img = LoadGraph("image/shot.png");
	player_img = LoadGraph("image/player.png");
	gameFrame_img = LoadGraph("image/gameFrame.png");
}