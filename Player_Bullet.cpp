#include "GameData.h"

//�v���C���[�̒e
bool P_Bullet_exist[PLAYER_BULLET_AMOUNT];
int P_Bullet_PosX[PLAYER_BULLET_AMOUNT];
int P_Bullet_PosY[PLAYER_BULLET_AMOUNT];
int P_Bullet_HitBoxSize[PLAYER_BULLET_AMOUNT];
float P_ShotCoolTime = 0;

void PlayerBulletGenerate(int num, int x, int y, int hitboxsize)
{
	P_Bullet_exist[num] = true;
	P_Bullet_PosX[num] = x;
	P_Bullet_PosY[num] = y;
	P_Bullet_HitBoxSize[num] = hitboxsize;
}

void PlayerBulletDestroy(int num)
{
	P_Bullet_exist[num] = false;
	P_Bullet_PosX[num] = NULL;
	P_Bullet_PosY[num] = NULL;
	P_Bullet_HitBoxSize[num] = NULL;
}

void PlayerShotGenerate(int px,int py)
{
	if (P_ShotCoolTime > 0) return;
	for (int i = 0; i < PLAYER_BULLET_AMOUNT; i++)
	{
		if (P_Bullet_exist[i] == false)//�V���b�g�ݒ�i�[�ꏊ�̋󂫂��m�F
		{
			PlayerBulletGenerate(i, px, py, 6);
			P_ShotCoolTime = 10;//�t���[���Őݒ�
			break;
		}
	}
}

void PlayerBulletAction(void)
{
	for (int i = 0; i < PLAYER_BULLET_AMOUNT; i++)
	{
		if (P_Bullet_exist[i] == true) DrawCircle(P_Bullet_PosX[i], P_Bullet_PosY[i], P_Bullet_HitBoxSize[i], GetColor(0, 100, 100), 1);
		else continue;

		P_Bullet_PosY[i] -= 12;

		//��ʊO�ŏ���
		if (P_Bullet_PosY[i] < -20)
		{
			PlayerBulletDestroy(i);
			continue;
		}

	}
}
