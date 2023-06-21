#include <DxLib.h>
#include "GameData.h"

void PlayerMove(int* keyState)
{
	int Frame_WIDTH = 580;
	int Frame_HEIGHT = 600;
	const int MOVE_SPEED = 4;
	float slow = 1;
	const int PLAYER_SIZE_X = 12;
	const int PLAYER_SIZE_Y = 24;

	if (keyState[KEY_INPUT_LSHIFT] > 0) slow = 0.5;
	else slow = 1;

	if (keyState[KEY_INPUT_RIGHT] > 0 && px < Frame_WIDTH - PLAYER_SIZE_X) //Œp‘±“ü—Í
	{
		px += (int)MOVE_SPEED * slow;
	}
	if (keyState[KEY_INPUT_LEFT] > 0 && px > 100 + PLAYER_SIZE_X) //Œp‘±“ü—Í
	{
		px -= (int)MOVE_SPEED * slow;
	}
	if (keyState[KEY_INPUT_DOWN] > 0 && py < Frame_HEIGHT - PLAYER_SIZE_Y) //Œp‘±“ü—Í
	{
		py += (int)MOVE_SPEED * slow;
	}
	if (keyState[KEY_INPUT_UP] > 0 && py > 0 + PLAYER_SIZE_Y) //Œp‘±“ü—Í
	{
		py -= (int)MOVE_SPEED * slow;
	}
}