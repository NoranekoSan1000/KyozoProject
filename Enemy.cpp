#include "GameData.h"
#include "Player.h"
#include "Player_Bullet.h"
#include "Enemy_Bullet.h"
#include "Item.h"
using namespace std;

struct Enemy
{
	int hp;//体力
	int movepattern;//移動パターン
	int firstshottime;
};
Enemy enemy[2] = 
{ 
	{ 4, 0, 60},
	{ 5, 1, 90} 
};

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
int E_AttackMode[ENEMY_AMOUNT];//射撃パターンの遷移

int CloseEnemy = -1;
float CloseDist = 1100;

void EnemyGenerate(int num, int type, int x, int y, int hitboxsize)
{
	Enemy_exist[num] = true;
	Enemy_visible[num] = false;
	Enemy_Type[num] = type;
	Enemy_X[num] = x;
	Enemy_Y[num] = y;
	Enemy_HitBoxSize[num] = hitboxsize;
	Enemy_MoveTime[num] = 0;
	MovePattern[num] = enemy[Enemy_Type[num]].movepattern;
	Enemy_HP[num] = enemy[Enemy_Type[num]].hp;
	E_ShotCoolTime[num] = enemy[Enemy_Type[num]].firstshottime;
	E_AttackMode[num] = 0;
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
	E_AttackMode[num] = NULL;

	CloseEnemy = -1;//近いキャラをリセット
	CloseDist = 1100;
}

void spawn(int type,int x,int y)
{
	for (int i = 0; i < ENEMY_AMOUNT; i++)
	{
		if (Enemy_exist[i] == false)
		{
			EnemyGenerate(i, type, x, y, 16);
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
	}
	else if (spawnPattern == 2) //上から3体
	{
		spawn(0, 450, 0);
	}
	else if (spawnPattern == 3)
	{
		spawn(1, 300, -300);
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
		case 1://高速in一時停止後直進
			if(Enemy_MoveTime[num] < 80) Enemy_Y[num] += 6;
			else if (Enemy_MoveTime[num] >= 80 && Enemy_MoveTime[num] < 240) Enemy_Y[num] += 0;
			else if (Enemy_MoveTime[num] >= 240) Enemy_Y[num] += 2;
			break;
		case 2://高速in一時停止後左下
			if (Enemy_MoveTime[num] < 50) Enemy_Y[num] += 5;
			else if (Enemy_MoveTime[num] >= 50 && Enemy_MoveTime[num] < 120) Enemy_Y[num] += 0;
			else if (Enemy_MoveTime[num] >= 120)
			{
				Enemy_X[num] -= 1;
				Enemy_Y[num] += 2;
			}
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
	int x = Enemy_X[num];
	int y = Enemy_Y[num];

	if (Enemy_Type[num] == 0) 
	{
		if (E_AttackMode[num] == 0)
		{
			EnemyShot(0, Explosion, x, y, 4, 5, NULL);//射撃	
			E_ShotCoolTime[num] = 30;//次のショットまでの時間
		}
		if (E_AttackMode[num] == 1)
		{
			EnemyShot(1, Diffusion, x, y, 4, 5, 90);//射撃	
		}
		E_AttackMode[num] ++;
		return;
	}
	if (Enemy_Type[num] == 1)
	{
		if (E_AttackMode[num] == 0)
		{
			EnemyShot(7, Explosion, x, y, 6, 10, NULL);//射撃	
			E_ShotCoolTime[num] = 5;//次のショットまでの時間
		}
		if (E_AttackMode[num] == 1)
		{
			EnemyShot(8, Explosion, x, y, 6, 10, NULL);//射撃	
			E_ShotCoolTime[num] = 5;//次のショットまでの時間
		}
		if (E_AttackMode[num] == 2)
		{
			EnemyShot(9, Explosion, x, y, 6, 10, NULL);//射撃	
		}
		E_AttackMode[num] ++;
		return;
	}
	
	
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
				if (DamagedCoolTime <= 0 && BombTime <= 0)
				{
					if (Life > 0)
					{
						px = InitialPosX;
						py = InitialPosY;
						Life -= 1;
						Bomb = 2;
						DamagedCoolTime = 120;
						EnemyBulletClear();
					}
				}
			}

			//ダメージ
			for (int j = 0; j < PLAYER_BULLET_AMOUNT; j++)
			{
				//敵との座標チェック
				float dis = sqrt(pow((double)Enemy_X[i] - P_Bullet_PosX[j], 2) + pow((double)Enemy_Y[i] - P_Bullet_PosY[j], 2));
				if (dis <= Enemy_HitBoxSize[i] + P_Bullet_HitBoxSize[j])//被弾判定
				{
					PlayerBulletDestroy(j);
					if (Enemy_HP[i] >= 1)
					{
						Score += 1;
						Enemy_HP[i] -= 1;
					}
					break;
				}
			}

			if(Enemy_HP[i] <= 0)//死亡時
			{
				Score += 10;
				ItemSpawn(Enemy_X[i], Enemy_Y[i]);//アイテム生成
				EnemyDestroy(i);
			}
		}
	}
}

void EnemyClear(void)
{
	for (int i = 0; i < ENEMY_AMOUNT; i++) EnemyDestroy(i);
}