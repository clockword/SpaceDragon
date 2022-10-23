#include "MySlayer.h"

CMySlayer::CMySlayer()
{
	m_exPos = m_pos;
	m_waitingTime = 0;
	m_prepareTime = 0;
	m_interval = 0;
}

CMySlayer::~CMySlayer()
{
}

void CMySlayer::CreateObject()
{
	CMyObject::CreateObject("./Data/sprite/character.png", "./Data/sprite_info/slayer_move.txt");
	LoadCollision("./Data/collision_info/slayer_collision_rect.txt");
}

void CMySlayer::SetExpos(Point pos)
{
	m_exPos = pos;
}

void CMySlayer::SetWaitingTime(DWORD time)
{
	m_waitingTime = time;
}

void CMySlayer::SetPrepareTime(DWORD time)
{
	m_prepareTime = time;
}

void CMySlayer::WaitingTimeDelay(DWORD tick)
{
	if (!m_isActive)
		return;
	if (m_direction != DEFAULT)
		return;
	m_interval += tick;

	if (m_interval >= m_waitingTime)
	{
		m_exPos = m_pos;
		m_interval = 0;
		SetDirection(DOWN);
	}
}

void CMySlayer::PrepareTimeDelay(DWORD tick)
{
	if (!m_isActive)
		return;
	if (m_direction != DOWN)
		return;
	m_interval += tick;

	if (m_interval >= m_prepareTime)
	{
		m_interval = 0;
		SetDirection(LEFT);
		SetMoveDirection({ 0.0f,1.291f });
	}
}

void CMySlayer::MoveIfEscape()
{
	if (!m_isActive)
		return;
	if (m_direction != LEFT)
		return;
	if (m_pos.Y >= 800)
	{
		SetPosition(m_pos.X, -34);
		SetDirection(DEFAULT);
		SetMoveDirection({ 0.0f,1.291f });
		m_interval = 0;
	}
}

void CMySlayer::MoveToExpos()
{
	if (!m_isActive)
		return;
	if (m_direction != DEFAULT)
		return;
	if (m_pos.Y > m_exPos.Y)
	{
		SetMoveDirection({ 0.0f,0.0f });
		SetPosition(m_exPos.X, m_exPos.Y);
		m_interval = 0;
	}
}

void CMySlayer::Start()
{
	SetActive(true);
	
	CreateObject();
}

void CMySlayer::Update(Graphics* backbuffer, DWORD tick)
{
	LimitDrawPos(0, -34, 1024, 834);
	WaitingTimeDelay(tick);
	PrepareTimeDelay(tick);
	MoveIfEscape();
	MoveToExpos();
	DrawObject(backbuffer, tick);
}
