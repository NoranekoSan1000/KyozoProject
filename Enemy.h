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

void EnemySpawn(int type, MoveList move, int x, int y);
void CheckDistance(int num);
void EnemyMove(int num);
void EnemyAction(void);
void EnemyShotAction(int num);
void EnemyClear(void);