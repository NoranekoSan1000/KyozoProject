#include "GameData.h"
#define PLAYER_SIZE_X 12
#define PLAYER_SIZE_Y 24

//�v���C���[
int InitialPosX = 325;
int InitialPosY = 675;
int Player_HitBoxSize = 4;
int px = InitialPosX;
int py = InitialPosY;
int Power = 0;
int NextPower[3] = { 10, 40, 100 };//LevelUp�ɕK�v��Power
int Level = 0;
int Score = 0;
int Life = 3;
float DamagedCoolTime = 0;
float P_ShotCoolTime = 0;

void LevelUp(void)
{
	if (Power < NextPower[0])
	{
		Level = 0;
	}
	else if (Power >= NextPower[0] && Power < NextPower[1])
	{
		Level = 1;
	}
	else if (Power >= NextPower[1] && Power < NextPower[2])
	{
		Level = 2;
	}
	else Level = 3;
}

void PlayerMove(void)
{
	int MOVE_SPEED = 5;
	
	if (KeyState[KEY_INPUT_LSHIFT] > 0) MOVE_SPEED = 2;
	else MOVE_SPEED = 5;

	if (KeyState[KEY_INPUT_RIGHT] > 0 && px < FRAME_WIDTH - PLAYER_SIZE_X) //�p������
	{
		px += (int)MOVE_SPEED;
	}
	if (KeyState[KEY_INPUT_LEFT] > 0 && px > 25 + PLAYER_SIZE_X) //�p������
	{
		px -= (int)MOVE_SPEED;
	}
	if (KeyState[KEY_INPUT_DOWN] > 0 && py < FRAME_HEIGHT - PLAYER_SIZE_Y) //�p������
	{
		py += (int)MOVE_SPEED;
	}
	if (KeyState[KEY_INPUT_UP] > 0 && py > 25 + PLAYER_SIZE_Y) //�p������
	{
		py -= (int)MOVE_SPEED;
	}
}

void ViewPlayer(void)
{
	PlayerMove();//�v���C���[�̈ړ�

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawCircle(px, py, DamagedCoolTime, GetColor(100, 100, 255)); // ��e�N�[���^�C����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 256);
	DrawRotaGraph(px, py, 1.0, 0, player_img, TRUE); //�v���C���[�摜�̕`��
	DrawCircle(px, py, Player_HitBoxSize, GetColor(255, 255, 80)); // �v���C���[�̓����蔻��\��
}
