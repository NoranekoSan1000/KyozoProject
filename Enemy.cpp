#include "GameData.h"
#include "Player.h"
#include "Player_Bullet.h"
#include "Enemy_Bullet.h"
#include "Item.h"
using namespace std;

struct EnemyType
{
	int hp;//体力
	bool boss;
	int enemyImg;
};
EnemyType enemytype[3] = 
{ 
	{3 ,false ,2},{4 ,false ,3},//Enemy
	{75 ,true , 0}//Boss
};

float CloseDist = 1100;
int CloseEnemy = -1;
bool BossActive = false;
int Boss = -1;
int BossMaxHp = 0;
int BossCurrentHp = 0;
int BossStock = 0;//ターン数

class Enemy
{
private:
	
public:
	bool State;//敵が存在するか
	bool Visible;//敵が画面内にいるか
	int Enemy_Type;//画像用
	int X,Y;
	int HitBoxSize;
	int MoveTime;
	int MovePattern;//移動パターン
	int NowMoveMode;
	int HP;
	float Enemy_dist;
	float E_ShotCoolTime;
	int E_AttackMode;//射撃パターンの遷移

	void EnemyGenerate(int num, int type, int move, int x, int y, int hitboxsize)
	{
		State = true;
		Visible = false;
		Enemy_Type = type;
		X = x;
		Y = y;
		HitBoxSize = hitboxsize;
		MoveTime = 0;
		MovePattern = move;
		NowMoveMode = 0;
		HP = enemytype[Enemy_Type].hp;
		E_ShotCoolTime = 0;
		E_AttackMode = 0;

		if (enemytype[type].boss == true)
		{
			BossActive = true;
			Boss = num;
			BossMaxHp = enemytype[Enemy_Type].hp;
			BossCurrentHp = enemytype[Enemy_Type].hp;
			BossStock = 1;
		}
	}

	void EnemyDestroy()
	{
		State = false;
		Visible = false;
		Enemy_Type = X = Y = HitBoxSize = MoveTime = MovePattern = NowMoveMode = HP = Enemy_dist = E_ShotCoolTime = E_AttackMode = NULL;
		
		CloseEnemy = -1;//近いキャラをリセット
		CloseDist = 1100;
	}

	void move(int spdX, int spdY, int time)
	{
		if (MoveTime <= 0) MoveTime = time;
		else
		{
			X += spdX;
			Y += spdY;
			MoveTime--;
			if (MoveTime <= 0) NowMoveMode++;
		}
	}
	void EnemyMove()
	{
		switch (MovePattern)
		{
		case MOVE_A://直進
			switch (NowMoveMode)
			{
			case 0: move(0, 2, 9999); break;
			default: break;
			}
			break;
		case MOVE_B://高速in一時停止後直進
			switch (NowMoveMode)
			{
			case 0: move(0, 5, 30); break;
			case 1: move(0, 0, 160); break;
			case 2: move(0, 2, 9999); break;
			default: break;
			}
			break;
		case MOVE_C://高速in一時停止後左下
			switch (NowMoveMode)
			{
			case 0: move(0, 5, 30); break;
			case 1: move(0, 0, 70); break;
			case 2: move(-1, 2, 9999); break;
			default: break;
			}
			break;
		case MOVE_D://高速in一時停止後右下
			switch (NowMoveMode)
			{
			case 0: move(0, 5, 30); break;
			case 1: move(0, 0, 70); break;
			case 2: move(1, 2, 9999); break;
			default: break;
			}
			break;
		case MOVE_E://右 から 下
			switch (NowMoveMode)
			{
			case 0: move(3, 0, 180); break;
			case 1: move(0, 0, 20); break;
			case 2: move(0, 2, 9999); break;
			default: break;
			}
			break;
		case MOVE_BOSS://ボス
			switch (NowMoveMode)
			{
			case 0: move(0, 5, 30); break;
			case 1: move(0, 0, 160); break;
			default: break;
			}
			break;
		default:
			break;
		}
	}

	void wait(int time)
	{
		E_ShotCoolTime = time;
		E_AttackMode++;
	}
	void loop(int back)
	{
		E_AttackMode = back;
	}
	void shot(int design, EnemyShotPattern type, int size, int capacity, int arc, int interval)
	{
		EnemyShot(design, type, X, Y, size, capacity, arc);//射撃	
		E_AttackMode++;
		E_ShotCoolTime = interval;
	}
	void EnemyShotAction()
	{
		if (E_ShotCoolTime >= 0) E_ShotCoolTime--;
		if (E_ShotCoolTime < 0)
		{
			if (Enemy_Type == 0)
			{
				if (SelectDifficulty == 0 || SelectDifficulty == 1); //NoAction
				else if (SelectDifficulty == 2)
				{
					switch (E_AttackMode)
					{
					case 0: wait(90); break;
					case 1: shot(0, AimingOneShot, 4, 1, 10, NULL); break;
					}
				}
				else if (SelectDifficulty == 3)
				{
					switch (E_AttackMode)
					{
					case 0: wait(90); break;
					case 1: shot(0, AimingDiffusion, 4, 3, 10, 90); break;
					}
				}
			}
			if (Enemy_Type == 1)
			{
				switch (E_AttackMode)
				{
				case 0: wait(90); break;
				case 1: shot(7, Explosion, 6, 10, NULL, 10); break;
				case 2: shot(8, Explosion, 6, 10, NULL, 10); break;
				case 3: shot(9, Explosion, 6, 10, NULL, 5); break;
				}
			}
			if (Enemy_Type == 2)
			{
				if (BossStock == 1)
				{
					switch (E_AttackMode)
					{
					case 0: wait(90); break;
					case 1: shot(0, Explosion, 6, 20, NULL, 10); break;
					case 2: shot(1, Explosion, 6, 20, NULL, 10); break;
					case 3: shot(2, Explosion, 6, 30, NULL, 5); break;
					case 4: loop(0); break;
					}
				}
				if (BossStock == 0)
				{
					switch (E_AttackMode)
					{
					case 0: wait(90); break;
					case 1: shot(5, Explosion, 10, 20, NULL, 20); break;
					case 2: shot(6, Explosion, 10, 20, NULL, 20); break;
					case 3: shot(7, Explosion, 10, 30, NULL, 20); break;
					case 4: shot(8, Explosion, 10, 30, NULL, 20); break;
					case 5: loop(0); break;
					}
				}

			}
		}

	}
};

