#include "GameData.h"
#include "Enemy.h"

//ÉvÉåÉCÉÑÅ[ÇÃíe
bool P_Bullet_exist[PLAYER_BULLET_AMOUNT];
int P_Bullet_PosX[PLAYER_BULLET_AMOUNT];
int P_Bullet_PosY[PLAYER_BULLET_AMOUNT];
int P_Bullet_HitBoxSize[PLAYER_BULLET_AMOUNT];
int P_Bullet_MovePattern[PLAYER_BULLET_AMOUNT];
float P_Bullet_Angle[PLAYER_BULLET_AMOUNT];

void PlayerBulletGenerate(int num, int x, int y, int hitboxsize, int pattern,float angle)
{
	P_Bullet_exist[num] = true;
	P_Bullet_PosX[num] = x;
	P_Bullet_PosY[num] = y;
	P_Bullet_HitBoxSize[num] = hitboxsize;
	P_Bullet_MovePattern[num] = pattern;
	P_Bullet_Angle[num] = angle;
}

void PlayerBulletDestroy(int num)
{
	P_Bullet_exist[num] = false;
	P_Bullet_PosX[num] = NULL;
	P_Bullet_PosY[num] = NULL;
	P_Bullet_HitBoxSize[num] = NULL;
	P_Bullet_MovePattern[num] = NULL;
	P_Bullet_Angle[num] = NULL;
}

float AngleCalc(int px, int py)
{
	float tmp;
	tmp = (float)atan2((Enemy_Y[CloseEnemy] + 40 - py), (Enemy_X[CloseEnemy] - px));
	return tmp;
}

void PlayerShot(int px,int py,int type)
{
	float angle;
	for (int i = 0; i < PLAYER_BULLET_AMOUNT; i++)
	{
		if (P_Bullet_exist[i] == false)//ÉVÉáÉbÉgê›íËäiî[èÍèäÇÃãÛÇ´ÇämîF
		{
			PlaySE(SE_PlayerShot); //å¯â âπ
			angle = AngleCalc(px,py);

			if (CloseEnemy == -1 && type == 5) type = 3;
			if (CloseEnemy == -1 && type == 6) type = 4;
			PlayerBulletGenerate(i, px, py, 4, type, angle);
			break;
		}
	}
}

void BulletMove(int num)
{
	float angle = (3 * PI / 2);//è„ï˚
	float speed = 14;

	switch (P_Bullet_MovePattern[num])
	{
	case 0://íºêi
		P_Bullet_PosX[num] += cos(angle) * speed;
		P_Bullet_PosY[num] += sin(angle) * speed;
		break;
	case 1://âEéŒÇﬂè¨
		P_Bullet_PosX[num] += cos(angle + 0.15) * speed;
		P_Bullet_PosY[num] += sin(angle + 0.15) * speed;
		break;
	case 2://ç∂éŒÇﬂè¨
		P_Bullet_PosX[num] += cos(angle - 0.10) * speed;
		P_Bullet_PosY[num] += sin(angle - 0.10) * speed;
		break;
	case 3://âEéŒÇﬂíÜ
		P_Bullet_PosX[num] += cos(angle + 0.3) * speed;
		P_Bullet_PosY[num] += sin(angle + 0.3) * speed;
		break;
	case 4://ç∂éŒÇﬂíÜ
		P_Bullet_PosX[num] += cos(angle - 0.25) * speed;
		P_Bullet_PosY[num] += sin(angle - 0.25) * speed;
		break;
	case 5://ãﬂÇ¢ìGë_Ç¢
		P_Bullet_PosX[num] += cos(P_Bullet_Angle[num] + 0.05) * speed;
		P_Bullet_PosY[num] += sin(P_Bullet_Angle[num] + 0.05) * speed;
		break;
	case 6://ãﬂÇ¢ìGë_Ç¢
		P_Bullet_PosX[num] += cos(P_Bullet_Angle[num] + 0.05) * speed;
		P_Bullet_PosY[num] += sin(P_Bullet_Angle[num] + 0.05) * speed;
		break;
	default:
		break;
	}
}

void PlayerBulletAction(void)
{
	for (int i = 0; i < PLAYER_BULLET_AMOUNT; i++)
	{
		if (P_Bullet_exist[i] == true) DrawCircle(P_Bullet_PosX[i], P_Bullet_PosY[i], P_Bullet_HitBoxSize[i], GetColor(100, 100, 255), 1);
		else continue;
		
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		if(0 <= P_Bullet_MovePattern[i] && P_Bullet_MovePattern[i] <= 2 ) DrawRotaGraph(P_Bullet_PosX[i], P_Bullet_PosY[i], 1.0, 0, PlayerShot01_img, TRUE);
		else DrawRotaGraph(P_Bullet_PosX[i], P_Bullet_PosY[i], 1.0, 0, PlayerShot02_img, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 256);

		BulletMove(i);

		//âÊñ äOÇ≈è¡ñ≈
		if (P_Bullet_PosY[i] < -20 || P_Bullet_PosY[i] > FRAME_HEIGHT || 0 > P_Bullet_PosX[i] || P_Bullet_PosX[i] > FRAME_WIDTH)
		{
			PlayerBulletDestroy(i);
			continue;
		}
	}
}

void PlayerBulletClear(void)
{
	for (int i = 0; i < PLAYER_BULLET_AMOUNT; i++) PlayerBulletDestroy(i);
}