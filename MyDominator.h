#pragma once
#include "MyObject.h"
#include "MyGun.h"

class CMyDominator : public CMyObject
{
private:
	CMyGun m_gun;
public:
	CMyDominator();
	virtual ~CMyDominator();

	void CreateObject();
	void CreateBullet();
	void DominatorShootActive(bool active);

	void SetActive(bool active);
	DWORD GetNumBullet();
	CMyGun* GetGun();

	void Start();
	void Update(Graphics *backbuffer, DWORD tick);
};