#pragma once
#include "MyPlayer.h"
#include "MyPredator.h"
#include "MySlayer.h"
#include "MyDominator.h"
#include "MyDevastator.h"
#include "MyBackGround.h"
#include "MyEffect.h"
#include "MyHpBar.h"

/*플레이어 최대hp 100고정*/

typedef enum _scnetyp
{
	TITLE_SCENE = 0,
	TEST_SCENE,
	FIRST_BATTLE_SCENE,
	SECOND_BATTLE_SCENE,
	THIRD_BATTLE_SCENE
}SCENETYPE;

typedef struct _scene
{
	SCENETYPE scene_type;

	CMyHpBar hpBar;

	CMyPlayer player;
	CMyPredator* predator = nullptr;
	CMySlayer* slayer = nullptr;
	CMyDominator* dominator = nullptr;
	CMyDevastator* devastator = nullptr;
	CMyBackGround background;

	DWORD num_pr = 0;
	DWORD num_sl = 0;
	DWORD num_dm = 0;
	DWORD num_dv = 0;
	DWORD num_bg = 0;
}SCENE;

typedef struct _efftb
{
	CMyEffect kniBullet_eff;
	CMyEffect preBullet_eff;
	CMyEffect domBullet_eff;
	CMyEffect devExplode_eff;
	CMyEffect objDeath_eff;
}EFFECTTB;

class CSceneManager
{
private:
	BOOL s_gameLoop;
	BOOL s_gameWin;

	DWORD s_nextSceneInterval;
	DWORD s_signInterval;

	Graphics* s_BackBuffer;
	Graphics* s_MainBuffer;
	Bitmap* s_Bitmap;
	RECT s_resolution;

	EFFECTTB s_effTable;
	CMyEffect* s_effect;
	CMyObject s_sign[3];

	SCENE s_scene;
public:
	CSceneManager();
	virtual ~CSceneManager();

	void CreateBuffer(HWND hWnd, HDC hDC);
	void ReleaseBuffer(HWND hWnd, HDC hDC);

	void ProcMsgKeydown(WPARAM wParam);
	void ProcMsgKeyup(WPARAM wParam);

	void SetGameLoop(BOOL bl);
	BOOL GetGameLoop();
	RECT GetResolution();

	void CreateEffTable();
	void DAllocEff();
	void DeleteEff();
	void TurnEffect(EFFECTTYPE type, Point pos);

	void CreateSign();
	void ShowSign(DWORD tick);

	void TitleInput(DIRECTION dir);

	void LoadScene(char* filename);
	void LoadTitleScene();
	void LoadBattleScene(SCENETYPE type);
	void TitleScenePrss(DWORD tick);
	void BattleScenePrss(DWORD tick);
	void ScenePrss(DWORD tick);
	void DeleteScene();

	void DelayToNextScene(DWORD tick, SCENETYPE type);

	void CollisionPrss();

	void Start();
	void OnUpdate(HWND hWnd, DWORD tick);

	void MessageLoof(HWND hwnd, HDC hDC);
};

