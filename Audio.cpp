#include <DxLib.h>
int ResonanceAtTwilight_audio;

int Volume = 100;

void AudioInit(void)
{
	ResonanceAtTwilight_audio = LoadSoundMem("ResonanceAtTwilight.mp3");
}

void PlayBGM(int music)
{
	StopSoundMem(music);
	ChangeVolumeSoundMem(Volume, music);//volume 0-255
	PlaySoundMem(music, DX_PLAYTYPE_BACK);
}

void VolumeSetting(int newVolume)
{
	Volume = newVolume;
}