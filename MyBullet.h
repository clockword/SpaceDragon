#pragma once
#include <time.h>
#include "MyObject.h"

typedef enum _typeBullet
{
	KNIGHT = 0,
	PREDATOR,
	DOMINATOR
}BULLETTYPE;

class CMyBullet : public CMyObject
{
private:
	BULLETTYPE m_bulletType;
public:
	CMyBullet();
	virtual ~CMyBullet();

	void SetBulletType(BULLETTYPE type);
	void SetDestroyCon();

	void CreateObject();

	void Start();
	void Update(Graphics* backbuffer, DWORD tick);
};

