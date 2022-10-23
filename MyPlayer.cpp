#include "MyPlayer.h"

CMyPlayer::CMyPlayer()
{
}

CMyPlayer::~CMyPlayer()
{
}

void CMyPlayer::CreateObject()
{
	CMyObject::CreateObject("./Data/sprite/character.png", "./Data/sprite_info/player_move.txt");
	LoadCollision("./Data/collision_info/knight_collision_rect.txt");
}

void CMyPlayer::CreateBullet()
{
	m_gun.SetBulletNumber(30);
	m_gun.SetShootDelay(100);
	m_gun.SetBulletType(KNIGHT);
	m_gun.CreateBullets();
	m_gun.SetBulletSpeed(500.0f);
}

void CMyPlayer::PlayerShootActive(bool active)
{
	if (!m_isActive)
	{
		m_gun.SetShootActive(false);
		return;
	}
	m_gun.SetShootActive(active);
}

void CMyPlayer::SetActive(bool active)
{
	CMyObject::SetActive(active);
	m_gun.SetActive(active);
}

void CMyPlayer::SetDirection(DIRECTION dir)
{
	m_direction = dir;
	switch (dir)
	{
	case DEFAULT: SetMoveDirection({ 0.0f,0.0f });  break;
	case LEFT: SetMoveDirection({ -1.0f,0.0f });  break;
	case RIGHT: SetMoveDirection({ 1.291f,0.0f });  break;
	case UP: SetMoveDirection({ 0.0f,-1.0f });  break;
	case DOWN: SetMoveDirection({ 0.0f,1.291f });  break;
	}
}

DWORD CMyPlayer::GetNumBullet()
{
	return m_gun.GetNumBullet();
}

CMyGun *CMyPlayer::GetGun()
{
	return &m_gun;
}

void CMyPlayer::Start()
{	
	m_gun.Start();

	CreateObject();
}

void CMyPlayer::Update(Graphics* backbuffer, DWORD tick)
{
	m_gun.SetPosition(m_pos.X, m_pos.Y - 20);
	m_gun.Update(backbuffer, tick);

	LimitDrawPos(0, 0, 1024, 768);
	DrawObject(backbuffer, tick);
}
