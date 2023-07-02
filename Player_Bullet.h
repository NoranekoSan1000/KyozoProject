#pragma once

//ÉvÉåÉCÉÑÅ[ÇÃíe
extern bool P_Bullet_exist[];
extern double P_Bullet_PosX[];
extern double P_Bullet_PosY[];
extern int P_Bullet_HitBoxSize[];
extern int P_Bullet_MovePattern[];
extern float P_Bullet_Angle[];

void PlayerBulletGenerate(int num, int x, int y, int hitboxsize, int pattern, float angle);
void PlayerBulletDestroy(int num);
void PlayerShot(int px, int py, int type);
void BulletMove(int num);
void PlayerBulletAction(void);
void PlayerBulletClear(void);