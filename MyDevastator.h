#pragma once
#include "MyObject.h"
#include <time.h>

class CMyDevastator : public CMyObject
{
private:
	CMyObject m_devastatorEye;
	DWORD m_moveInterval;
public:
	CMyDevastator();
	virtual ~CMyDevastator();

	void CreateObject();

	void SetActive(bool active);

	void MoveEye(DWORD tick);

	void LimitDrawPos(int x, int y, int width, int height);
	void DevastatorMove(DWORD tick);

	void Start();
	void Update(Graphics *backbuffer, DWORD tick);
};