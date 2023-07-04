#pragma once
extern int BGM[];
extern int SE_PlayerShot;
extern int SE_Bomb;

extern int NowPlayBGM;

void AudioInit(void);
void PlayBGM(int music);
void PlaySE(int se);
void BGMVolumeSetting(int newVolume);
void SEVolumeSetting(int newVolume);