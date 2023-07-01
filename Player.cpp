#include "GameData.h"
#include "Player_Bullet.h"
#define PLAYER_SIZE_X 12
#define PLAYER_SIZE_Y 24

//vC[
int InitialPosX = 325;
int InitialPosY = 675;
int Player_HitBoxSize = 4;
int px = InitialPosX;
int py = InitialPosY;
int Power = 100;
int NextPower[3] = { 10, 40, 100 };//LevelUpÉKvÈPower
int Level = 3;
int Score = 0;
int Life = 3;
float DamagedCoolTime = 0;
float P_ShotCoolTime = 0;

void PlayerShotAction(void)
{
	if (KeyState[KEY_INPUT_Z] > 0)
	{
		if (P_ShotCoolTime > 0) return;
		if (Level >= 0)
		{
			PlayerShot(px, py - 8, 0);//Ë
		}
		if (Level >= 1 && Level < 3)//_¢Lv1
		{
			PlayerShot(px, py + 20, 7);//Ë
		}
		if (Level >= 2)
		{
			PlayerShot(px, py - 4, 1);//Ë
			PlayerShot(px, py - 4, 2);//Ë
		}
		if (Level >= 3)//_¢Lv2
		{
			PlayerShot(px + 8, py + 8, 5);//Ë
			PlayerShot(px - 8, py + 8, 6);//Ë
		}
		P_ShotCoolTime = 8;//t[ÅÝè
	}
}

void LevelUp(void)
{
	if (Power < NextPower[0])
	{
		Level = 0;
	}
	else if (Power >= NextPower[0] && Power < NextPower[1])
	{
		Level = 1;
	}
	else if (Power >= NextPower[1] && Power < NextPower[2])
	{
		Level = 2;
	}
	else Level = 3;
}

void PlayerMove(void)
{
	int MOVE_SPEED = 5;
	
	if (KeyState[KEY_INPUT_LSHIFT] > 0) MOVE_SPEED = 2;
	else MOVE_SPEED = 5;

	if (KeyState[KEY_INPUT_RIGHT] > 0 && px < FRAME_WIDTH - PLAYER_SIZE_X) //p±üÍ
	{
		px += (int)MOVE_SPEED;
	}
	if (KeyState[KEY_INPUT_LEFT] > 0 && px > 25 + PLAYER_SIZE_X) //p±üÍ
	{
		px -= (int)MOVE_SPEED;
	}
	if (KeyState[KEY_INPUT_DOWN] > 0 && py < FRAME_HEIGHT - PLAYER_SIZE_Y) //p±üÍ
	{
		py += (int)MOVE_SPEED;
	}
	if (KeyState[KEY_INPUT_UP] > 0 && py > 25 + PLAYER_SIZE_Y) //p±üÍ
	{
		py -= (int)MOVE_SPEED;
	}
}

void ViewPlayer(void)
{
	PlayerMove();//vC[ÌÚ®

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawCircle(px, py, DamagedCoolTime, GetColor(100, 100, 255)); // íeN[^C
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 256);
	DrawRotaGraph(px, py, 1.0, 0, player_img, TRUE); //vC[æÌ`æ
	DrawCircle(px, py, Player_HitBoxSize, GetColor(255, 255, 80)); // vC[Ì½è»è\¦
}
