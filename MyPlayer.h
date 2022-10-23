#pragma once
#include "MyObject.h"
#include "MyGun.h"

class CMyPlayer : public CMyObject
{
private:
	CMyGun m_gun;
public:
	CMyPlayer();
	virtual ~CMyPlayer();

	void CreateObject();
	void CreateBullet();
	void PlayerShootActive(bool active);

	void SetActive(bool active);

	void SetDirection(DIRECTION dir);
	DWORD GetNumBullet();
	CMyGun *GetGun();

	void Start();
	void Update(Graphics* backbuffer, DWORD tick);
};

