#include "GameData.h"
#include "Enemy.h"

//�v���C���[�̒e
bool P_Bullet_exist[PLAYER_BULLET_AMOUNT];
int P_Bullet_PosX[PLAYER_BULLET_AMOUNT];
int P_Bullet_PosY[PLAYER_BULLET_AMOUNT];
int P_Bullet_HitBoxSize[PLAYER_BULLET_AMOUNT];
int P_Bullet_MovePattern[PLAYER_BULLET_AMOUNT];

void PlayerBulletGenerate(int num, int x, int y, int hitboxsize, int pattern)
{
	P_Bullet_exist[num] = true;
	P_Bullet_PosX[num] = x;
	P_Bullet_PosY[num] = y;
	P_Bullet_HitBoxSize[num] = hitboxsize;
	P_Bullet_MovePattern[num] = pattern;
}

void PlayerBulletDestroy(int num)
{
	P_Bullet_exist[num] = false;
	P_Bullet_PosX[num] = NULL;
	P_Bullet_PosY[num] = NULL;
	P_Bullet_HitBoxSize[num] = NULL;
	P_Bullet_MovePattern[num] = NULL;
}

void PlayerShot(int px,int py,int type)
{
	for (int i = 0; i < PLAYER_BULLET_AMOUNT; i++)
	{
		if (P_Bullet_exist[i] == false)//�V���b�g�ݒ�i�[�ꏊ�̋󂫂��m�F
		{
			PlaySE(SE_PlayerShot); //���ʉ�
			PlayerBulletGenerate(i, px, py, 4, type);
			break;
		}
	}
}

void BulletMove(int num)
{
	float angle = (3 * PI / 2);//���
	float speed = 12;

	switch (P_Bullet_MovePattern[num])
	{
	case 0://���i
		P_Bullet_PosX[num] += cos(angle) * speed;
		P_Bullet_PosY[num] += sin(angle) * speed;
		break;
	case 1://�E�΂ߒ�
		P_Bullet_PosX[num] += cos(angle + 0.3) * speed;
		P_Bullet_PosY[num] += sin(angle + 0.3) * speed;
		break;
	case 2://���΂ߒ�
		P_Bullet_PosX[num] += cos(angle - 0.2) * speed;
		P_Bullet_PosY[num] += sin(angle - 0.2) * speed;
		break;
	case 3://�߂��G�_��
		P_Bullet_PosX[num] += cos(angle + 0.15) * speed;
		P_Bullet_PosY[num] += sin(angle + 0.15) * speed;
		break;
	case 4://�߂��G�_��
		P_Bullet_PosX[num] += cos(angle - 0.05) * speed;
		P_Bullet_PosY[num] += sin(angle - 0.05) * speed;
		break;
	case 5://�߂��G�_��

		break;
	case 6://�߂��G�_��

		break;
	default:
		break;
	}
}

void PlayerBulletAction(void)
{
	
	for (int i = 0; i < PLAYER_BULLET_AMOUNT; i++)
	{
		
		if (P_Bullet_exist[i] == true) DrawCircle(P_Bullet_PosX[i], P_Bullet_PosY[i], P_Bullet_HitBoxSize[i], GetColor(100, 100, 255), 1);
		else continue;
		DrawRotaGraph(P_Bullet_PosX[i], P_Bullet_PosY[i], 1.0, 0, PlayerShot_img, TRUE);

		BulletMove(i);

		//��ʊO�ŏ���
		if (P_Bullet_PosY[i] < -20 || P_Bullet_PosY[i] > FRAME_HEIGHT || 0 > P_Bullet_PosX[i] || P_Bullet_PosX[i] > FRAME_WIDTH)
		{
			PlayerBulletDestroy(i);
			continue;
		}

	}
}
