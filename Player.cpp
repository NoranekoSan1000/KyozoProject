#include "GameData.h"
#define PLAYER_SIZE_X 12
#define PLAYER_SIZE_Y 24

//プレイヤー
int InitialPosX = 325;
int InitialPosY = 675;
int Player_HitBoxSize = 4;
int px = InitialPosX;
int py = InitialPosY;
int Power = 0;
int NextPower[3] = { 20, 60, 120 };//LevelUpに必要なPower
int Level = 2;
int Score = 0;
int Life = 10;
float DamagedCoolTime = 0;
float P_ShotCoolTime = 0;

void PlayerMove(void)
{
	int MOVE_SPEED = 5;
	
	if (KeyState[KEY_INPUT_LSHIFT] > 0) MOVE_SPEED = 2;
	else MOVE_SPEED = 5;

	if (KeyState[KEY_INPUT_RIGHT] > 0 && px < FRAME_WIDTH - PLAYER_SIZE_X) //継続入力
	{
		px += (int)MOVE_SPEED;
	}
	if (KeyState[KEY_INPUT_LEFT] > 0 && px > 25 + PLAYER_SIZE_X) //継続入力
	{
		px -= (int)MOVE_SPEED;
	}
	if (KeyState[KEY_INPUT_DOWN] > 0 && py < FRAME_HEIGHT - PLAYER_SIZE_Y) //継続入力
	{
		py += (int)MOVE_SPEED;
	}
	if (KeyState[KEY_INPUT_UP] > 0 && py > 25 + PLAYER_SIZE_Y) //継続入力
	{
		py -= (int)MOVE_SPEED;
	}
}

void ViewPlayer(void)
{
	PlayerMove();//プレイヤーの移動

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawCircle(px, py, DamagedCoolTime, GetColor(100, 100, 255)); // 被弾クールタイム中
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 256);
	DrawRotaGraph(px, py, 1.0, 0, player_img, TRUE); //プレイヤー画像の描画
	DrawCircle(px, py, Player_HitBoxSize, GetColor(255, 255, 80)); // プレイヤーの当たり判定表示
}
