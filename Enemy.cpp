#include <stdio.h>
#define ENEMY_AMOUNT 20
//“G
int Enemy_Amount = ENEMY_AMOUNT;
bool exist[ENEMY_AMOUNT];
int enX[ENEMY_AMOUNT];
int enY[ENEMY_AMOUNT];
int enHitBoxSize[ENEMY_AMOUNT];
int moveSpeed[ENEMY_AMOUNT];

void EnemyGenerate(int num, int x, int y, int hitboxsize, int movespeed)
{
	exist[num] = true;
	enX[num] = x;
	enY[num] = y;
	enHitBoxSize[num] = hitboxsize;
	moveSpeed[num] = movespeed;
}

void EnemyDestroy(int num)
{
	exist[num] = false;
	enX[num] = NULL;
	enY[num] = NULL;
	enHitBoxSize[num] = NULL;
	moveSpeed[num] = NULL;
}
