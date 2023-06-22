#pragma once

//ÉvÉåÉCÉÑÅ[ÇÃíe
extern bool P_Bullet_exist[];
extern int P_Bullet_PosX[];
extern int P_Bullet_PosY[];
extern int P_Bullet_HitBoxSize[];
extern float P_ShotCoolTime;

void PlayerBulletGenerate(int num, int x, int y, int hitboxsize);
void PlayerBulletDestroy(int num);
void PlayerShotGenerate(int px, int py);
void PlayerBulletAction(void);