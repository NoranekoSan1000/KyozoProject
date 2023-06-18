#include <DxLib.h>
//ƒvƒŒƒCƒ„[
int InitialPosX = 350;
int InitialPosY = 550;
int Player_HitBoxSize = 4;
int px = InitialPosX;
int py = InitialPosY;

int Score = 0;
int Life = 10;


void PlayerMove(int* keyState)
{
	int WINDOW_WIDTH = 580;
	int WINDOW_HEIGHT = 600;
	const int MOVE_SPEED = 4;
	float slow = 1;
	const int PLAYER_SIZE_X = 12;
	const int PLAYER_SIZE_Y = 24;

	if (keyState[KEY_INPUT_LSHIFT] > 0) slow = 0.5;
	else slow = 1;

	if (keyState[KEY_INPUT_RIGHT] > 0 && px < WINDOW_WIDTH - PLAYER_SIZE_X) //Œp‘±“ü—Í
	{
		px += (int)MOVE_SPEED * slow;
	}
	if (keyState[KEY_INPUT_LEFT] > 0 && px > 100 + PLAYER_SIZE_X) //Œp‘±“ü—Í
	{
		px -= (int)MOVE_SPEED * slow;
	}
	if (keyState[KEY_INPUT_DOWN] > 0 && py < WINDOW_HEIGHT - PLAYER_SIZE_Y) //Œp‘±“ü—Í
	{
		py += (int)MOVE_SPEED * slow;
	}
	if (keyState[KEY_INPUT_UP] > 0 && py > 0 + PLAYER_SIZE_Y) //Œp‘±“ü—Í
	{
		py -= (int)MOVE_SPEED * slow;
	}
}