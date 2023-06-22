#include "GameData.h"
#define PLAYER_SIZE_X 12
#define PLAYER_SIZE_Y 24

//�v���C���[
int InitialPosX = 350;
int InitialPosY = 550;
int Player_HitBoxSize = 4;
int px = InitialPosX;
int py = InitialPosY;
int Score = 0;
int Life = 10;
float DamagedCoolTime = 0;

void PlayerMove(int* keyState)
{
	int MOVE_SPEED = 4;
	float slow = 1;
	

	if (keyState[KEY_INPUT_LSHIFT] > 0) slow = 0.5;
	else slow = 1;

	if (keyState[KEY_INPUT_RIGHT] > 0 && px < FRAME_WIDTH - PLAYER_SIZE_X) //�p������
	{
		px += (int)MOVE_SPEED * slow;
	}
	if (keyState[KEY_INPUT_LEFT] > 0 && px > 100 + PLAYER_SIZE_X) //�p������
	{
		px -= (int)MOVE_SPEED * slow;
	}
	if (keyState[KEY_INPUT_DOWN] > 0 && py < FRAME_HEIGHT - PLAYER_SIZE_Y) //�p������
	{
		py += (int)MOVE_SPEED * slow;
	}
	if (keyState[KEY_INPUT_UP] > 0 && py > 0 + PLAYER_SIZE_Y) //�p������
	{
		py -= (int)MOVE_SPEED * slow;
	}
}

void ViewPlayer(void)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawCircle(px, py, DamagedCoolTime, GetColor(100, 100, 255)); // ��e�N�[���^�C����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 256);
	DrawRotaGraph(px, py, 1.0, 0, player_img, TRUE); //�v���C���[�摜�̕`��
	DrawCircle(px, py, Player_HitBoxSize, GetColor(255, 255, 80)); // �v���C���[�̓����蔻��\��
}