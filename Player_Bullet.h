#pragma once

//ÉvÉåÉCÉÑÅ[ÇÃíe
extern bool P_Bullet_exist[];
extern int P_Bullet_PosX[];
extern int P_Bullet_PosY[];
extern int P_Bullet_HitBoxSize[];

void PlayerBulletGenerate(int num, int x, int y, int hitboxsize, int pattern);
void PlayerBulletDestroy(int num);
void PlayerShot(int px, int py, int type);
void BulletMove(int num);
void PlayerBulletAction(void);