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
	Point *center = nullptr;	// 스프라이트 센터점
	Rect *aniRect = nullptr;	// 스프라이트 정보
	DWORD *aniTime = nullptr;	// 스프라이트 지연시간
	DWORD interval = 0;			// 지연시간까지의 시간 스택
}ANIINFO, * LPANIINFO;

class CMyObject : public CMyImage
{
protected:
	ANIINFO *m_aniInfo;		// 애니메이션(스프라이트) 정보
	Point m_pos;			// 오브젝트 위치
	Rect m_rcCollision;		// 오브젝트 충돌박스 정보
	Point m_ptCollision;	// 오브젝트 충돌박스 센터점

	int m_hp;				// 오브젝트 체력
	
	VECTOR2 m_vecDir;		// 이동방향
	float m_speed;			// 이동 속도

	DIRECTION m_direction;	// 보는 방향(인덱스)
	DWORD m_aniIndex;		// 한방향 애니메이션 인덱스
	DWORD m_aniFrame;		// 한방향 애니메이션 인덱스 최대값
	DWORD m_maxFrame;		// 전체 애니메이션 인덱스 최대값

	bool m_isActive;		// 오브젝트 활성/비활성
public:
	CMyObject();
	virtual ~CMyObject();

	BOOL CreateObject(char* imgfilename, char* infofilename);	// 오브젝트 생성
	BOOL LoadObjectInfo(char* filename);						// (호출됨)
	
	void SetPosition(int x, int y);			// 오브젝트 위치 선정
	void SetDirection(DIRECTION dir);		// 오브젝트 방향 선정
	void SetMoveDirection(VECTOR2 vec);		// 오브젝트 이동방향 선정
	void SetSpeed(float speed);				// 오브젝트 속도 선정
	void SetActive(bool active);			// 오브젝트 활성유무 선정
	void SetHp(int hp);						// 오브젝트 체력 선정
	int GetHp();							// 오브젝트 체력 반환
	bool GetActive();						// 오브젝트 활성유무 반환
	Point GetPosition();					// 오브젝트 위치 반환
	Rect GetCollisionRect();							// 오브젝트 충돌박스 반환

	void LoadCollision(char *filename);			// 오브젝트 충돌 정보 할당(너비,높이,중심점)
	BOOL CheckCollision(Rect rc);				// 오브젝트 충돌 체크 반환

	void LimitDrawPos(int x, int y, int width, int height);	// 오브젝트 이동제한 영역 설정
	void DrawObject(Graphics* g, DWORD tick);				// 스프라이트(애니메이션) 드로우
	void DrawObjectRect(Graphics* g);						// 스프라이트 영역 표시
	void DrawObjectCollision(Graphics* g);					// 충돌 영역 표시
	void DrawRect(Graphics* g);								// 디버그모드일때 스프라이트, 충돌영역 표시

	void Start();									// main의 WinMain함수에서 불러옴
	void Update(Graphics* backbuffer, DWORD tick);	// main의 OnUpdate함수에서 불러옴
};

