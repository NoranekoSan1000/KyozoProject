#include "GameData.h"
#include "Enemy.h"
#include "Player.h"

//�v���C���[�̒e
bool P_Bullet_exist[PLAYER_BULLET_AMOUNT];
int P_Bullet_PosX[PLAYER_BULLET_AMOUNT];
int P_Bullet_PosY[PLAYER_BULLET_AMOUNT];
int P_Bullet_HitBoxSize[PLAYER_BULLET_AMOUNT];
int P_Bullet_MovePattern[PLAYER_BULLET_AMOUNT];
float P_ShotCoolTime = 0;

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

void PlayerShotGenerate(int px,int py)
{
	if (P_ShotCoolTime > 0) return;
	for (int i = 0; i < PLAYER_BULLET_AMOUNT; i++)
	{
		if (P_Bullet_exist[i] == false)//�V���b�g�ݒ�i�[�ꏊ�̋󂫂��m�F
		{
			PlaySE(SE_PlayerShot); //���ʉ�
			PlayerBulletGenerate(i, px, py, 4, 3);
			//PlayerBulletGenerate(i+1, px, py, 4, 1);
			//PlayerBulletGenerate(i+2, px, py, 4, 2);
			P_ShotCoolTime = 10;//�t���[���Őݒ�
			break;
		}
	}
}

void BulletMove(int num)
{
	float angle = (3 * PI / 2);//���
	float speed = 12;

	float xv, yv, v; //�x�N�g��
	switch (P_Bullet_MovePattern[num])
	{
	case 0://���i
		P_Bullet_PosX[num] += cos(angle) * speed;
		P_Bullet_PosY[num] += sin(angle) * speed;
		break;
	case 1://�E�΂�
		P_Bullet_PosX[num] += cos(angle + 0.3) * speed;
		P_Bullet_PosY[num] += sin(angle + 0.3) * speed;
		break;
	case 2://���΂�
		P_Bullet_PosX[num] += cos(angle - 0.2) * speed;
		P_Bullet_PosY[num] += sin(angle - 0.2) * speed;
		break;
	case 3://�߂��G�_��
		if (CloseEnemy == NULL) 
		{
			P_Bullet_PosX[num] += cos(angle) * speed;
			P_Bullet_PosY[num] += sin(angle) * speed;
		}
		else
		{
			xv = (Enemy_X[CloseEnemy] - P_Bullet_PosX[num]);
			yv = (Enemy_Y[CloseEnemy] - P_Bullet_PosY[num]);
			v = sqrt((xv * xv) + (yv * yv));
			P_Bullet_PosX[num] += (xv / v) * speed;
			P_Bullet_PosY[num] += (yv / v) * speed;
		}	
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
		if (P_Bullet_PosY[i] < -20)
		{
			PlayerBulletDestroy(i);
			continue;
		}

	}
}
