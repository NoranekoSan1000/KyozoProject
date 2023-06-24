#include <DxLib.h>
int BGM[9];
int SE_PlayerShot;

int BGMVolume = 100;
int SEVolume = 100;

void AudioInit(void)
{
	BGM[0] = LoadSoundMem("audio/00_MirrorImageDiva.mp3");
	BGM[1] = LoadSoundMem("audio/01_Departure.mp3");
	BGM[2] = LoadSoundMem("audio/02_Explosion.mp3");
	BGM[3] = LoadSoundMem("audio/03_WitchPromenade.mp3");
	BGM[4] = LoadSoundMem("audio/04_Jade-coloredWitch.mp3");
	BGM[5] = LoadSoundMem("audio/05_KnightRoad.mp3");
	BGM[6] = LoadSoundMem("audio/06_Ruthlessblade.mp3");
	BGM[7] = LoadSoundMem("audio/07_ResonanceAtTwilight.mp3");
	BGM[8] = LoadSoundMem("audio/08_EndofTheStory.mp3");
	SE_PlayerShot = LoadSoundMem("audio/SE_PlayerShot.mp3");
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