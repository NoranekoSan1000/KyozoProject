#include <DxLib.h>

void PlayerMove(int* keyState, int* player_x, int* player_y)
{
	int WINDOW_WIDTH = 580;
	int WINDOW_HEIGHT = 600;
	const int MOVE_SPEED = 4;
	float slow = 1;
	const int PLAYER_SIZE_X = 12;
	const int PLAYER_SIZE_Y = 24;

	if (keyState[KEY_INPUT_LSHIFT] > 0) slow = 0.5;
	else slow = 1;

	if (keyState[KEY_INPUT_RIGHT] > 0 && *player_x < WINDOW_WIDTH - PLAYER_SIZE_X) //Œp‘±“ü—Í
	{
		*player_x += (int)MOVE_SPEED * slow;
	}
	if (keyState[KEY_INPUT_LEFT] > 0 && *player_x > 100 + PLAYER_SIZE_X) //Œp‘±“ü—Í
	{
		*player_x -= (int)MOVE_SPEED * slow;
	}
	if (keyState[KEY_INPUT_DOWN] > 0 && *player_y < WINDOW_HEIGHT - PLAYER_SIZE_Y) //Œp‘±“ü—Í
	{
		*player_y += (int)MOVE_SPEED * slow;
	}
	if (keyState[KEY_INPUT_UP] > 0 && *player_y > 0 + PLAYER_SIZE_Y) //Œp‘±“ü—Í
	{
		*player_y -= (int)MOVE_SPEED * slow;
	}
}