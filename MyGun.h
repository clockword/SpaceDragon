#pragma once
#include "MyObject.h"
#include "MyBullet.h"

class CMyGun : public CMyObject
{
protected:
	CMyBullet *m_bullet;
	DWORD m_numBullet;
	DWORD m_shootDelay;
	DWORD m_shootInterval;
	bool m_shootActive;
public:
	CMyGun();
	virtual ~CMyGun();

	void SetBulletNumber(DWORD num);
	void SetBulletType(BULLETTYPE type);
	void SetBulletSpeed(float speed);
	CMyBullet *GetBullet(DWORD index);
	DWORD GetNumBullet();

	void CreateBullets();

	void SetShootActive(bool active);
	void SetShootDelay(DWORD delay);

	void Shoot(DWORD tick);

	void Start();
	void Update(Graphics* backbuffer, DWORD tick);
};

