#pragma once
//�v���C���[
extern int InitialPosX;
extern int InitialPosY;
extern int Player_HitBoxSize;
extern int px;
extern int py;
extern int Score;
extern int Life;
extern float DamagedCoolTime;

void PlayerMove(int* keyState);
void ViewPlayer(void);