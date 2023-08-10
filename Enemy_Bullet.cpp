#include "GameData.h"
#include "Player.h"

void EnemyBulletClear(void);

class EnemyBullet
{
public:
	bool State;
	int Design;
	double X;
	double Y;
	int HitBoxSize;
	int MovePattern;
	double Angle;

	void EnemyBulletGenerate(int design, int x, int y, int hitboxsize, int pattern, double angle)
{
	State = true;
	Design = design;
	X = x;
	Y = y;
	HitBoxSize = hitboxsize;
	MovePattern = pattern;
	Angle = angle;
}

void EnemyBulletDestroy()
{
	State = false;
	Design = X = Y = HitBoxSize = MovePattern = Angle = NULL;
}


void EnemyBulletMove()
{
	float angle = (PI / 2);//����
	float speed = 3;

	switch (MovePattern)
	{
	case 0://�^����
		X += cos(Angle) * speed;
		Y += sin(Angle) * speed;
		break;
	case 1://�E�F�[�u�i���j

		break;
	default:
		break;
	}
}

void EnemyBulletHit()
{
	//�e�ƃv���C���[���ڐG
	double dis = sqrt(pow((double)px - X, 2) + pow((double)py - Y, 2));
	if (dis <= HitBoxSize + Player_HitBoxSize)//��e����
	{
		//��e����
		if (DamagedCoolTime <= 0 && BombTime <= 0)
		{
			if (Life > 0)
			{
				px = InitialPosX;
				py = InitialPosY;
				Life -= 1;
				Bomb = 2;
				DamagedCoolTime = 120;
				EnemyBulletClear();
			}
		}
	}

}

};

EnemyBullet enemybullet[ENEMY_BULLET_AMOUNT];

void EnemyBulletSpawn(int design, int en_x, int en_y, int size,int pattern,double angle)
{
	for (int i = 0; i < ENEMY_BULLET_AMOUNT; i++)
	{
		if (enemybullet[i].State == false)//�V���b�g�ݒ�i�[�ꏊ�̋󂫂��m�F
		{
			PlaySE(SE_PlayerShot); //���ʉ�
			enemybullet[i].EnemyBulletGenerate(design, en_x, en_y, size, pattern, angle);
			break;
		}
	}	
}

void EnemyBulletClear(void)
{
	for (int i = 0; i < ENEMY_BULLET_AMOUNT; i++) enemybullet[i].EnemyBulletDestroy();
}


double  EnemyAngleCalc(int en_x, int en_y)
{
	double tmp;
	tmp = (double)atan2((py - en_y), (px - en_x));
	return tmp;
}

void EnemyShot(int design, EnemyShotPattern type, int en_x, int en_y, int size, int capacity, int arc)
{
	double angle;
	angle = EnemyAngleCalc(en_x, en_y);//���@�_���p
	if (type == ShotWait) return;//�������Ȃ�
	else if (type == OneShot) //1�����@�_��
	{
		EnemyBulletSpawn(design, en_x, en_y, size, 0, -(3 * PI / 2));
	}
	else if (type == AimingOneShot) // ������
	{
		EnemyBulletSpawn(design, en_x, en_y, size, 0, angle - 0.05);
	}
	else if (type == Explosion) // ����
	{
		for (int t = 0; t < 720; t += (720 / capacity))
		{
			EnemyBulletSpawn(design, en_x, en_y, size, 0, PI / 360 * t);
		}
	}
	else if (type == AimingExplosion) // ���@�_������
	{
		for (int t = -360; t < 360; t += (720 / capacity))
		{
			EnemyBulletSpawn(design, en_x, en_y, size, 0, angle + PI / 360 * t);
		}
	}
	else if (type == Diffusion) // �U�e
	{
		for (int t = -arc; t < arc; t += (arc * 2 / capacity))
		{
			EnemyBulletSpawn(design, en_x, en_y, size, 0, -(3 * PI / 2) + PI / 360 * t);
		}
	}
	else if (type == AimingDiffusion) // ���@�_���U�e		���h���������̂Ŋ�����I
	{
		for (int t = -arc; t < arc; t += (arc * 2 / capacity))
		{
			EnemyBulletSpawn(design, en_x, en_y, size, 0, angle + PI / 360 * t);
		}
	}


}

void EnemyBulletAction(void)
{

	for (int i = 0; i < ENEMY_BULLET_AMOUNT; i++)
	{

		if (enemybullet[i].State == true) DrawCircle((int)enemybullet[i].X, (int)enemybullet[i].Y, enemybullet[i].HitBoxSize, GetColor(100, 100, 255), 1);
		else continue;

		DrawRotaGraph((int)enemybullet[i].X, (int)enemybullet[i].Y, 1.0, 0, EnemyShot_img[enemybullet[i].Design], TRUE);//�摜

		enemybullet[i].EnemyBulletMove();
		enemybullet[i].EnemyBulletHit();

		//��ʊO�ŏ���
		if (enemybullet[i].Y < -20 || enemybullet[i].Y > FRAME_HEIGHT || 0 > enemybullet[i].X || enemybullet[i].X > FRAME_WIDTH)
		{
			enemybullet[i].EnemyBulletDestroy();
			continue;
		}

	}
}

