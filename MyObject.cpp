#include "MyObject.h"

CMyObject::CMyObject()
{
	m_aniInfo = nullptr;
	m_pos = { 0,0 };
	m_rcCollision = { 0, 0, 0, 0 };

	m_hp = 0;

	m_vecDir = { 0,0 };
	m_speed = 0;

	m_direction = DEFAULT;
	m_aniIndex = 0;
	m_aniFrame = 0;
	m_maxFrame = 0;

	m_isActive = false;
}

CMyObject::~CMyObject()
{
	for (DWORD i = 0; i < m_maxFrame; i += m_aniFrame)
		if (m_aniInfo[i / m_aniFrame].center)
		{
			delete[] m_aniInfo[i / m_aniFrame].center;
			m_aniInfo[i / m_aniFrame].center = nullptr;
		}
	for (DWORD i = 0; i < m_maxFrame; i += m_aniFrame)
		if (m_aniInfo[i / m_aniFrame].aniRect)
		{
			delete[] m_aniInfo[i / m_aniFrame].aniRect;
			m_aniInfo[i / m_aniFrame].aniRect = nullptr;
		}
	for (DWORD i = 0; i < m_maxFrame; i += m_aniFrame)
		if (m_aniInfo[i / m_aniFrame].aniTime)
		{
			delete[] m_aniInfo[i / m_aniFrame].aniTime;
			m_aniInfo[i / m_aniFrame].aniTime = nullptr;
		}
	if (m_aniInfo)
	{
		delete[] m_aniInfo;
		m_aniInfo = nullptr;
	}
}

BOOL CMyObject::CreateObject(char* imgfilename, char* infofilename)
{
	Load(imgfilename);

	if (m_pImage == NULL)
		return FALSE;

	m_pPen = new Pen(Color(0, 255, 255), 1.0f);

	return LoadObjectInfo(infofilename);
}

BOOL CMyObject::LoadObjectInfo(char* filename)
{
	int max_frame, ani_frame, left, top, width, height, anitime, xCenter, yCenter;

	FILE* fp = fopen(filename, "rt");
	if (!fp)
		return FALSE;

	fscanf(fp, "%d %d", &max_frame, &ani_frame);
	m_aniFrame = ani_frame;
	m_maxFrame = max_frame;

	m_aniInfo = new ANIINFO[m_maxFrame];

	for (DWORD i = 0; i < m_maxFrame; i += m_aniFrame)
	{
		m_aniInfo[i / m_aniFrame].center = new Point[m_aniFrame];
		m_aniInfo[i / m_aniFrame].aniRect = new Rect[m_aniFrame];
		m_aniInfo[i / m_aniFrame].aniTime = new DWORD[m_aniFrame];
	}
	for (DWORD i = 0; i < m_maxFrame; i++)
	{
		fscanf(fp, "%d %d %d %d %d %d %d", &left, &top, &width, &height, &xCenter, &yCenter ,&anitime);
		m_aniInfo[i / m_aniFrame].aniRect[i % m_aniFrame].X = left;
		m_aniInfo[i / m_aniFrame].aniRect[i % m_aniFrame].Y = top;
		m_aniInfo[i / m_aniFrame].aniRect[i % m_aniFrame].Width = width;
		m_aniInfo[i / m_aniFrame].aniRect[i % m_aniFrame].Height = height;
		m_aniInfo[i / m_aniFrame].center[i % m_aniFrame].X = xCenter;
		m_aniInfo[i / m_aniFrame].center[i % m_aniFrame].Y = yCenter;
		m_aniInfo[i / m_aniFrame].aniTime[i % m_aniFrame] = anitime;
	}

	fclose(fp);

	return 0;
}

void CMyObject::SetPosition(int x, int y)
{
	m_pos.X = x;
	m_pos.Y = y;
}

void CMyObject::SetDirection(DIRECTION dir)
{
	m_direction = dir;
}

void CMyObject::SetMoveDirection(VECTOR2 vec)
{
	m_vecDir = vec;
}

void CMyObject::SetSpeed(float speed)
{
	m_speed = speed;
}

void CMyObject::SetActive(bool active)
{
	m_isActive = active;
}

void CMyObject::SetHp(int hp)
{
	m_hp = hp;
}

int CMyObject::GetHp()
{
	return m_hp;
}

bool CMyObject::GetActive()
{
	return m_isActive;
}

Point CMyObject::GetPosition()
{
	return m_pos;
}

Rect CMyObject::GetCollisionRect()
{
	return m_rcCollision;
}

void CMyObject::LoadCollision(char *filename)
{
	int width, height, centerX, centerY;

	FILE* fp = fopen(filename, "rt");
	if (!fp)
		return;

	fscanf(fp, "%d %d %d %d", &width, &height, &centerX, &centerY);
	m_rcCollision.Width = width;
	m_rcCollision.Height = height;
	m_ptCollision.X = centerX;
	m_ptCollision.Y = centerY;

	fclose(fp);
}

BOOL CMyObject::CheckCollision(Rect rc)
{
	if (!m_isActive)
		return false;

	if ((m_rcCollision.X + m_rcCollision.Width > rc.X) && (m_rcCollision.Y + m_rcCollision.Height > rc.Y) &&
		(m_rcCollision.X < rc.X + rc.Width) && (m_rcCollision.Y < rc.Y + rc.Height))
		return true;
	else
		return false;
}

void CMyObject::LimitDrawPos(int x, int y, int width, int height)
{
	if (!m_isActive)
		return;
	if (m_pos.X < x)
	{
		m_pos.X = x;
		m_vecDir.x = 0.0f;
	}
	else if (m_pos.X > (x + width))
	{
		m_pos.X = x + width;
		m_vecDir.x = 0.0f;
	}
	if (m_pos.Y < y)
	{
		m_pos.Y = y;
		m_vecDir.y = 0.0f;
	}
	else if (m_pos.Y > (y + height))
	{
		m_pos.Y = y + height;
		m_vecDir.y = 0.0f;
	}
}

void CMyObject::DrawObject(Graphics* g, DWORD tick)
{
	if (!m_isActive)
		return;

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
		m_aniInfo[m_direction].aniRect[m_aniIndex].Width,
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

void CMyObject::DrawObjectRect(Graphics* g)
{
	if (!m_isActive)
		return;
	if (m_pPen == NULL)
		return;

	Rect rc(m_aniInfo[m_direction].aniRect[m_aniIndex]);
	rc.X = m_pos.X - (m_aniInfo[m_direction].center[m_aniIndex].X - m_aniInfo[m_direction].aniRect[m_aniIndex].X);
	rc.Y = m_pos.Y - (m_aniInfo[m_direction].center[m_aniIndex].Y - m_aniInfo[m_direction].aniRect[m_aniIndex].Y);

	g->DrawRectangle(m_pPen, rc);
}

void CMyObject::DrawObjectCollision(Graphics* g)
{
	if (!m_isActive)
		return;
	if (m_pPen == NULL)
		return;

	Pen pen = Color(255, 0, 255);
	pen.SetWidth(1.0f);
	g->DrawRectangle(&pen, m_rcCollision);
}

void CMyObject::DrawRect(Graphics* g)
{
#if _DEBUG
	DrawObjectRect(g);
	DrawObjectCollision(g);
#endif
}

void CMyObject::Start()
{
}

void CMyObject::Update(Graphics* backbuffer, DWORD tick)
{
	DrawObject(backbuffer, tick);
}