#include <DxLib.h>
int BGM[12];
int SE_PlayerShot;
int SE_Bomb;

int NowPlayBGM;

int BGMVolume = 0;
int SEVolume = 0;

int BGMVolumeList[11] = { 0,25,50,75,100,125,150,185,220,255 };
int BGMCurrentVolume = 6;
int SEVolumeList[11] = { 0,25,50,75,100,125,150,185,220,255 };
int SECurrentVolume = 3;

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
	BGM[8] = LoadSoundMem("audio/08_null.mp3");
	BGM[9] = LoadSoundMem("audio/09_HermitOfTheAbyss.mp3");
	BGM[10] = LoadSoundMem("audio/10_null.mp3");
	BGM[11] = LoadSoundMem("audio/11_EndofTheStory.mp3");

	SE_PlayerShot = LoadSoundMem("audio/SE_PlayerShot.mp3");
	SE_Bomb = LoadSoundMem("audio/SE_BOON.mp3");
}

void PlayBGM(int music)
{
	if (music == NowPlayBGM) return;
	StopSoundMem(NowPlayBGM);
	NowPlayBGM = music;
	ChangeVolumeSoundMem(BGMVolumeList[BGMCurrentVolume], NowPlayBGM);//volume 0-255
	PlaySoundMem(NowPlayBGM, DX_PLAYTYPE_LOOP);
}

void PlaySE(int se)
{
	ChangeVolumeSoundMem(SEVolumeList[SECurrentVolume], se);//volume 0-255
	PlaySoundMem(se, DX_PLAYTYPE_BACK);
}

void volumeSetBGM(void)
{
	ChangeVolumeSoundMem(BGMVolumeList[BGMCurrentVolume], NowPlayBGM);//volume 0-255
}