Enemy enemy[ENEMY_AMOUNT];

void CheckDistance(int num)
{
	if (enemy[num].Enemy_dist < CloseDist) CloseEnemy = num;
	CloseDist = enemy[CloseEnemy].Enemy_dist;//最近を編集
}

//外部から呼び出し
void EnemySpawn(int type, MoveList move, int x, int y)
{
	for (int i = 0; i < ITEM_AMOUNT; i++)
	{
		if (enemy[i].State != true)
		{
			enemy[i].EnemyGenerate(i, type, move, x, y, 16);
			break;
		}
	}
}
void EnemyClear(void)
{
	for (int i = 0; i < ENEMY_AMOUNT; i++) enemy[i].EnemyDestroy();
}
void EnemyAction(void)
{
	for (int i = 0; i < ENEMY_AMOUNT; i++)
	{
		if (enemy[i].State != true) continue;

		//敵キャラ画像表示
		if (!enemytype[enemy[i].Enemy_Type].boss) DrawRotaGraph(enemy[i].X, enemy[i].Y, 1.0, 0, Enemy_img[enemytype[enemy[i].Enemy_Type].enemyImg], TRUE);
		else 
		{
			if(enemytype[enemy[i].Enemy_Type].enemyImg == 0) DrawRotaGraph(enemy[i].X, enemy[i].Y, 1.0, 0, orivia_img[0], TRUE);//1boss
			else if (enemytype[enemy[i].Enemy_Type].enemyImg == 0) DrawRotaGraph(enemy[i].X, enemy[i].Y, 1.0, 0, orivia_img[0], TRUE);//2boss
		}

		//DrawCircle(X[i], Y[i], HitBoxSize[i], GetColor(255, 0, 0), 1);
		
		enemy[i].EnemyMove();//移動

		//画面内に一度でも入ればtrue
		if (enemy[i].X <= FRAME_WIDTH && enemy[i].X >= 0 && enemy[i].Y <= FRAME_HEIGHT && enemy[i].Y >= 0) enemy[i].Visible = true;
		
		if (enemy[i].Visible)
		{
			if (enemy[i].E_ShotCoolTime >= 0) enemy[i].E_ShotCoolTime--;
			enemy[i].EnemyShotAction();

			//敵とプレイヤーの距離
			enemy[i].Enemy_dist = sqrt(pow((double)enemy[i].X - px, 2) + pow((double)enemy[i].Y - py, 2));
			CheckDistance(i);
			

			//画面外で消滅
			if (enemy[i].Visible && (enemy[i].Y > FRAME_HEIGHT || -20 > enemy[i].X || enemy[i].X > FRAME_WIDTH + 20))
			{
				enemy[i].EnemyDestroy();
				continue;
			}

			if (enemy[i].Enemy_dist <= enemy[i].HitBoxSize + Player_HitBoxSize)
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
				float dis = sqrt(pow((double)enemy[i].X - GetP_BulletPosX(j), 2) + pow((double)enemy[i].Y - GetP_BulletPosY(j), 2));
				if (dis <= enemy[i].HitBoxSize + GetP_BulletHitBoxSize(j))//被弾判定
				{
					DelP_Bullet(j);
					if (enemy[i].HP >= 1)
					{
						Score += 1;
						enemy[i].HP -= 1;
					}
					break;
				}
			}

			if(enemy[i].HP <= 0)//死亡時
			{		
				if (i == Boss && BossStock == 0)
				{
					BossActive = false;
					BossStock = NULL;
					BossMaxHp = NULL;
					BossCurrentHp = NULL;
					Boss = -1;		
					PlaySE(SE_ExplosionB);
				}
				else if (i == Boss && BossStock > 0) //次のターン
				{
					BossStock--;
					enemy[i].HP = enemytype[enemy[i].Enemy_Type].hp;
					BossMaxHp = enemytype[enemy[i].Enemy_Type].hp;
					BossCurrentHp = enemytype[enemy[i].Enemy_Type].hp;
					enemy[i].E_AttackMode = 0;
					enemy[i].E_ShotCoolTime = 0;
					break;
				}
				
				Score += 10;
				ItemSpawn(0, enemy[i].X, enemy[i].Y);//アイテム生成
				enemy[i].EnemyDestroy();
				PlaySE(SE_ExplosionA);
			}
		}
	}
}
int GetBossCurrentHP(void)
{
	return enemy[Boss].HP;
}
int GetBossMaxHP(void)
{
	return BossMaxHp;
}
int GetCloseEnemy_X(void)
{
	return enemy[CloseEnemy].X;
}
int GetCloseEnemy_Y(void)
{
	return enemy[CloseEnemy].Y;
}
int GetCloseEnemyNum(void)
{
	return CloseEnemy;
}

