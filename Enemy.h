#pragma once

//“G
extern bool Enemy_exist[];
extern int Enemy_X[];
extern int Enemy_Y[];
extern int Enemy_HitBoxSize[];
extern int Enemy_MoveSpeed[];
extern int MovePattern[];
extern int Enemy_HP[];

void EnemyGenerate(int num, int x, int y, int hitboxsize, int movespeed, int movepattern, int hp);
void EnemyDestroy(int num);
void EnemySpawn(void);
void EnemyMove(int num);
void EnemyAction(void);