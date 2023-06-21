#include <stdio.h>
#define ENEMY_AMOUNT 20
//�G
int Enemy_Amount = ENEMY_AMOUNT;
bool Enemy_exist[ENEMY_AMOUNT];
int Enemy_X[ENEMY_AMOUNT];
int Enemy_Y[ENEMY_AMOUNT];
int Enemy_HitBoxSize[ENEMY_AMOUNT];
int Enemy_MoveSpeed[ENEMY_AMOUNT];
int MovePattern[ENEMY_AMOUNT];

void EnemyGenerate(int num, int x, int y, int hitboxsize, int movespeed, int movepattern)
{
	Enemy_exist[num] = true;
	Enemy_X[num] = x;
	Enemy_Y[num] = y;
	Enemy_HitBoxSize[num] = hitboxsize;
	Enemy_MoveSpeed[num] = movespeed;
	MovePattern[num] = movepattern;
}

void EnemyDestroy(int num)
{
	Enemy_exist[num] = false;
	Enemy_X[num] = NULL;
	Enemy_Y[num] = NULL;
	Enemy_HitBoxSize[num] = NULL;
	Enemy_MoveSpeed[num] = NULL;
	MovePattern[num] = NULL;
}

void EnemyMove(int num)//�ޏ�
{
	switch (MovePattern[num])
	{
	case 0://���i
		Enemy_Y[num] += Enemy_MoveSpeed[num];
		break;
	default:
		break;
	}
	
}