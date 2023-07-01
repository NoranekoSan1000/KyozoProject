#include "GameData.h"
#include "Player.h"


//敵の弾
bool E_Bullet_exist[ENEMY_BULLET_AMOUNT];
int E_Bullet_Type[ENEMY_BULLET_AMOUNT];//画像用
double E_Bullet_PosX[ENEMY_BULLET_AMOUNT];
double E_Bullet_PosY[ENEMY_BULLET_AMOUNT];
int E_Bullet_HitBoxSize[ENEMY_BULLET_AMOUNT];
int E_Bullet_MovePattern[ENEMY_BULLET_AMOUNT];
double E_Bullet_Angle[ENEMY_BULLET_AMOUNT];

void EnemyBulletGenerate(int num, int type, int x, int y, int hitboxsize, int pattern, double angle)
{
	E_Bullet_exist[num] = true;
	E_Bullet_Type[num] = type;
	E_Bullet_PosX[num] = x;
	E_Bullet_PosY[num] = y;
	E_Bullet_HitBoxSize[num] = hitboxsize;
	E_Bullet_MovePattern[num] = pattern;
	E_Bullet_Angle[num] = angle;
}

void EnemyBulletDestroy(int num)
{
	E_Bullet_exist[num] = false;
	E_Bullet_Type[num] = NULL;
	E_Bullet_PosX[num] = NULL;
	E_Bullet_PosY[num] = NULL;
	E_Bullet_HitBoxSize[num] = NULL;
	E_Bullet_MovePattern[num] = NULL;
	E_Bullet_Angle[num] = NULL;
}

double  EnemyAngleCalc(int en_x, int en_y)
{
	double tmp;
	tmp = (double)atan2((py - en_y), (px - en_x));
	return tmp;
}

void EnemyBulletSpawn(int type, int en_x, int en_y, int size,int pattern,double angle)
{
	for (int i = 0; i < ENEMY_BULLET_AMOUNT; i++)
	{
		if (E_Bullet_exist[i] == false)//ショット設定格納場所の空きを確認
		{
			PlaySE(SE_PlayerShot); //効果音
			EnemyBulletGenerate(i, type, en_x, en_y, size, pattern, angle);
			break;
		}
	}	
}

void EnemyBulletClear(void)
{
	for (int i = 0; i < ENEMY_BULLET_AMOUNT; i++) EnemyBulletDestroy(i);
}

void EnemyShot(int type, int en_x, int en_y)
{
	double angle;
	angle = EnemyAngleCalc(en_x, en_y);//自機狙い用
	if (type == 0) return;//生成しない
	else if (type == 1) //1発自機狙い
	{
		EnemyBulletSpawn(type, en_x, en_y, 4, 0, angle - 0.05);
	}
	else if (type == 2) // 直線下
	{
		EnemyBulletSpawn(type, en_x, en_y, 4, 0, -(3 * PI / 2));
	}
	else if (type == 3) // 爆発
	{
		for (int t = 0; t < 720; t += 40)
		{
			EnemyBulletSpawn(type, en_x, en_y, 4, 0, PI / 360 * t);
		}	
	}
	else if (type == 3) // 自機狙い爆発
	{
		for (int t = -360; t < 360; t += 10)
		{
			EnemyBulletSpawn(type, en_x, en_y, 4, 0, angle + PI / 360 * t);
		}
	}
	else if (type == 4) // 散弾
	{
		for (int t = -90; t < 90; t += 10)
		{
			EnemyBulletSpawn(type, en_x, en_y, 4, 0, -(3 * PI / 2) + PI / 360 * t);
		}
	}
	else if (type == 5) // 自機狙い散弾
	{
		for (int t = -90; t < 90; t += 10)
		{
			EnemyBulletSpawn(type, en_x, en_y, 4, 0, angle + PI / 360 * t);
		}
	}
}

void EnemyBulletMove(int num)
{
	float angle = (PI / 2);//下方
	float speed = 6;

	switch (E_Bullet_MovePattern[num])
	{
	case 0://真直ぐ
		E_Bullet_PosX[num] += cos(E_Bullet_Angle[num]) * speed;
		E_Bullet_PosY[num] += sin(E_Bullet_Angle[num]) * speed;
		break;
	case 1://ウェーブ（仮）

		break;
	default:
		break;
	}
}

void EnemyBulletHit(int num)
{
	//弾とプレイヤーが接触
	double dis = sqrt(pow((double)px - E_Bullet_PosX[num], 2) + pow((double)py - E_Bullet_PosY[num], 2));
	if (dis <= E_Bullet_HitBoxSize[num] + Player_HitBoxSize)//被弾判定
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

}


void EnemyBulletAction(void)
{

	for (int i = 0; i < ENEMY_BULLET_AMOUNT; i++)
	{

		if (E_Bullet_exist[i] == true) DrawCircle((int)E_Bullet_PosX[i], (int)E_Bullet_PosY[i], E_Bullet_HitBoxSize[i], GetColor(100, 100, 255), 1);
		else continue;

		DrawRotaGraph((int)E_Bullet_PosX[i], (int)E_Bullet_PosY[i], 1.0, 0, EnemyShot01_img, TRUE);//画像

		EnemyBulletMove(i);
		EnemyBulletHit(i);

		//画面外で消滅
		if (E_Bullet_PosY[i] < -20 || E_Bullet_PosY[i] > FRAME_HEIGHT || 0 > E_Bullet_PosX[i] ||E_Bullet_PosX[i] > FRAME_WIDTH)
		{
			EnemyBulletDestroy(i);
			continue;
		}

	}
}

