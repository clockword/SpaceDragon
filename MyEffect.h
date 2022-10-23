#pragma once
#include "MyObject.h"

typedef enum _efttyp
{
	KNIGHT_BULLET_EFFECT = 0,
	PREDATOR_BULLET_EFFECT,
	DOMINATOR_BULLET_EFFECT,
	DEVASTATOR_EXPOLSION_EFFECT,
	OBJECT_DEATH_EFFECT
}EFFECTTYPE;

class CMyEffect : public CMyObject
{
private:
	EFFECTTYPE m_effectType;
public:
	CMyEffect();
	virtual ~CMyEffect();

	void SetEffectType(EFFECTTYPE type);
	EFFECTTYPE GetEffectType();

	void DrawObject(Graphics* g, DWORD tick);

	void CreateObject();

	void Start();
	void Update(Graphics* g, DWORD tick);
};

