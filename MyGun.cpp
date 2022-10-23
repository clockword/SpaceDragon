#include "MyGun.h"

CMyGun::CMyGun()
{
	m_bullet = nullptr;
	m_numBullet = 0;
	m_shootDelay = 0;
	m_shootInterval = 0;
	m_shootActive = false;
}

CMyGun::~CMyGun()
{
	if (m_bullet) 
	{
		delete []m_bullet;
		m_bullet = nullptr;
	}
}

void CMyGun::SetBulletNumber(DWORD num)
{
	m_numBullet = num;
	if (m_bullet)
	{
		delete[] m_bullet;
		m_bullet = nullptr;
	}
	m_bullet = new CMyBullet[m_numBullet];
}

void CMyGun::SetBulletType(BULLETTYPE type)
{
	for (DWORD i = 0; i < m_numBullet; i++)
	{
		m_bullet[i].SetBulletType(type);
	}
}

void CMyGun::SetBulletSpeed(float speed)
{
	for (DWORD i = 0; i < m_numBullet; i++)
	{
		m_bullet[i].SetSpeed(speed);
	}
}

CMyBullet *CMyGun::GetBullet(DWORD index)
{
	return &m_bullet[index];
}

DWORD CMyGun::GetNumBullet()
{
	return m_numBullet;
}

void CMyGun::CreateBullets()
{
	for (DWORD i = 0; i < m_numBullet; i++)
	{
		m_bullet[i].CreateObject();
	}
}

void CMyGun::SetShootActive(bool active)
{
	m_shootActive = active;
}

void CMyGun::SetShootDelay(DWORD delay)
{
	m_shootDelay = delay;
}

void CMyGun::Shoot(DWORD tick)
{
	if (!m_isActive)
		return;

	m_shootInterval += tick;
	if (m_shootInterval < m_shootDelay)
		return;
	m_shootInterval = 0;

 	if (!m_shootActive)
		return;
	for (DWORD i = 0; i < m_numBullet; i++)
	{
		if (!m_bullet[i].GetActive())
		{
 			m_bullet[i].SetPosition(m_pos.X, m_pos.Y);
			m_bullet[i].SetActive(true);
			break;
		}
	}
}

void CMyGun::Start()
{
	for (DWORD i = 0; i < m_numBullet; i++)
	{
		m_bullet[i].Start();
	}
}

void CMyGun::Update(Graphics* backbuffer, DWORD tick)
{
	Shoot(tick);

	for (DWORD i = 0; i < m_numBullet; i++)
	{
		m_bullet[i].Update(backbuffer, tick);
	}
}
