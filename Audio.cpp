#include <DxLib.h>
int ResonanceAtTwilight_audio;
int SE_PlayerShot;

int BGMVolume = 100;
int SEVolume = 100;

void AudioInit(void)
{
	ResonanceAtTwilight_audio = LoadSoundMem("ResonanceAtTwilight.mp3");
	SE_PlayerShot = LoadSoundMem("SE_PlayerShot.mp3");
}

void PlayBGM(int music)
{
	StopSoundMem(music);
	ChangeVolumeSoundMem(BGMVolume, music);//volume 0-255
	PlaySoundMem(music, DX_PLAYTYPE_LOOP);
}

void PlaySE(int se)
{
	ChangeVolumeSoundMem(SEVolume, se);//volume 0-255
	PlaySoundMem(se, DX_PLAYTYPE_BACK);
}

void BGMVolumeSetting(int newVolume)
{
	BGMVolume = newVolume;
}

void SEVolumeSetting(int newVolume)
{
	SEVolume = newVolume;
}