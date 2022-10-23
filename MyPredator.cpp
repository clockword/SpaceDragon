#include "MyPredator.h"

CMyPredator::CMyPredator()
{
	m_animInterval = 400;
}

CMyPredator::~CMyPredator()
{
}

void CMyPredator::CreateObject()
{
	CMyObject::CreateObject("./Data/sprite/character.png", "./Data/sprite_info/predator_move.txt");
	LoadCollision("./Data/collision_info/predator_collision_rect.txt");
}

void CMyPredator::CreateBullet()
{
	m_gun.SetBulletNumber(10);
	m_gun.SetShootDelay(800);
	m_gun.SetBulletType(PREDATOR);
	m_gun.CreateBullets();
	m_gun.SetBulletSpeed(250.0f);
}

void CMyPredator::PredatorShootActive(bool active)
{
	if (!m_isActive)
	{
		m_gun.SetShootActive(false);
		return;
	}
	m_gun.SetShootActive(active);
}

void CMyPredator::PredatorShootAnimation(DWORD tick)
{
	m_animInterval += tick;
	if (m_animInterval >= 400)
	{
		m_animInterval = 0;
		switch (m_direction)
		{
		case DEFAULT: SetDirection(DOWN); break;
		case DOWN: SetDirection(DEFAULT); break;
		}
	}
}

void CMyPredator::PredatorMove()
{
	if (!m_isActive)
		return;
	if (m_pos.X <= 32)
	{
		SetMoveDirection({ 1.291f,0.0f });
	}
	else if (m_pos.X >= 992)
	{
		SetMoveDirection({ -1.0f,0.0f });
	}
	if (m_vecDir.x == 0)
	{
		if (m_pos.X > 512)
			SetMoveDirection({ 1.291f,0.0f });
		else if (m_pos.X < 512)
			SetMoveDirection({ -1.0f,0.0f });
		else if (m_pos.X == 512)
			SetMoveDirection({ 0.0f,0.0f });
	}
}

void CMyPredator::SetActive(bool active)
{
	CMyObject::SetActive(active);
	m_gun.SetActive(active);
}

DWORD CMyPredator::GetNumBullet()
{
	return m_gun.GetNumBullet();
}

CMyGun* CMyPredator::GetGun()
{
	return &m_gun;
}

void CMyPredator::Start()
{
	srand((DWORD)time(NULL));

	m_gun.Start();
}

void CMyPredator::Update(Graphics* backbuffer, DWORD tick)
{
	LimitDrawPos(0, 0, 1024, 768);
	PredatorShootAnimation(tick);
	DrawObject(backbuffer, tick);

	PredatorMove();

	m_gun.SetPosition(m_pos.X, m_pos.Y);
	m_gun.Update(backbuffer, tick);
}
