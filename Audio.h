#pragma once
extern int BGM[];
extern int SE_PlayerShot;
extern int SE_Bomb;

extern int NowPlayBGM;

extern int BGMCurrentVolume;
extern int SECurrentVolume;

void AudioInit(void);
void PlayBGM(int music);
void PlaySE(int se);
