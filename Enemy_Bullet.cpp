#include "GameData.h"
#include "Player.h"

//“G‚Ì’e
bool E_Bullet_exist[ENEMY_BULLET_AMOUNT];
int E_Bullet_Design[ENEMY_BULLET_AMOUNT];
double E_Bullet_PosX[ENEMY_BULLET_AMOUNT];
double E_Bullet_PosY[ENEMY_BULLET_AMOUNT];
int E_Bullet_HitBoxSize[ENEMY_BULLET_AMOUNT];
int E_Bullet_MovePattern[ENEMY_BULLET_AMOUNT];
double E_Bullet_Angle[ENEMY_BULLET_AMOUNT];

void EnemyBulletGenerate(int num, int design, int x, int y, int hitboxsize, int pattern, double angle)
{
	E_Bullet_exist[num] = true;
	E_Bullet_Design[num] = design;
	E_Bullet_PosX[num] = x;
	E_Bullet_PosY[num] = y;
	E_Bullet_HitBoxSize[num] = hitboxsize;
	E_Bullet_MovePattern[num] = pattern;
	E_Bullet_Angle[num] = angle;
}

void EnemyBulletDestroy(int num)
{
	E_Bullet_exist[num] = false;
	E_Bullet_Design[num] = NULL;
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

void EnemyBulletSpawn(int design, int en_x, int en_y, int size,int pattern,double angle)
{
	for (int i = 0; i < ENEMY_BULLET_AMOUNT; i++)
	{
		if (E_Bullet_exist[i] == false)//ƒVƒ‡ƒbƒgÝ’èŠi”[êŠ‚Ì‹ó‚«‚ðŠm”F
		{
			PlaySE(SE_PlayerShot); //Œø‰Ê‰¹
			EnemyBulletGenerate(i, design, en_x, en_y, size, pattern, angle);
			break;
		}
	}	
}

void EnemyBulletClear(void)
{
	for (int i = 0; i < ENEMY_BULLET_AMOUNT; i++) EnemyBulletDestroy(i);
}

void EnemyShot(int design, EnemyShotPattern type, int en_x, int en_y, int size, int capacity,int arc)
{
	double angle;
	angle = EnemyAngleCalc(en_x, en_y);//Ž©‹@‘_‚¢—p
	if (type == ShotWait) return;//¶¬‚µ‚È‚¢
	else if (type == OneShot) //1”­Ž©‹@‘_‚¢
	{
		EnemyBulletSpawn(design, en_x, en_y, size, 0, -(3 * PI / 2));
	}
	else if (type == AimingOneShot) // ’¼ü‰º
	{
		EnemyBulletSpawn(design, en_x, en_y, size, 0, angle - 0.05);
	}
	else if (type == Explosion) // ”š”­
	{
		for (int t = 0; t < 720; t += (720 / capacity))
		{
			EnemyBulletSpawn(design, en_x, en_y, size, 0, PI / 360 * t);
		}	
	}
	else if (type == AimingExplosion) // Ž©‹@‘_‚¢”š”­
	{
		for (int t = -360; t < 360; t += (720 / capacity))
		{
			EnemyBulletSpawn(design, en_x, en_y, size, 0, angle + PI / 360 * t);
		}
	}
	else if (type == Diffusion) // ŽU’e
	{
		for (int t = -arc; t < arc; t += (arc * 2 / capacity))
		{
			EnemyBulletSpawn(design, en_x, en_y, size, 0, -(3 * PI / 2) + PI / 360 * t);
		}
	}
	else if (type == AimingDiffusion) // Ž©‹@‘_‚¢ŽU’e		Œ©‰h‚¦‚ªˆ«‚¢‚Ì‚ÅŠï”„§I
	{
		for (int t = -arc; t < arc; t += (arc * 2 / capacity))
		{
			EnemyBulletSpawn(design, en_x, en_y, size, 0, angle + PI / 360 * t);
		}
	}
}

void EnemyBulletMove(int num)
{
	float angle = (PI / 2);//‰º•û
	float speed = 6;

	switch (E_Bullet_MovePattern[num])
	{
	case 0://^’¼‚®
		E_Bullet_PosX[num] += cos(E_Bullet_Angle[num]) * speed;
		E_Bullet_PosY[num] += sin(E_Bullet_Angle[num]) * speed;
		break;
	case 1://ƒEƒF[ƒui‰¼j

		break;
	default:
		break;
	}
}

void EnemyBulletHit(int num)
{
	//’e‚ÆƒvƒŒƒCƒ„[‚ªÚG
	double dis = sqrt(pow((double)px - E_Bullet_PosX[num], 2) + pow((double)py - E_Bullet_PosY[num], 2));
	if (dis <= E_Bullet_HitBoxSize[num] + Player_HitBoxSize)//”í’e”»’è
	{
		//”í’e”»’è
		if (DamagedCoolTime <= 0)
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

}


void EnemyBulletAction(void)
{

	for (int i = 0; i < ENEMY_BULLET_AMOUNT; i++)
	{

		if (E_Bullet_exist[i] == true) DrawCircle((int)E_Bullet_PosX[i], (int)E_Bullet_PosY[i], E_Bullet_HitBoxSize[i], GetColor(100, 100, 255), 1);
		else continue;

		DrawRotaGraph((int)E_Bullet_PosX[i], (int)E_Bullet_PosY[i], 1.0, 0, EnemyShot_img[E_Bullet_Design[i]], TRUE);//‰æ‘œ

		EnemyBulletMove(i);
		EnemyBulletHit(i);

		//‰æ–ÊŠO‚ÅÁ–Å
		if (E_Bullet_PosY[i] < -20 || E_Bullet_PosY[i] > FRAME_HEIGHT || 0 > E_Bullet_PosX[i] ||E_Bullet_PosX[i] > FRAME_WIDTH)
		{
			EnemyBulletDestroy(i);
			continue;
		}

	}
}

