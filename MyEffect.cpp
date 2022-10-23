#include "MyEffect.h"

CMyEffect::CMyEffect()
{
	m_effectType = KNIGHT_BULLET_EFFECT;
}

CMyEffect::~CMyEffect()
{
}

void CMyEffect::SetEffectType(EFFECTTYPE type)
{
	m_effectType = type;
}

EFFECTTYPE CMyEffect::GetEffectType()
{
	return m_effectType;
}

void CMyEffect::DrawObject(Graphics* g, DWORD tick)
{
	if (!m_isActive)
		return;

	m_pos.X = m_pos.X + (int)(m_speed * (tick / 1000.0f) * m_vecDir.x);
	m_pos.Y = m_pos.Y + (int)(m_speed * (tick / 1000.0f) * m_vecDir.y);

	Point pos(m_pos);
	pos.X = pos.X - (m_aniInfo[m_direction].center[m_aniIndex].X - m_aniInfo[m_direction].aniRect[m_aniIndex].X);
	pos.Y = pos.Y - (m_aniInfo[m_direction].center[m_aniIndex].Y - m_aniInfo[m_direction].aniRect[m_aniIndex].Y);

	m_rcCollision.X = m_pos.X - (m_rcCollision.Width - m_ptCollision.X);
	m_rcCollision.Y = m_pos.Y - (m_rcCollision.Height - m_ptCollision.Y);

	this->Draw(g, pos.X, pos.Y,
		m_aniInfo[m_direction].aniRect[m_aniIndex].X,
		m_aniInfo[m_direction].aniRect[m_aniIndex].Y,
		m_aniInfo[m_direction].aniRect[m_aniIndex].Width,
		m_aniInfo[m_direction].aniRect[m_aniIndex].Height);

	m_aniInfo[m_direction].interval += tick;

	if (m_aniInfo[m_direction].interval >= m_aniInfo[m_direction].aniTime[m_aniIndex])
	{
		m_aniInfo[m_direction].interval = 0;
		m_aniIndex++;
		if (m_aniIndex >= m_aniFrame)
		{
			m_aniIndex = 0;
			SetActive(false);
		}
	}

	DrawRect(g);
}

void CMyEffect::CreateObject()
{
	switch (m_effectType)
	{
	case KNIGHT_BULLET_EFFECT: 
		CMyObject::CreateObject("./Data/sprite/bullet_effect.png", "./Data/sprite_info/knight_bullet_effect.txt");
		break;
	case PREDATOR_BULLET_EFFECT: 
		CMyObject::CreateObject("./Data/sprite/bullet_effect.png", "./Data/sprite_info/predator_bullet_effect.txt");
		break;
	case DOMINATOR_BULLET_EFFECT: 
		CMyObject::CreateObject("./Data/sprite/bullet_effect.png", "./Data/sprite_info/dominator_bullet_effect.txt");
		break;
	case DEVASTATOR_EXPOLSION_EFFECT: 
		CMyObject::CreateObject("./Data/sprite/death_explosion_effect.png", "./Data/sprite_info/devastator_expolsion.txt");
		LoadCollision("./Data/collision_info/devastator_explode_collision_rect.txt");
		break;
	case OBJECT_DEATH_EFFECT: 
		CMyObject::CreateObject("./Data/sprite/death_explosion_effect.png", "./Data/sprite_info/object_death.txt");
		break;
	}
}

void CMyEffect::Start()
{
	CreateObject();
}

void CMyEffect::Update(Graphics* g, DWORD tick)
{
	DrawObject(g, tick);
}
