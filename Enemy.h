#pragma once

//“G
extern bool Enemy_exist[];
extern bool Enemy_visible[];
extern int Enemy_Type[];
extern int Enemy_X[];
extern int Enemy_Y[];
extern int Enemy_HitBoxSize[];
extern int Enemy_MoveSpeed[];
extern int MovePattern[];
extern int Enemy_HP[];
extern float Enemy_dist[];
extern float E_ShotCoolTime[];

extern int CloseEnemy;
extern float CloseDist;

void EnemyGenerate(int num, int type, int x, int y, int hitboxsize, int movespeed, int movepattern, int hp);
void EnemyDestroy(int num);
void EnemySpawn(int pattern);
void CheckDistance(int num);
void EnemyMove(int num);
void EnemyAction(void);
void EnemyShotAction(int num);
void EnemyClear(void);