#pragma once
#include "MyImage.h"
#include "DSpriteManager.h"

typedef struct _vec2
{
	float x = 0;
	float y = 0;
}VECTOR2;

typedef enum _dirDef
{
	DEFAULT = 0,
	DOWN,
	LEFT,
	RIGHT,
	UP,
	SELECT
}DIRECTION;

typedef struct _tgAniInfo
{
	Point *center = nullptr;	// ��������Ʈ ������
	Rect *aniRect = nullptr;	// ��������Ʈ ����
	DWORD *aniTime = nullptr;	// ��������Ʈ �����ð�
	DWORD interval = 0;			// �����ð������� �ð� ����
}ANIINFO, * LPANIINFO;

class CMyObject : public CMyImage
{
protected:
	ANIINFO *m_aniInfo;		// �ִϸ��̼�(��������Ʈ) ����
	Point m_pos;			// ������Ʈ ��ġ
	Rect m_rcCollision;		// ������Ʈ �浹�ڽ� ����
	Point m_ptCollision;	// ������Ʈ �浹�ڽ� ������

	int m_hp;				// ������Ʈ ü��
	
	VECTOR2 m_vecDir;		// �̵�����
	float m_speed;			// �̵� �ӵ�

	DIRECTION m_direction;	// ���� ����(�ε���)
	DWORD m_aniIndex;		// �ѹ��� �ִϸ��̼� �ε���
	DWORD m_aniFrame;		// �ѹ��� �ִϸ��̼� �ε��� �ִ밪
	DWORD m_maxFrame;		// ��ü �ִϸ��̼� �ε��� �ִ밪

	bool m_isActive;		// ������Ʈ Ȱ��/��Ȱ��
public:
	CMyObject();
	virtual ~CMyObject();

	BOOL CreateObject(char* imgfilename, char* infofilename);	// ������Ʈ ����
	BOOL LoadObjectInfo(char* filename);						// (ȣ���)
	
	void SetPosition(int x, int y);			// ������Ʈ ��ġ ����
	void SetDirection(DIRECTION dir);		// ������Ʈ ���� ����
	void SetMoveDirection(VECTOR2 vec);		// ������Ʈ �̵����� ����
	void SetSpeed(float speed);				// ������Ʈ �ӵ� ����
	void SetActive(bool active);			// ������Ʈ Ȱ������ ����
	void SetHp(int hp);						// ������Ʈ ü�� ����
	int GetHp();							// ������Ʈ ü�� ��ȯ
	bool GetActive();						// ������Ʈ Ȱ������ ��ȯ
	Point GetPosition();					// ������Ʈ ��ġ ��ȯ
	Rect GetCollisionRect();							// ������Ʈ �浹�ڽ� ��ȯ

	void LoadCollision(char *filename);			// ������Ʈ �浹 ���� �Ҵ�(�ʺ�,����,�߽���)
	BOOL CheckCollision(Rect rc);				// ������Ʈ �浹 üũ ��ȯ

	void LimitDrawPos(int x, int y, int width, int height);	// ������Ʈ �̵����� ���� ����
	void DrawObject(Graphics* g, DWORD tick);				// ��������Ʈ(�ִϸ��̼�) ��ο�
	void DrawObjectRect(Graphics* g);						// ��������Ʈ ���� ǥ��
	void DrawObjectCollision(Graphics* g);					// �浹 ���� ǥ��
	void DrawRect(Graphics* g);								// ����׸���϶� ��������Ʈ, �浹���� ǥ��

	void Start();									// main�� WinMain�Լ����� �ҷ���
	void Update(Graphics* backbuffer, DWORD tick);	// main�� OnUpdate�Լ����� �ҷ���
};

