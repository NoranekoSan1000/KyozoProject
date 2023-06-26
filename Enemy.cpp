#include "GameData.h"
#include "Player.h"
#include "Player_Bullet.h"
#include "Enemy_Bullet.h"
using namespace std;

//敵
bool Enemy_exist[ENEMY_AMOUNT];
int Enemy_X[ENEMY_AMOUNT];
int Enemy_Y[ENEMY_AMOUNT];
int Enemy_HitBoxSize[ENEMY_AMOUNT];
int Enemy_MoveSpeed[ENEMY_AMOUNT];
int MovePattern[ENEMY_AMOUNT];
int Enemy_HP[ENEMY_AMOUNT];
float Enemy_dist[ENEMY_AMOUNT];

float E_ShotCoolTime[ENEMY_AMOUNT];

int CloseEnemy = -1;
float CloseDist = 800;

void EnemyGenerate(int num, int x, int y, int hitboxsize, int movespeed, int movepattern, int hp, int ct)
{
	Enemy_exist[num] = true;
	Enemy_X[num] = x;
	Enemy_Y[num] = y;
	Enemy_HitBoxSize[num] = hitboxsize;
	Enemy_MoveSpeed[num] = movespeed;
	MovePattern[num] = movepattern;
	Enemy_HP[num] = hp;
	E_ShotCoolTime[num] = ct;
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
	E_ShotCoolTime[num] = NULL;

	CloseEnemy = -1;//近いキャラをリセット
	CloseDist = 800;
}

void EnemySpawn(void)
{
	for (int i = 0; i < ENEMY_AMOUNT; i++)
	{
		if (Enemy_exist[i] == false)
		{
			EnemyGenerate(i, px, py - 900, 12, 2, 0, 5, 0);
			break;
		}
	}
}

void EnemyMove(int num)
{
	switch (MovePattern[num])
	{
		case 0://直進
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
	EnemyShot(Enemy_X[num], Enemy_Y[num], 4, 5);//射撃
	E_ShotCoolTime[num] = 60;//フレームで設定
}

void EnemyAction(void)
{
	for (int i = 0; i < ENEMY_AMOUNT; i++)
	{
		//敵キャラ画像表示
		if (Enemy_exist[i] == true) DrawCircle(Enemy_X[i], Enemy_Y[i], Enemy_HitBoxSize[i], GetColor(255, 0, 0), 1);
		else continue;

		EnemyMove(i); 

		if (E_ShotCoolTime[i] >= 0) E_ShotCoolTime[i]--;
		EnemyShotAction(i);

		//画面外で消滅
		if (/*E_Bullet_PosY[i] < -20 || */E_Bullet_PosY[i] > FRAME_HEIGHT || 0 > E_Bullet_PosX[i] || E_Bullet_PosX[i] > FRAME_WIDTH)
		{
			EnemyDestroy(i);
			continue;
		}

		//敵とプレイヤーが接触
		Enemy_dist[i] = sqrt(pow((double)Enemy_X[i] - px, 2) + pow((double)Enemy_Y[i] - py, 2));

		CheckDistance(i);

		if (Enemy_dist[i] <= Enemy_HitBoxSize[i] + Player_HitBoxSize)
		{
			//被弾判定
			if (DamagedCoolTime <= 0)
			{
				px = InitialPosX;
				py = InitialPosY;
				Life -= 1;
				DamagedCoolTime = 120;
			}

		}

		//ダメージor死亡
		for (int j = 0; j < PLAYER_BULLET_AMOUNT; j++)
		{
			//敵との座標チェック
			float dis = sqrt(pow((double)Enemy_X[i] - P_Bullet_PosX[j], 2) + pow((double)Enemy_Y[i] - P_Bullet_PosY[j], 2));
			if (dis <= Enemy_HitBoxSize[i] + P_Bullet_HitBoxSize[j])//被弾判定
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

void EnemyClear(void)
{
	for (int i = 0; i < ENEMY_AMOUNT; i++) EnemyDestroy(i);
}