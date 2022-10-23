#pragma once
#include "MyObject.h"

class CMySlayer : public CMyObject
{
private:
	Point m_exPos;

	DWORD m_waitingTime;
	DWORD m_prepareTime;
	DWORD m_interval;
public:
	CMySlayer();
	virtual ~CMySlayer();

	void CreateObject();

	void SetExpos(Point pos);

	void SetWaitingTime(DWORD time);
	void SetPrepareTime(DWORD time);
	void WaitingTimeDelay(DWORD tick);
	void PrepareTimeDelay(DWORD tick);
	void MoveIfEscape();
	void MoveToExpos();

	void Start();
	void Update(Graphics *backbuffer, DWORD tick);
};