#include "MyBullet.h"

CMyBullet::CMyBullet()
{
	m_bulletType = KNIGHT;
}

CMyBullet::~CMyBullet()
{
}

void CMyBullet::SetBulletType(BULLETTYPE type)
{
	m_bulletType = type;
	switch (m_bulletType)
	{
	case KNIGHT: SetMoveDirection({ 0.0f,-1.0f });  break;
	case PREDATOR: SetMoveDirection({ 0.0f,1.291f });  break;
	case DOMINATOR: SetMoveDirection({ ((float)((rand() % (10 + 1 + 7)) - 7) / 10.0f),1.291f });  break;
	}
}

void CMyBullet::SetDestroyCon()
{
	if (!m_isActive)
		return;
	if (m_pos.X < (0 - 10) || m_pos.Y >(1024 + 10) || m_pos.Y < (0 - 10) || m_pos.Y >(768 + 30))
	{
		SetActive(false);
	}
}

void CMyBullet::CreateObject()
{
	switch (m_bulletType)
	{
	case KNIGHT: 
		CMyObject::CreateObject("./Data/sprite/bullet_effect.png", "./Data/sprite_info/knight_bullet_move.txt");
		LoadCollision("./Data/collision_info/knibullet_collision_rect.txt");
		break;
	case PREDATOR:
		CMyObject::CreateObject("./Data/sprite/bullet_effect.png", "./Data/sprite_info/predator_bullet_move.txt");
		LoadCollision("./Data/collision_info/prebullet_collision_rect.txt");
		break;
	case DOMINATOR:
		CMyObject::CreateObject("./Data/sprite/bullet_effect.png", "./Data/sprite_info/dominator_bullet_move.txt");
		LoadCollision("./Data/collision_info/dombullet_collision_rect.txt");
		break;
	}
}

void CMyBullet::Start()
{
	srand((DWORD)time(NULL));
}

void CMyBullet::Update(Graphics* backbuffer, DWORD tick)
{
	SetDestroyCon();
	DrawObject(backbuffer, tick);
}