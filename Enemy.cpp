#include "GameData.h"
#include "Player.h"
#include "Player_Bullet.h"
#include "Enemy_Bullet.h"
#include "Item.h"
using namespace std;

//�G
bool Enemy_exist[ENEMY_AMOUNT];
bool Enemy_visible[ENEMY_AMOUNT];
int Enemy_X[ENEMY_AMOUNT];
int Enemy_Y[ENEMY_AMOUNT];
int Enemy_HitBoxSize[ENEMY_AMOUNT];
int Enemy_MoveSpeed[ENEMY_AMOUNT];
int MovePattern[ENEMY_AMOUNT];
int Enemy_HP[ENEMY_AMOUNT];
float Enemy_dist[ENEMY_AMOUNT];

float E_ShotCoolTime[ENEMY_AMOUNT];

int CloseEnemy = -1;
float CloseDist = 1100;

void EnemyGenerate(int num, int x, int y, int hitboxsize, int movespeed, int movepattern, int hp)
{
	Enemy_exist[num] = true;
	Enemy_visible[num] = false;
	Enemy_X[num] = x;
	Enemy_Y[num] = y;
	Enemy_HitBoxSize[num] = hitboxsize;
	Enemy_MoveSpeed[num] = movespeed;
	MovePattern[num] = movepattern;
	Enemy_HP[num] = hp;
	E_ShotCoolTime[num] = 0;
}

void EnemyDestroy(int num)
{
	Enemy_exist[num] = false;
	Enemy_visible[num] = false;
	Enemy_X[num] = NULL;
	Enemy_Y[num] = NULL;
	Enemy_HitBoxSize[num] = NULL;
	Enemy_MoveSpeed[num] = NULL;
	MovePattern[num] = NULL;
	Enemy_HP[num] = NULL;
	Enemy_dist[num] = NULL;
	E_ShotCoolTime[num] = NULL;

	CloseEnemy = -1;//�߂��L���������Z�b�g
	CloseDist = 1100;
}

void spawn(int x,int y,int spd,int move,int hp)
{
	for (int i = 0; i < ENEMY_AMOUNT; i++)
	{
		if (Enemy_exist[i] == false)
		{
			EnemyGenerate(i, x, y, 16, spd, move, hp);
			EnemyGenerate(i, x, y, 16, spd, move, hp);
			break;
		}
	}
}

void EnemySpawn(int pattern)
{
	if (pattern == 0) return;
	else if (pattern == 1) 
	{
		spawn(100, 0, 2, 0, 5);
		spawn(100, -90, 2, 0, 5);
		spawn(100, -180, 2, 0, 5);
	}
	else if (pattern == 2)
	{
		spawn(500, 0, 2, 0, 5);
		spawn(500, -90, 2, 0, 5);
		spawn(500, -180, 2, 0, 5);
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

void EnemyShotAction(int num)
{
	if (E_ShotCoolTime[num] > 0) return;
	EnemyShot(Enemy_X[num], Enemy_Y[num], 4, 5);//�ˌ�
	E_ShotCoolTime[num] = 60;//�t���[���Őݒ�
}

void EnemyAction(void)
{
	for (int i = 0; i < ENEMY_AMOUNT; i++)
	{
		//�G�L�����摜�\��
		if (Enemy_exist[i] == true) DrawCircle(Enemy_X[i], Enemy_Y[i], Enemy_HitBoxSize[i], GetColor(255, 0, 0), 1);
		else continue;
		//��ʓ��ɂ���
		if (Enemy_X[i] <= FRAME_WIDTH && Enemy_X[i] >= 0 && Enemy_Y[i] <= FRAME_HEIGHT && Enemy_Y[i] >= 0) Enemy_visible[i] = true;

		EnemyMove(i);

		if (Enemy_visible[i])
		{
			if (E_ShotCoolTime[i] >= 0) E_ShotCoolTime[i]--;
			EnemyShotAction(i);

			//�G�ƃv���C���[���ڐG
			Enemy_dist[i] = sqrt(pow((double)Enemy_X[i] - px, 2) + pow((double)Enemy_Y[i] - py, 2));
			CheckDistance(i);

			//��ʊO�ŏ���
			if (Enemy_visible[i] && (Enemy_Y[i] > FRAME_HEIGHT || -20 > Enemy_X[i] || Enemy_X[i] > FRAME_WIDTH + 20))
			{
				EnemyDestroy(i);
				continue;
			}

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
					else//���S��
					{
						Score += 10;
						ItemSpawn(Enemy_X[i], Enemy_Y[i]);//�A�C�e������
						EnemyDestroy(i);
					}
					break;
				}
			}
		}
	}
}

void EnemyClear(void)
{
	for (int i = 0; i < ENEMY_AMOUNT; i++) EnemyDestroy(i);
}