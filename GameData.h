#pragma once
#define ENEMY_AMOUNT 20
#define PLAYER_BULLET_AMOUNT 50
//プレイヤー
extern int InitialPosX;
extern int InitialPosY;
extern int Player_HitBoxSize;
extern int px;
extern int py;
extern int Score;
extern int Life;

//プレイヤーの弾
extern bool P_Bullet_exist[];
extern int P_Bullet_PosX[];
extern int P_Bullet_PosY[];
extern int P_Bullet_HitBoxSize[];
extern float P_ShotCoolTime;

//敵
extern bool Enemy_exist[];
extern int Enemy_X[];
extern int Enemy_Y[];
extern int Enemy_HitBoxSize[];
extern int Enemy_MoveSpeed[];
extern int MovePattern[];