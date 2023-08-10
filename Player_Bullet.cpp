#include "GameData.h"

#include "Enemy.h"

class PlayerBullet
{
public:
	bool State;
	double X,Y;
	int HitBoxSize;
	int MovePattern;
	double IndivAngle;

	void PlayerBulletGenerate(double x, double y, int hitboxsize, int pattern, double angle)
	{
		State = true;
		X = x;
		Y = y;
		HitBoxSize = hitboxsize;
		MovePattern = pattern;
		IndivAngle = angle;
	}

	void PlayerBulletDestroy()
	{
		State = false;
		X = Y = HitBoxSize = MovePattern = IndivAngle = NULL;
	}

	double AngleCalc(int px, int py)
	{
		EnemyController enemyController;
		double tmp;
		tmp = atan2((enemyController.GetCloseEnemy_Y() + 40.0 - py), (enemyController.GetCloseEnemy_X() - px)); //Enemy.cpp
		return tmp;
	}

	void BulletMove()
	{
		float angle = (3 * PI / 2);//è„ï˚
		float speed = 14;

		switch (MovePattern)
		{
		case 0://íºêi
			X += cos(angle) * speed;
			Y += sin(angle) * speed;
			break;
		case 1://âEéŒÇﬂè¨
			X += cos(angle + 0.15) * speed;
			Y += sin(angle + 0.15) * speed;
			break;
		case 2://ç∂éŒÇﬂè¨
			X += cos(angle - 0.15) * speed;
			Y += sin(angle - 0.15) * speed;
			break;
		case 3://âEéŒÇﬂíÜ
			X += cos(angle + 0.3) * speed;
			Y += sin(angle + 0.3) * speed;
			break;
		case 4://ç∂éŒÇﬂíÜ
			X += cos(angle - 0.3) * speed;
			Y += sin(angle - 0.3) * speed;
			break;
		case 5://ãﬂÇ¢ìGë_Ç¢
			X += cos(IndivAngle) * speed;
			Y += sin(IndivAngle + 0.05) * speed;
			break;
		case 6://ãﬂÇ¢ìGë_Ç¢
			X += cos(IndivAngle) * speed;
			Y += sin(IndivAngle + 0.05) * speed;
			break;
		case 7://ãﬂÇ¢ìGë_Ç¢
			X += cos(IndivAngle) * speed;
			Y += sin(IndivAngle + 0.05) * speed;
			break;
		case 8://íºêi
			X += cos(angle) * speed;
			Y += sin(angle) * speed;
			break;
		case 9://bomb
			X += cos(IndivAngle) * speed;
			Y += sin(IndivAngle) * speed;
			break;
		default:
			break;
		}
	}
};

PlayerBullet p_bullet[PLAYER_BULLET_AMOUNT];

void PlayerBomb(int x, int y)
{
	for (int t = 0; t <= 720; t += (720 / 10))
	{
		for (int i = 0; i < PLAYER_BULLET_AMOUNT; i++)
		{
			if (p_bullet[i].State == false)//ÉVÉáÉbÉgê›íËäiî[èÍèäÇÃãÛÇ´ÇämîF
			{
				p_bullet[i].PlayerBulletGenerate(x, y, 8, 9, PI / 360 * t);
				break;
			}
		}
		
	}
}

void PlayerShot(int px,int py,int type)
{
	EnemyController enemyController;
	double angle;
	for (int i = 0; i < PLAYER_BULLET_AMOUNT; i++)
	{
		if (p_bullet[i].State == false)//ÉVÉáÉbÉgê›íËäiî[èÍèäÇÃãÛÇ´ÇämîF
		{
			PlaySE(SE_PlayerShot); //å¯â âπ
			angle = p_bullet[i].AngleCalc(px,py);

			if (enemyController.GetCloseEnemyNum() == -1 && type == 5) type = 3;	//Enemy.cpp
			if (enemyController.GetCloseEnemyNum() == -1 && type == 6) type = 4;
			if (enemyController.GetCloseEnemyNum() == -1 && type == 7) type = 8;
			p_bullet[i].PlayerBulletGenerate(px, py, 4, type, angle);
			break;
		}
	}
}

void PlayerBulletAction(void)
{
	for (int i = 0; i < PLAYER_BULLET_AMOUNT; i++)
	{
		if (p_bullet[i].State == true) DrawCircle(p_bullet[i].X, p_bullet[i].Y, p_bullet[i].HitBoxSize, GetColor(100, 100, 255), 1);
		else continue;
		
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		if(0 <= p_bullet[i].MovePattern && p_bullet[i].MovePattern <= 2 ) DrawRotaGraph(p_bullet[i].X, p_bullet[i].Y, 1.0, 0, PlayerShot01_img, TRUE);
		else DrawRotaGraph(p_bullet[i].X, p_bullet[i].Y, 1.0, 0, PlayerShot02_img, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 256);

		p_bullet[i].BulletMove();

		//âÊñ äOÇ≈è¡ñ≈
		if (p_bullet[i].Y < -20 || p_bullet[i].Y > FRAME_HEIGHT || 0 > p_bullet[i].X || p_bullet[i].X > FRAME_WIDTH)
		{
			p_bullet[i].PlayerBulletDestroy();
			continue;
		}
	}
}

void PlayerBulletClear(void)
{
	for (int i = 0; i < PLAYER_BULLET_AMOUNT; i++) p_bullet[i].PlayerBulletDestroy();
}

int GetP_BulletPosX(int num)
{
	return p_bullet[num].X;
}
int GetP_BulletPosY(int num)
{
	return p_bullet[num].Y;
}
int GetP_BulletHitBoxSize(int num)
{
	return p_bullet[num].HitBoxSize;
}
void DelP_Bullet(int num)
{
	 p_bullet[num].PlayerBulletDestroy();
}