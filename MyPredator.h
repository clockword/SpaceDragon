#pragma once
#include <time.h>
#include "MyObject.h"
#include "MyGun.h"

class CMyPredator : public CMyObject
{
private:
	CMyGun m_gun;
	DWORD m_animInterval;
public:
	CMyPredator();
	virtual ~CMyPredator();

	void CreateObject();
	void CreateBullet();
	void PredatorShootActive(bool active);
	void PredatorShootAnimation(DWORD tick);

	void PredatorMove();

	void SetActive(bool active);
	DWORD GetNumBullet();
	CMyGun* GetGun();

	void Start();
	void Update(Graphics* backbuffer, DWORD tick);
};

