#include <stdio.h>
#include "GameData.h"

void PlayerBulletGenerate(int num, int x, int y, int hitboxsize)
{
	P_Bullet_exist[num] = true;
	P_Bullet_PosX[num] = x;
	P_Bullet_PosY[num] = y;
	P_Bullet_HitBoxSize[num] = hitboxsize;
}

void PlayerBulletDestroy(int num)
{
	P_Bullet_exist[num] = false;
	P_Bullet_PosX[num] = NULL;
	P_Bullet_PosY[num] = NULL;
	P_Bullet_HitBoxSize[num] = NULL;
}

void PlayerShotGenerate(int px,int py)
{
	if (P_ShotCoolTime > 0) return;
	for (int i = 0; i < PLAYER_BULLET_AMOUNT; i++)
	{
		if (P_Bullet_exist[i] == false)//ショット設定格納場所の空きを確認
		{
			PlayerBulletGenerate(i, px, py, 6);
			P_ShotCoolTime = 10;//フレームで設定
			break;
		}
	}
}