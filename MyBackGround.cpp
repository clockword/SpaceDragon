#include "MyBackGround.h"

CMyBackGround::CMyBackGround()
{
	m_bgType = TITLE_BACKGROUND;
}

CMyBackGround::~CMyBackGround()
{
}

void CMyBackGround::SetBackgroundType(BACKGROUNDTYPE type)
{
	m_bgType = type;
}

void CMyBackGround::CreateObject()
{
	switch (m_bgType)
	{
	case TITLE_BACKGROUND: CMyObject::CreateObject("./Data/sprite/title.png", "./Data/sprite_info/title.txt"); break;
	case TEST_BACKGROUND: CMyObject::CreateObject("./Data/sprite/universe.png", "./Data/sprite_info/universe.txt"); break;
	case FIRST_BATTLE_BACKGROUND: CMyObject::CreateObject("./Data/sprite/first_stage.png", "./Data/sprite_info/earth.txt"); break;break;
	case SECOND_BATTLE_BACKGROUND: CMyObject::CreateObject("./Data/sprite/second_stage.png", "./Data/sprite_info/star.txt"); break;break;
	case THIRD_BATTLE_BACKGROUND: CMyObject::CreateObject("./Data/sprite/third_stage.png", "./Data/sprite_info/end.txt"); break;break;
	}
}

void CMyBackGround::Start()
{
	SetActive(true);
}

void CMyBackGround::Update(Graphics* back_buffer, DWORD tick)
{
	DrawObject(back_buffer, tick);
}
