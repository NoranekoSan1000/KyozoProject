#pragma once
extern int ResonanceAtTwilight_audio;
extern int SE_PlayerShot;

void AudioInit(void);
void PlayBGM(int music);
void PlaySE(int se);
void BGMVolumeSetting(int newVolume);
void SEVolumeSetting(int newVolume);