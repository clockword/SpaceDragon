#include "MyHpBar.h"

CMyHpBar::CMyHpBar()
{
}

CMyHpBar::~CMyHpBar()
{
}

void CMyHpBar::CreateObject()
{
	CMyObject::CreateObject("./Data/sprite/bullet_effect.png", "./Data/sprite_info/hpbar.txt");
}

void CMyHpBar::DrawObject(Graphics* g, DWORD tick)
{
	if (!m_isActive)
		return;

	INT hpWidth = m_aniInfo[m_direction].aniRect[m_aniIndex].Width;
	hpWidth = hpWidth * m_hp / 100;

	m_pos.X = m_pos.X + (m_speed * (tick / 1000.0f) * m_vecDir.x);
	m_pos.Y = m_pos.Y + (m_speed * (tick / 1000.0f) * m_vecDir.y);

	Point pos(m_pos);
	pos.X = pos.X - (m_aniInfo[m_direction].center[m_aniIndex].X - m_aniInfo[m_direction].aniRect[m_aniIndex].X);
	pos.Y = pos.Y - (m_aniInfo[m_direction].center[m_aniIndex].Y - m_aniInfo[m_direction].aniRect[m_aniIndex].Y);

	m_rcCollision.X = m_pos.X - (m_rcCollision.Width - m_ptCollision.X);
	m_rcCollision.Y = m_pos.Y - (m_rcCollision.Height - m_ptCollision.Y);

	this->Draw(g, pos.X, pos.Y,
		m_aniInfo[m_direction].aniRect[m_aniIndex].X,
		m_aniInfo[m_direction].aniRect[m_aniIndex].Y,
		hpWidth,
		m_aniInfo[m_direction].aniRect[m_aniIndex].Height);

	m_aniInfo[m_direction].interval += tick;

	if (m_aniInfo[m_direction].interval >= m_aniInfo[m_direction].aniTime[m_aniIndex])
	{
		m_aniInfo[m_direction].interval = 0;
		m_aniIndex++;
		if (m_aniIndex >= m_aniFrame)
			m_aniIndex = 0;
	}

	DrawRect(g);
}

void CMyHpBar::Start()
{
	CreateObject();
}

void CMyHpBar::Update(Graphics* g, DWORD tick)
{
	DrawObject(g, tick);
}
