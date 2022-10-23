#include "MyDominator.h"

CMyDominator::CMyDominator()
{
}

CMyDominator::~CMyDominator()
{
}

void CMyDominator::CreateObject()
{
	CMyObject::CreateObject("./Data/sprite/character.png", "./Data/sprite_info/dominator_move.txt");
	LoadCollision("./Data/collision_info/dominator_collision_rect.txt");
}

void CMyDominator::CreateBullet()
{
	m_gun.SetBulletNumber(30);
	m_gun.SetShootDelay(500);
	m_gun.SetBulletType(DOMINATOR);
	m_gun.CreateBullets();
	m_gun.SetBulletSpeed(100);
}

void CMyDominator::DominatorShootActive(bool active)
{
	if (!m_isActive)
	{
		m_gun.SetShootActive(false);
		return;
	}
	m_gun.SetShootActive(active);
}

void CMyDominator::SetActive(bool active)
{
	CMyObject::SetActive(active);
	m_gun.SetActive(active);
}

DWORD CMyDominator::GetNumBullet()
{
	return m_gun.GetNumBullet();
}

CMyGun* CMyDominator::GetGun()
{
	return &m_gun;
}

void CMyDominator::Start()
{
	m_gun.Start();
	
	CreateObject();
}

void CMyDominator::Update(Graphics* backbuffer, DWORD tick)
{
	m_gun.SetPosition(m_pos.X, m_pos.Y);
	m_gun.Update(backbuffer, tick);

	LimitDrawPos(0, 0, 1024, 768);
	DrawObject(backbuffer, tick);
}
