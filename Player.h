#pragma once
//�v���C���[
extern int InitialPosX;
extern int InitialPosY;
extern int Player_HitBoxSize;
extern int px;
extern int py;
extern int Power;
extern int NextPower[];
extern int Level;
extern int Score;
extern int Life;
extern int Bomb;
extern float BombTime;
extern float DamagedCoolTime;
extern float P_ShotCoolTime;

void PlayerUseBomb(void);
void PlayerShotAction(void);
void LevelUp(void);
void PlayerMove(void);
void ViewPlayer(void);