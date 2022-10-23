#pragma once
#include "MyObject.h"

typedef enum _bgtype
{
	TITLE_BACKGROUND = 0,
	TEST_BACKGROUND,
	FIRST_BATTLE_BACKGROUND,
	SECOND_BATTLE_BACKGROUND,
	THIRD_BATTLE_BACKGROUND
}BACKGROUNDTYPE;

class CMyBackGround : public CMyObject
{
	BACKGROUNDTYPE m_bgType;
public:
	CMyBackGround();
	virtual ~CMyBackGround();

	void SetBackgroundType(BACKGROUNDTYPE type);

	void CreateObject();

	void Start();
	void Update(Graphics* back_buffer, DWORD tick);
};

