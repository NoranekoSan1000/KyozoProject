#include "GameData.h"
#include "Player.h"
#include "Player_Bullet.h"
#include "Enemy_Bullet.h"
#include "Item.h"
using namespace std;

struct Enemy
{
	int hp;
	int speed;
	int movepattern;
};
Enemy enemy[2] = { { 5,2,0 }, { 6,2,1 } };

//敵
bool Enemy_exist[ENEMY_AMOUNT];//敵が存在するか
bool Enemy_visible[ENEMY_AMOUNT];//敵が画面内にいるか
int Enemy_Type[ENEMY_AMOUNT];//画像用
int Enemy_X[ENEMY_AMOUNT];
int Enemy_Y[ENEMY_AMOUNT];
int Enemy_HitBoxSize[ENEMY_AMOUNT];
int Enemy_MoveTime[ENEMY_AMOUNT];
int MovePattern[ENEMY_AMOUNT];//移動パターン
int Enemy_HP[ENEMY_AMOUNT];
float Enemy_dist[ENEMY_AMOUNT];
float E_ShotCoolTime[ENEMY_AMOUNT];

int CloseEnemy = -1;
float CloseDist = 1100;

void EnemyGenerate(int num, int type, int x, int y, int hitboxsize, int movetime, int movepattern, int hp)
{
	Enemy_exist[num] = true;
	Enemy_visible[num] = false;
	Enemy_Type[num] = type;
	Enemy_X[num] = x;
	Enemy_Y[num] = y;
	Enemy_HitBoxSize[num] = hitboxsize;
	Enemy_MoveTime[num] = movetime;
	MovePattern[num] = movepattern;
	Enemy_HP[num] = hp;
	E_ShotCoolTime[num] = 0;
}

void EnemyDestroy(int num)
{
	Enemy_exist[num] = false;
	Enemy_visible[num] = false;
	Enemy_Type[num] = NULL;
	Enemy_X[num] = NULL;
	Enemy_Y[num] = NULL;
	Enemy_HitBoxSize[num] = NULL;
	Enemy_MoveTime[num] = NULL;
	MovePattern[num] = NULL;
	Enemy_HP[num] = NULL;
	Enemy_dist[num] = NULL;
	E_ShotCoolTime[num] = NULL;

	CloseEnemy = -1;//近いキャラをリセット
	CloseDist = 1100;
}

void spawn(int type,int x,int y)
{
	for (int i = 0; i < ENEMY_AMOUNT; i++)
	{
		if (Enemy_exist[i] == false)
		{
			EnemyGenerate(i, type, x, y, 16, 2, enemy[type].movepattern, enemy[type].hp);
			break;
		}
	}
}

void EnemySpawn(int spawnPattern)
{
	if (spawnPattern == 0) return;
	else if (spawnPattern == 1) //上から3体
	{
		spawn(0, 150, 0);
		spawn(0, 150, -100);
		spawn(1, 300, -200);
	}
	else if (spawnPattern == 2)
	{
		spawn(0, 450, 0);
		spawn(0, 450, -100);
		spawn(1, 300, -200);
	}
}

void EnemyMove(int num)
{
	Enemy_MoveTime[num]++;
	switch (MovePattern[num])
	{
		case 0://直進
			Enemy_Y[num] += 2;
			break;
		case 1://直進
			if(Enemy_MoveTime[num] < 60) Enemy_Y[num] += 6;
			else if (Enemy_MoveTime[num] >= 60 && Enemy_MoveTime[num] < 180) Enemy_Y[num] += 0;
			else if (Enemy_MoveTime[num] >= 180) Enemy_Y[num] += 2;
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
	EnemyShot(3, Enemy_X[num], Enemy_Y[num]);//射撃
	E_ShotCoolTime[num] = 60;//フレームで設定
}

void EnemyAction(void)
{
	for (int i = 0; i < ENEMY_AMOUNT; i++)
	{
		//敵キャラ画像表示
		if (Enemy_exist[i] == true) DrawRotaGraph(Enemy_X[i], Enemy_Y[i], 1.0, 0, Enemy_img[Enemy_Type[i]], TRUE); //画像の描画
		else continue;

		//DrawCircle(Enemy_X[i], Enemy_Y[i], Enemy_HitBoxSize[i], GetColor(255, 0, 0), 1);
		
		//移動
		EnemyMove(i);

		//画面内に一度でも入ればtrue
		if (Enemy_X[i] <= FRAME_WIDTH && Enemy_X[i] >= 0 && Enemy_Y[i] <= FRAME_HEIGHT && Enemy_Y[i] >= 0) Enemy_visible[i] = true;
		
		if (Enemy_visible[i])
		{
			if (E_ShotCoolTime[i] >= 0) E_ShotCoolTime[i]--;
			EnemyShotAction(i);

			//敵とプレイヤーの距離
			Enemy_dist[i] = sqrt(pow((double)Enemy_X[i] - px, 2) + pow((double)Enemy_Y[i] - py, 2));
			CheckDistance(i);

			//画面外で消滅
			if (Enemy_visible[i] && (Enemy_Y[i] > FRAME_HEIGHT || -20 > Enemy_X[i] || Enemy_X[i] > FRAME_WIDTH + 20))
			{
				EnemyDestroy(i);
				continue;
			}

			if (Enemy_dist[i] <= Enemy_HitBoxSize[i] + Player_HitBoxSize)
			{		
				//被弾判定
				if (DamagedCoolTime <= 0)
				{
					if (Life > 0)
					{
						px = InitialPosX;
						py = InitialPosY;
						Life -= 1;
						DamagedCoolTime = 120;
						EnemyBulletClear();
					}
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
					else//死亡時
					{
						Score += 10;
						ItemSpawn(Enemy_X[i], Enemy_Y[i]);//アイテム生成
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