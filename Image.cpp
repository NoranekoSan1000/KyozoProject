#include<DxLib.h>

int shot_img;
int player_img;
int gameFrame_img;

void ImageInit(void)// �摜�̏�����
{
	shot_img = LoadGraph("image/shot.png");
	player_img = LoadGraph("image/player.png");
	gameFrame_img = LoadGraph("image/gameFrame.png");
}