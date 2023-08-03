#pragma once
extern int BGM[];
extern int SE_PlayerShot;
extern int SE_Bomb;
extern int SE_ExplosionA;
extern int SE_ExplosionB;

extern int NowPlayBGM;

extern int BGMCurrentVolume;
extern int SECurrentVolume;

void AudioInit(void);
void PlayBGM(int music);
void PlaySE(int se);

void volumeSetBGM(void);