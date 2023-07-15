#include "GameData.h"
#include "Player.h"
#include "Player_Bullet.h"
#include "Enemy_Bullet.h"
#include "Item.h"
using namespace std;

struct Enemy
{
	int hp;//体力
	bool boss;
};
Enemy enemy[3] = 
{ 
	{3 ,false},{4 ,false},{100 ,true}
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
int NowMoveMode[ENEMY_AMOUNT];
int Enemy_HP[ENEMY_AMOUNT];
float Enemy_dist[ENEMY_AMOUNT];
float E_ShotCoolTime[ENEMY_AMOUNT];
int E_AttackMode[ENEMY_AMOUNT];//射撃パターンの遷移

int CloseEnemy = -1;
float CloseDist = 1100;

void EnemyGenerate(int num, int type ,int move ,int x, int y, int hitboxsize)
{
	Enemy_exist[num] = true;
	Enemy_visible[num] = false;
	Enemy_Type[num] = type;
	Enemy_X[num] = x;
	Enemy_Y[num] = y;
	Enemy_HitBoxSize[num] = hitboxsize;
	Enemy_MoveTime[num] = 0;
	MovePattern[num] = move;
	NowMoveMode[num] = 0;
	Enemy_HP[num] = enemy[Enemy_Type[num]].hp;
	E_ShotCoolTime[num] = 0;
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
	NowMoveMode[num] = NULL;
	Enemy_HP[num] = NULL;
	Enemy_dist[num] = NULL;
	E_ShotCoolTime[num] = NULL;
	E_AttackMode[num] = NULL;

	CloseEnemy = -1;//近いキャラをリセット
	CloseDist = 1100;
}

void EnemySpawn(int type, MoveList move, int x, int y)
{
	for (int i = 0; i < ENEMY_AMOUNT; i++)
	{
		if (Enemy_exist[i] == false)
		{
			EnemyGenerate(i, type, move, x, y, 16);
			break;
		}
	}
}

void move(int num, int spdX, int spdY, int time)
{
	if(Enemy_MoveTime[num] <= 0) Enemy_MoveTime[num] = time;
	else
	{
		Enemy_X[num] += spdX;
		Enemy_Y[num] += spdY;
		Enemy_MoveTime[num]--;
		if (Enemy_MoveTime[num] <= 0) NowMoveMode[num]++;
	}
}

void EnemyMove(int num)
{
	
	switch (MovePattern[num])
	{
		case MOVE_A://直進
			switch (NowMoveMode[num])
			{
				case 0: move(num, 0, 2, 9999); break;
				default: break;
			}
			break;
		case MOVE_B://高速in一時停止後直進
			switch (NowMoveMode[num])
			{
				case 0: move(num, 0, 5, 30); break;
				case 1: move(num, 0, 0, 160); break;
				case 2: move(num, 0, 2, 9999); break;
				default: break;
			}
			break;
		case MOVE_C://高速in一時停止後左下
			switch (NowMoveMode[num])
			{
				case 0: move(num, 0, 5, 30); break;
				case 1: move(num, 0, 0, 70); break;
				case 2: move(num, -1, 2, 9999); break;
				default: break;
			}
			break;
		case MOVE_D://高速in一時停止後右下
			switch (NowMoveMode[num])
			{
				case 0: move(num, 0, 5, 30); break;
				case 1: move(num, 0, 0, 70); break;
				case 2: move(num, 1, 2, 9999); break;
				default: break;
			}
			break;
		case MOVE_E://右 から 下
			switch (NowMoveMode[num])
			{
				case 0: move(num, 3, 0, 180); break;
				case 1: move(num, 0, 0, 20); break;
				case 2: move(num, 0, 2, 9999); break;
				default: break;
			}
			break;
		case MOVE_BOSS://ボス
			switch (NowMoveMode[num])
			{
				case 0: move(num, 0, 5, 30); break;
				case 1: move(num, 0, 0, 160); break;
				default: break;
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

void wait(int num,int time)
{
	E_ShotCoolTime[num] = time;
	E_AttackMode[num]++;
}
void roop(int num)
{
	E_AttackMode[num] = 0;
}
void shot(int num, int design, EnemyShotPattern type, int size, int capacity, int arc, int interval)
{
	EnemyShot(design, type, Enemy_X[num], Enemy_Y[num], size, capacity, arc);//射撃	
	E_AttackMode[num]++;
	E_ShotCoolTime[num] = interval;
}

void EnemyShotAction(int num)
{
	if (E_ShotCoolTime[num] >= 0) E_ShotCoolTime[num]--;
	if (E_ShotCoolTime[num] < 0)
	{
		if (Enemy_Type[num] == 0)
		{
			switch (E_AttackMode[num])
			{
				case 0: wait(num, 60); break;
				case 1: shot(num, 0, AimingDiffusion, 4, 5, 10, 30); break;
			}
		}
		if (Enemy_Type[num] == 1)
		{
			switch (E_AttackMode[num])
			{
				case 0: wait(num, 90); break;
				case 1: shot(num, 7, Explosion, 6, 10, NULL, 10); break;
				case 2: shot(num, 8, Explosion, 6, 10, NULL, 10); break;
				case 3: shot(num, 9, Explosion, 6, 10, NULL, 5); break;
			}
		}
		if (Enemy_Type[num] == 2)
		{
			switch (E_AttackMode[num])
			{
				case 0: wait(num, 90); break;
				case 1: shot(num, 0, Explosion, 6, 20, NULL, 10); break;
				case 2: shot(num, 1, Explosion, 6, 20, NULL, 10); break;
				case 3: shot(num, 2, Explosion, 6, 30, NULL, 5); break;
				case 4: roop(num); break;
			}
		}
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