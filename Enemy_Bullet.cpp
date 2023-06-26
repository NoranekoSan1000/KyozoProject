#include "GameData.h"
#include "Player.h"


//ìGÇÃíe
bool E_Bullet_exist[ENEMY_BULLET_AMOUNT];
int E_Bullet_PosX[ENEMY_BULLET_AMOUNT];
int E_Bullet_PosY[ENEMY_BULLET_AMOUNT];
int E_Bullet_HitBoxSize[ENEMY_BULLET_AMOUNT];
int E_Bullet_MovePattern[ENEMY_BULLET_AMOUNT];
float E_Bullet_Angle[ENEMY_BULLET_AMOUNT];

void EnemyBulletGenerate(int num, int x, int y, int hitboxsize, int pattern, float angle)
{
	E_Bullet_exist[num] = true;
	E_Bullet_PosX[num] = x;
	E_Bullet_PosY[num] = y;
	E_Bullet_HitBoxSize[num] = hitboxsize;
	E_Bullet_MovePattern[num] = pattern;
	E_Bullet_Angle[num] = angle;
}

void EnemyBulletDestroy(int num)
{
	E_Bullet_exist[num] = false;
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

void EnemyShot(int en_x, int en_y, int size, int type)
{

	if (type == 0) return;//ê∂ê¨ÇµÇ»Ç¢
	float angle;
	for (int i = 0; i < ENEMY_BULLET_AMOUNT; i++)
	{
		if (E_Bullet_exist[i] == false)//ÉVÉáÉbÉgê›íËäiî[èÍèäÇÃãÛÇ´ÇämîF
		{
			PlaySE(SE_PlayerShot); //å¯â âπ
			angle = EnemyAngleCalc(en_x, en_y);
			EnemyBulletGenerate(i, en_x, en_y, size, type, angle);
			break;
		}
	}
}

void EnemyBulletMove(int num)
{
	float angle = (PI / 2);//â∫ï˚
	float speed = 12;

	switch (E_Bullet_MovePattern[num])
	{
	case 0:
		break;
	case 1://âEéŒÇﬂè¨
		E_Bullet_PosX[num] += cos(angle - 0.05) * speed;
		E_Bullet_PosY[num] += sin(angle - 0.05) * speed;
		break;
	case 2://ç∂éŒÇﬂè¨
		E_Bullet_PosX[num] += cos(angle - 0.10) * speed;
		E_Bullet_PosY[num] += sin(angle - 0.10) * speed;
		break;
	case 3://âEéŒÇﬂíÜ
		E_Bullet_PosX[num] += cos(angle + 0.3) * speed;
		E_Bullet_PosY[num] += sin(angle + 0.3) * speed;
		break;
	case 4://ç∂éŒÇﬂíÜ
		E_Bullet_PosX[num] += cos(angle - 0.25) * speed;
		E_Bullet_PosY[num] += sin(angle - 0.25) * speed;
		break;
	case 5://ãﬂÇ¢ìGë_Ç¢
		E_Bullet_PosX[num] += cos(E_Bullet_Angle[num]- 0.05) * speed;
		E_Bullet_PosY[num] += sin(E_Bullet_Angle[num]- 0.05) * speed;
		break;
	default:
		break;
	}
}

void EnemyBulletHit(int num)
{
	//íeÇ∆ÉvÉåÉCÉÑÅ[Ç™ê⁄êG
	float dis = sqrt(pow((double)px - E_Bullet_PosX[num], 2) + pow((double)py - E_Bullet_PosY[num], 2));
	if (dis <= E_Bullet_HitBoxSize[num] + Player_HitBoxSize)//îÌíeîªíË
	{
		EnemyBulletDestroy(num);
		if (Life > 0)
		{
			//îÌíeîªíË
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

		DrawRotaGraph(E_Bullet_PosX[i], E_Bullet_PosY[i], 1.0, 0, PlayerShot01_img, TRUE);//âÊëú

		EnemyBulletMove(i);
		EnemyBulletHit(i);

		//âÊñ äOÇ≈è¡ñ≈
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