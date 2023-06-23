#include "GameData.h"
#include "Player.h"
#include "Player_Bullet.h"
using namespace std;

//�G
bool Enemy_exist[ENEMY_AMOUNT];
int Enemy_X[ENEMY_AMOUNT];
int Enemy_Y[ENEMY_AMOUNT];
int Enemy_HitBoxSize[ENEMY_AMOUNT];
int Enemy_MoveSpeed[ENEMY_AMOUNT];
int MovePattern[ENEMY_AMOUNT];
int Enemy_HP[ENEMY_AMOUNT];
float Enemy_dist[ENEMY_AMOUNT];

int CloseEnemy = -1;
float CloseDist = 700;

void EnemyGenerate(int num, int x, int y, int hitboxsize, int movespeed, int movepattern, int hp)
{
	Enemy_exist[num] = true;
	Enemy_X[num] = x;
	Enemy_Y[num] = y;
	Enemy_HitBoxSize[num] = hitboxsize;
	Enemy_MoveSpeed[num] = movespeed;
	MovePattern[num] = movepattern;
	Enemy_HP[num] = hp;
}

void EnemyDestroy(int num)
{
	Enemy_exist[num] = false;
	Enemy_X[num] = NULL;
	Enemy_Y[num] = NULL;
	Enemy_HitBoxSize[num] = NULL;
	Enemy_MoveSpeed[num] = NULL;
	MovePattern[num] = NULL;
	Enemy_HP[num] = NULL;
	Enemy_dist[num] = NULL;

	CloseEnemy = -1;//�߂��L���������Z�b�g
	CloseDist = 700;
}

void EnemySpawn(void)
{
	for (int i = 0; i < ENEMY_AMOUNT; i++)
	{
		if (Enemy_exist[i] == false)
		{
			EnemyGenerate(i, px, py - 600, 12, 2, 0, 5);
			DrawFormatString(WINDOW_WIDTH - 100, 90, GetColor(255, 255, 255), "%d\n", i);
			break;
		}
	}
}

void EnemyMove(int num)
{
	switch (MovePattern[num])
	{
		case 0://���i
			Enemy_Y[num] += Enemy_MoveSpeed[num];
			break;
		default:
			break;
	}
}

void CheckDistance(int num) 
{
	if (Enemy_dist[num] < CloseDist)
	{
		CloseEnemy = num;
	}
	CloseDist = Enemy_dist[CloseEnemy];
}

void EnemyAction(void)
{
	for (int i = 0; i < ENEMY_AMOUNT; i++)
	{
		//�G�L�����摜�\��
		if (Enemy_exist[i] == true) DrawCircle(Enemy_X[i], Enemy_Y[i], Enemy_HitBoxSize[i], GetColor(255, 0, 0), 1);
		else continue;

		EnemyMove(i);

		//��ʊO�ŏ���
		if (Enemy_Y[i] > WINDOW_HEIGHT + 30)
		{
			EnemyDestroy(i);
			continue;
		}

		//�G�ƃv���C���[���ڐG
		Enemy_dist[i] = sqrt(pow((double)Enemy_X[i] - px, 2) + pow((double)Enemy_Y[i] - py, 2));

		CheckDistance(i);
		DrawFormatString(WINDOW_WIDTH - 400, 30, GetColor(255, 255, 255), "Score : %d", CloseEnemy);

		if (Enemy_dist[i] <= Enemy_HitBoxSize[i] + Player_HitBoxSize)
		{
			//��e����
			if (DamagedCoolTime <= 0)
			{
				px = InitialPosX;
				py = InitialPosY;
				Life -= 1;
				DamagedCoolTime = 120;
			}

		}

		//�_���[�Wor���S
		for (int j = 0; j < PLAYER_BULLET_AMOUNT; j++)
		{
			//�G�Ƃ̍��W�`�F�b�N
			float dis = sqrt(pow((double)Enemy_X[i] - P_Bullet_PosX[j], 2) + pow((double)Enemy_Y[i] - P_Bullet_PosY[j], 2));
			if (dis <= Enemy_HitBoxSize[i] + P_Bullet_HitBoxSize[j])//��e����
			{
				PlayerBulletDestroy(j);
				if (Enemy_HP[i] > 0)
				{
					Score += 1;
					Enemy_HP[i] -= 1;
				}
				else
				{
					Score += 100;
					EnemyDestroy(i);
				}
				break;
			}
		}
	}
}

