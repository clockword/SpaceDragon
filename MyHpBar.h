#pragma once
#include "MyObject.h"

class CMyHpBar : public CMyObject
{
public:
	CMyHpBar();
	virtual ~CMyHpBar();

	void CreateObject();

	void DrawObject(Graphics* g, DWORD tick);

	void Start();
	void Update(Graphics* g, DWORD tick);
};

