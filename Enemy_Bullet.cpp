#include "GameData.h"
#include "Player.h"


//“G‚Ì’e
bool E_Bullet_exist[ENEMY_BULLET_AMOUNT];
int E_Bullet_Type[ENEMY_AMOUNT];//‰æ‘œ—p
int E_Bullet_PosX[ENEMY_BULLET_AMOUNT];
int E_Bullet_PosY[ENEMY_BULLET_AMOUNT];
int E_Bullet_HitBoxSize[ENEMY_BULLET_AMOUNT];
int E_Bullet_MovePattern[ENEMY_BULLET_AMOUNT];
float E_Bullet_Angle[ENEMY_BULLET_AMOUNT];

void EnemyBulletGenerate(int num, int type, int x, int y, int hitboxsize, int pattern, float angle)
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

float EnemyAngleCalc(int en_x, int en_y)
{
	float tmp;
	tmp = (float)atan2((py - en_y), (px - en_x));
	return tmp;
}

void EnemyBulletSpawn(int type, int en_x, int en_y, int size,int pattern,float angle)
{
	for (int i = 0; i < ENEMY_BULLET_AMOUNT; i++)
	{
		if (E_Bullet_exist[i] == false)//ƒVƒ‡ƒbƒgÝ’èŠi”[êŠ‚Ì‹ó‚«‚ðŠm”F
		{
			PlaySE(SE_PlayerShot); //Œø‰Ê‰¹
			EnemyBulletGenerate(i, type, en_x, en_y, size, pattern, angle);
			break;
		}
	}	
}

void EnemyShot(int type, int en_x, int en_y)
{
	float angle;
	angle = EnemyAngleCalc(en_x, en_y);//Ž©‹@‘_‚¢—p
	if (type == 0) return;//¶¬‚µ‚È‚¢
	else if (type == 1) //1”­Ž©‹@‘_‚¢
	{
		EnemyBulletSpawn(type, en_x, en_y, 4, 0, angle - 0.05);
	}
	else if (type == 2) // ’¼ü‰º
	{
		EnemyBulletSpawn(type, en_x, en_y, 4, 0, -(3 * PI / 2));
	}
	else if (type == 3) // ”š”­
	{
		EnemyBulletSpawn(type, en_x, en_y, 4, 0, -(3 * PI / 2));
		EnemyBulletSpawn(type, en_x, en_y, 4, 0, -((3 * PI / 2)/2));
		EnemyBulletSpawn(type, en_x, en_y, 4, 0, +(3 * PI / 2));		//’l‚ð•\Ž¦‚µ‚Ä/ŒvŽZ‚·‚é
		EnemyBulletSpawn(type, en_x, en_y, 4, 0, +((3 * PI / 2) / 2));
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
	float dis = sqrt(pow((double)px - E_Bullet_PosX[num], 2) + pow((double)py - E_Bullet_PosY[num], 2));
	if (dis <= E_Bullet_HitBoxSize[num] + Player_HitBoxSize)//”í’e”»’è
	{
		EnemyBulletDestroy(num);
		if (Life > 0)
		{
			//”í’e”»’è
			if (DamagedCoolTime <= 0)
			{
				px = InitialPosX;
				py = InitialPosY;
				Life -= 1;
				DamagedCoolTime = 120;
			}
		}
	}

}


void EnemyBulletAction(void)
{

	for (int i = 0; i < ENEMY_BULLET_AMOUNT; i++)
	{

		if (E_Bullet_exist[i] == true) DrawCircle(E_Bullet_PosX[i], E_Bullet_PosY[i], E_Bullet_HitBoxSize[i], GetColor(100, 100, 255), 1);
		else continue;

		DrawRotaGraph(E_Bullet_PosX[i], E_Bullet_PosY[i], 1.0, 0, EnemyShot01_img, TRUE);//‰æ‘œ

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

void EnemyBulletClear(void)
{
	for (int i = 0; i < ENEMY_BULLET_AMOUNT; i++) EnemyBulletDestroy(i);
}