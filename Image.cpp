#include<DxLib.h>

int shot_img;
int player_img;
int status_img;

void ImageInit(void)// �摜�̏�����
{
	shot_img = LoadGraph("shot.png");
	player_img = LoadGraph("player.png");
	status_img = LoadGraph("status.png");
}