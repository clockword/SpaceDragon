#include "MyDevastator.h"

CMyDevastator::CMyDevastator()
{
	m_moveInterval = 0;
}

CMyDevastator::~CMyDevastator()
{
}

void CMyDevastator::CreateObject()
{
	CMyObject::CreateObject("./Data/sprite/character.png", "./Data/sprite_info/devastator_move.txt");
	m_devastatorEye.CreateObject("./Data/sprite/character.png", "./Data/sprite_info/devastator_eye_move.txt");
	LoadCollision("./Data/collision_info/devastator_collision_rect.txt");
}

void CMyDevastator::SetActive(bool active)
{
	m_isActive = active;
	m_devastatorEye.SetActive(active);
}

void CMyDevastator::MoveEye(DWORD tick)
{
	Point pos(m_pos);
	pos.X += ((rand() % 3) - 1);
	pos.Y += ((rand() % 3) - 1);

	m_devastatorEye.SetPosition(pos.X, pos.Y);
}

void CMyDevastator::LimitDrawPos(int x, int y, int width, int height)
{
	if (!m_isActive)
		return;
	if (m_pos.X < x)
	{
		m_pos.X = x + width;
	}
	else if (m_pos.X > (x + width))
	{
		m_pos.X = x;
	}
	if (m_pos.Y < y)
	{
		m_pos.Y = y + height;
	}
	else if (m_pos.Y > (y + height))
	{
		m_pos.Y = y;
	}
}

void CMyDevastator::DevastatorMove(DWORD tick)
{
	if (!m_isActive)
		return;
	
	m_moveInterval += tick;
	if (m_moveInterval >= 1000)
	{
		int random = rand() % 8;
		m_moveInterval = 0;
		switch (random)
		{
		case 0: SetMoveDirection({ -1.0f,0.0f }); break;
		case 1: SetMoveDirection({ -1.0f,-1.0f }); break;
		case 2: SetMoveDirection({ -1.0f,1.291f }); break;
		case 3: SetMoveDirection({ 1.291f,0.0f }); break;
		case 4: SetMoveDirection({ 1.291f,-1.0f }); break;
		case 5: SetMoveDirection({ 1.291f, 1.291f }); break;
		case 6: SetMoveDirection({ 0.0f,-1.0f }); break;
		case 7: SetMoveDirection({ 0.0f,1.291f }); break;
		}
	}
}

void CMyDevastator::Start()
{
	srand((DWORD)time(NULL));

	CreateObject();
}

void CMyDevastator::Update(Graphics* backbuffer, DWORD tick)
{
	LimitDrawPos(-32, -32, 1056, 800);

	DevastatorMove(tick);

	MoveEye(tick);
	DrawObject(backbuffer, tick);
	m_devastatorEye.DrawObject(backbuffer, tick);
}
