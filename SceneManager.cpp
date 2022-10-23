#include "SceneManager.h"

CSceneManager::CSceneManager()
{
	s_gameWin = false;
	s_gameLoop = true;
	s_nextSceneInterval = 0;
	s_signInterval = 0;
	s_BackBuffer = nullptr;
	s_MainBuffer = nullptr;
	s_Bitmap = nullptr;
	s_resolution = { 0,0,1024,768 };
	s_effect = nullptr;
}

CSceneManager::~CSceneManager()
{

}

void CSceneManager::CreateBuffer(HWND hWnd, HDC hDC)
{
	GdiplusStartupInput			gdiplusStartupInput;
	ULONG_PTR					gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	RECT rc;
	GetClientRect(hWnd, &rc);

	s_Bitmap = new Bitmap(rc.right - rc.left, rc.bottom - rc.top);
	s_BackBuffer = new Graphics(s_Bitmap);
	s_BackBuffer->SetPageUnit(Gdiplus::Unit::UnitPixel);

	s_MainBuffer = new Graphics(hDC);
	s_MainBuffer->SetPageUnit(Gdiplus::Unit::UnitPixel);
}

void CSceneManager::ReleaseBuffer(HWND hWnd, HDC hDC)
{
	ReleaseDC(hWnd, hDC);

	delete s_Bitmap;
	delete s_BackBuffer;
	delete s_MainBuffer;
}

void CSceneManager::ProcMsgKeydown(WPARAM wParam)
{
	switch (s_scene.scene_type)
	{
	case TITLE_SCENE:
		switch (wParam)
		{
		case VK_UP: TitleInput(UP); break;
		case VK_DOWN: TitleInput(DOWN); break;
		case VK_SPACE: TitleInput(SELECT); break;
		}
		break;
	default :
		switch (wParam)
		{
		case VK_LEFT: s_scene.player.SetDirection(LEFT); break;
		case VK_RIGHT: s_scene.player.SetDirection(RIGHT); break;
		case VK_UP: s_scene.player.SetDirection(UP); break;
		case VK_DOWN: s_scene.player.SetDirection(DOWN); break;
		case VK_SPACE: s_scene.player.PlayerShootActive(true); break;
		}
		break;
	}
}

void CSceneManager::ProcMsgKeyup(WPARAM wParam)
{
	switch (s_scene.scene_type)
	{
	case TITLE_SCENE:
		
		break;
	default:
		switch (wParam)
		{
		case VK_SPACE: s_scene.player.PlayerShootActive(false); break;
		}
		break;
	}
}

void CSceneManager::SetGameLoop(BOOL bl)
{
	s_gameLoop = bl;
}

BOOL CSceneManager::GetGameLoop()
{
	return s_gameLoop;
}

RECT CSceneManager::GetResolution()
{
	return s_resolution;
}

void CSceneManager::CreateEffTable()
{
	s_effTable.kniBullet_eff.SetEffectType(KNIGHT_BULLET_EFFECT);
	s_effTable.preBullet_eff.SetEffectType(PREDATOR_BULLET_EFFECT);
	s_effTable.domBullet_eff.SetEffectType(DOMINATOR_BULLET_EFFECT);
	s_effTable.devExplode_eff.SetEffectType(DEVASTATOR_EXPOLSION_EFFECT);
	s_effTable.objDeath_eff.SetEffectType(OBJECT_DEATH_EFFECT);

	s_effTable.kniBullet_eff.CreateObject();
	s_effTable.preBullet_eff.CreateObject();
	s_effTable.domBullet_eff.CreateObject();
	s_effTable.devExplode_eff.CreateObject();
	s_effTable.objDeath_eff.CreateObject();
}

void CSceneManager::DAllocEff()
{
	s_effect = new CMyEffect[50];
}

void CSceneManager::DeleteEff()
{
	s_effect = nullptr;
	delete[] s_effect;
}

void CSceneManager::TurnEffect(EFFECTTYPE type, Point pos)
{
	DWORD index = 0;
	for (DWORD i = 0; i < 50; i++)
	{
		if (!s_effect[i].GetActive())
			index = i;
	}
	switch (type)
	{
	case KNIGHT_BULLET_EFFECT: s_effect[index] = s_effTable.kniBullet_eff; break;
	case PREDATOR_BULLET_EFFECT: s_effect[index] = s_effTable.preBullet_eff; break;
	case DOMINATOR_BULLET_EFFECT: s_effect[index] = s_effTable.domBullet_eff; break;
	case DEVASTATOR_EXPOLSION_EFFECT: s_effect[index] = s_effTable.devExplode_eff; break;
	case OBJECT_DEATH_EFFECT: s_effect[index] = s_effTable.objDeath_eff; break;
	}
	s_effect[index].SetPosition(pos.X, pos.Y);
	s_effect[index].SetActive(true);
}

void CSceneManager::CreateSign()
{
	s_sign[0].CreateObject("./Data/sprite/bullet_effect.png", "./Data/sprite_info/game_clear_sign.txt");
	s_sign[0].SetPosition(512, 384);
	s_sign[1].CreateObject("./Data/sprite/bullet_effect.png", "./Data/sprite_info/game_fail_sign.txt");
	s_sign[1].SetPosition(512, 384);
	s_sign[2].CreateObject("./Data/sprite/reward.png", "./Data/sprite_info/reward_sign.txt");
	s_sign[2].SetPosition(768, 384);
}

void CSceneManager::ShowSign(DWORD tick)
{
	if (s_sign[0].GetActive())
	{
		s_signInterval += tick;
		if (s_signInterval >= 3000)
		{
			s_signInterval = 0;
			s_sign[0].SetActive(false);
		}
	}
	else if (s_sign[1].GetActive())
	{
		s_signInterval += tick;
		if (s_signInterval >= 3000)
		{
			s_signInterval = 0;
			s_sign[1].SetActive(false);
		}
	}
}

void CSceneManager::TitleInput(DIRECTION dir)
{
	switch (dir)
	{
	case UP:
		if (s_scene.devastator[0].GetActive())
		{
			s_scene.devastator[0].SetActive(false);
			s_scene.dominator[0].SetActive(true);
		}
		else if (s_scene.dominator[0].GetActive())
		{
			s_scene.dominator[0].SetActive(false);
			s_scene.predator[0].SetActive(true);
		}
		else if (s_scene.predator[0].GetActive())
		{
			s_scene.predator[0].SetActive(false);
			s_scene.devastator[0].SetActive(true);
		}
		break;
	case DOWN:
		if (s_scene.devastator[0].GetActive())
		{
			s_scene.devastator[0].SetActive(false);
			s_scene.predator[0].SetActive(true);
		}
		else if (s_scene.dominator[0].GetActive())
		{
			s_scene.dominator[0].SetActive(false);
			s_scene.devastator[0].SetActive(true);
		}
		else if (s_scene.predator[0].GetActive())
		{
			s_scene.predator[0].SetActive(false);
			s_scene.dominator[0].SetActive(true);
		}
		break;
	case SELECT:
		if (s_scene.devastator[0].GetActive())
		{
			SetGameLoop(false);
		}
		else if (s_scene.dominator[0].GetActive())
		{
			LoadBattleScene(FIRST_BATTLE_SCENE);
		}
		else if (s_scene.predator[0].GetActive())
		{
			LoadBattleScene(TEST_SCENE);
		}
		break;
	}
}

void CSceneManager::LoadScene(char* filename)
{
	DWORD amount;
	int posX, posY;
	FILE* fp = fopen(filename, "rt");
	if (!fp)
		return;

	if (filename == "./Data/scene_info/title_scene.txt")
		s_scene.scene_type = TITLE_SCENE;
	else if (filename == "./Data/scene_info/test_scene.txt")
		s_scene.scene_type = TEST_SCENE;
	else if (filename == "./Data/scene_info/first_scene.txt")
		s_scene.scene_type = FIRST_BATTLE_SCENE;
	else if (filename == "./Data/scene_info/second_scene.txt")
		s_scene.scene_type = SECOND_BATTLE_SCENE;
	else if (filename == "./Data/scene_info/third_scene.txt")
		s_scene.scene_type = THIRD_BATTLE_SCENE;

	fscanf(fp, "%d %d %d", &amount, &posX, &posY);
	if (s_scene.predator)
	{
		delete[] s_scene.predator;
		s_scene.predator = nullptr;
	}
	s_scene.num_pr = amount;
	if (s_scene.num_pr > 0)
	{
		s_scene.predator = new CMyPredator[s_scene.num_pr];
		s_scene.num_pr = s_scene.num_pr;
		s_scene.predator[0].SetPosition(posX, posY);
		for (DWORD i = 1; i < s_scene.num_pr; i++)
		{
			fscanf(fp, " %d %d", &posX, &posY);
			s_scene.predator[i].SetPosition(posX, posY);
		}
	}
	fscanf(fp, "%d %d %d", &amount, &posX, &posY);
	if (s_scene.slayer)
	{
		delete[] s_scene.slayer;
		s_scene.slayer = nullptr;
	}
	s_scene.num_sl = amount;
	if (s_scene.num_sl > 0)
	{
		s_scene.slayer = new CMySlayer[s_scene.num_sl];
		s_scene.num_sl = s_scene.num_sl;
		s_scene.slayer[0].SetPosition(posX, posY);
		for (DWORD i = 1; i < s_scene.num_sl; i++)
		{
			fscanf(fp, " %d %d", &posX, &posY);
			s_scene.slayer[i].SetPosition(posX, posY);
		}
	}
	fscanf(fp, "%d %d %d", &amount, &posX, &posY);
	if (s_scene.dominator)
	{
		delete[] s_scene.dominator;
		s_scene.dominator = nullptr;
	}
	s_scene.num_dm = amount;
	if (s_scene.num_dm > 0)
	{
		s_scene.dominator = new CMyDominator[s_scene.num_dm];
		s_scene.num_dm = s_scene.num_dm;
		s_scene.dominator[0].SetPosition(posX, posY);
		for (DWORD i = 1; i < s_scene.num_dm; i++)
		{
			fscanf(fp, " %d %d", &posX, &posY);
			s_scene.dominator[i].SetPosition(posX, posY);
		}
	}
	fscanf(fp, "%d %d %d", &amount, &posX, &posY);
	if (s_scene.devastator)
	{
		delete[] s_scene.devastator;
		s_scene.devastator = nullptr;
	}
	s_scene.num_dv = amount;
	if (s_scene.num_dv > 0)
	{
		s_scene.devastator = new CMyDevastator[s_scene.num_dv];
		s_scene.num_dv = s_scene.num_dv;
		s_scene.devastator[0].SetPosition(posX, posY);
		for (DWORD i = 1; i < s_scene.num_dv; i++)
		{
			fscanf(fp, " %d %d", &posX, &posY);
			s_scene.devastator[i].SetPosition(posX, posY);
		}
	}
	fscanf(fp, "%d %d %d", &amount, &posX, &posY);
	s_scene.background.SetPosition(posX, posY);

	if (s_scene.scene_type == TITLE_SCENE)
		s_scene.background.SetBackgroundType(TITLE_BACKGROUND);
	else if(s_scene.scene_type == TEST_SCENE)
		s_scene.background.SetBackgroundType(TEST_BACKGROUND);
	else if(s_scene.scene_type == FIRST_BATTLE_SCENE)
		s_scene.background.SetBackgroundType(FIRST_BATTLE_BACKGROUND);
	else if (s_scene.scene_type == SECOND_BATTLE_SCENE)
		s_scene.background.SetBackgroundType(SECOND_BATTLE_BACKGROUND);
	else if (s_scene.scene_type == THIRD_BATTLE_SCENE)
		s_scene.background.SetBackgroundType(THIRD_BATTLE_BACKGROUND);

	s_scene.background.CreateObject();

	fclose(fp);
}

void CSceneManager::LoadTitleScene()
{
	LoadScene("./Data/scene_info/title_scene.txt");

	if (s_gameWin)
		s_sign[2].SetActive(true);

	s_scene.player.SetActive(false);

	s_scene.hpBar.SetActive(false);
	
	s_scene.predator[0].CreateObject();

	s_scene.predator[0].SetActive(true);
	s_scene.predator[0].PredatorShootActive(false);
	s_scene.predator[0].SetSpeed(0.0f);

	s_scene.dominator[0].CreateObject();

	s_scene.dominator[0].SetActive(false);
	s_scene.dominator[0].DominatorShootActive(false);
	s_scene.dominator[0].SetSpeed(0.0f);

	s_scene.devastator[0].CreateObject();

	s_scene.devastator[0].SetActive(false);
	s_scene.devastator[0].SetSpeed(0.0f);
}

void CSceneManager::LoadBattleScene(SCENETYPE type)
{
	switch (type)
	{
	case TEST_SCENE: LoadScene("./Data/scene_info/test_scene.txt"); break;
	case FIRST_BATTLE_SCENE: LoadScene("./Data/scene_info/first_scene.txt"); break;
	case SECOND_BATTLE_SCENE: LoadScene("./Data/scene_info/second_scene.txt"); break;
	case THIRD_BATTLE_SCENE: LoadScene("./Data/scene_info/third_scene.txt"); break;
	}
	DWORD scale = 0;

	s_sign[2].SetActive(false);

	s_scene.player.SetActive(true);
	s_scene.player.SetSpeed(300.0f);
	s_scene.player.CreateBullet();
	s_scene.player.SetHp(100);
	s_scene.player.SetPosition(512, 700);
	s_scene.player.SetDirection(DEFAULT);

	s_scene.hpBar.SetActive(true);
	s_scene.hpBar.SetHp(s_scene.player.GetHp());
	s_scene.hpBar.SetPosition(10, 740);

	scale = s_scene.num_pr;
	for (DWORD i = 0; i < scale; i++)
	{
		s_scene.predator[i].SetActive(true);
		s_scene.predator[i].CreateObject();
		s_scene.predator[i].SetSpeed(100.0f);
		s_scene.predator[i].CreateBullet();
		s_scene.predator[i].PredatorShootActive(true);
		s_scene.predator[i].SetHp(4);
	}

	scale = s_scene.num_sl;
	for (DWORD i = 0; i < scale; i++)
	{
		s_scene.slayer[i].SetActive(true);
		s_scene.slayer[i].CreateObject();
		s_scene.slayer[i].SetExpos(s_scene.slayer[i].GetPosition());
		s_scene.slayer[i].SetSpeed(1000.0f);
		s_scene.slayer[i].SetHp(8);
		s_scene.slayer[i].SetWaitingTime(5000);
		s_scene.slayer[i].SetPrepareTime(1000);
	}

	scale = s_scene.num_dm;
	for (DWORD i = 0; i < scale; i++)
	{
		s_scene.dominator[i].SetActive(true);
		s_scene.dominator[i].CreateObject();
		s_scene.dominator[i].CreateBullet();
		s_scene.dominator[i].DominatorShootActive(true);
		s_scene.dominator[i].SetHp(15);
	}

	scale = s_scene.num_dv;
	for (DWORD i = 0; i < scale; i++)
	{
		s_scene.devastator[i].SetActive(true);
		s_scene.devastator[i].CreateObject();
		s_scene.devastator[i].SetSpeed(150.0f);
		s_scene.devastator[i].SetHp(4);
	}
}

void CSceneManager::TitleScenePrss(DWORD tick)
{
}

void CSceneManager::BattleScenePrss(DWORD tick)
{
	DWORD scale = 0;
	bool allKill = true;

	s_scene.hpBar.SetHp(s_scene.player.GetHp());

	if (s_scene.player.GetHp() == 0 && s_scene.player.GetActive())
	{
		s_scene.player.SetActive(false);
		TurnEffect(OBJECT_DEATH_EFFECT, s_scene.player.GetPosition());
	}

	scale = s_scene.num_pr;
	for (DWORD i = 0; i < scale; i++)
	{
		if (s_scene.predator[i].GetHp() == 0 && s_scene.predator[i].GetActive())
		{
			s_scene.predator[i].SetActive(false);
			TurnEffect(OBJECT_DEATH_EFFECT, s_scene.predator[i].GetPosition());
		}
		if (s_scene.predator[i].GetActive())
			allKill = false;
	}

	scale = s_scene.num_sl;
	for (DWORD i = 0; i < scale; i++)
	{
		if (s_scene.slayer[i].GetHp() == 0 && s_scene.slayer[i].GetActive())
		{
			s_scene.slayer[i].SetActive(false);
			TurnEffect(OBJECT_DEATH_EFFECT, s_scene.slayer[i].GetPosition());
		}
		if (s_scene.slayer[i].GetActive())
			allKill = false;
	}

	scale = s_scene.num_dm;
	for (DWORD i = 0; i < scale; i++)
	{
		if (s_scene.dominator[i].GetHp() == 0 && s_scene.dominator[i].GetActive())
		{
			s_scene.dominator[i].SetActive(false);
			TurnEffect(OBJECT_DEATH_EFFECT, s_scene.dominator[i].GetPosition());
		}
		if (s_scene.dominator[i].GetActive())
			allKill = false;
	}

	scale = s_scene.num_dv;
	for (DWORD i = 0; i < scale; i++)
	{
		if (s_scene.devastator[i].GetHp() == 0 && s_scene.devastator[i].GetActive())
		{
			s_scene.devastator[i].SetActive(false);
			TurnEffect(DEVASTATOR_EXPOLSION_EFFECT, s_scene.devastator[i].GetPosition());
		}
		if (s_scene.devastator[i].GetActive())
			allKill = false;
	}

	if (!s_scene.player.GetActive())
	{
		DelayToNextScene(tick, TITLE_SCENE);
		s_sign[1].SetActive(true);
	}

	if (allKill && s_scene.player.GetActive())
	{
		if (s_scene.scene_type == TEST_SCENE)
		{
			DelayToNextScene(tick, TITLE_SCENE);
		}
		else if (s_scene.scene_type == FIRST_BATTLE_SCENE)
		{
			DelayToNextScene(tick, SECOND_BATTLE_SCENE);
		}
		else if (s_scene.scene_type == SECOND_BATTLE_SCENE)
		{
			DelayToNextScene(tick, THIRD_BATTLE_SCENE);
		}
		else if (s_scene.scene_type == THIRD_BATTLE_SCENE)
		{
			s_gameWin = true;
			DelayToNextScene(tick, TITLE_SCENE);
		}
		s_sign[0].SetActive(true);
	}
}

void CSceneManager::ScenePrss(DWORD tick)
{
	switch (s_scene.scene_type)
	{
	case TITLE_SCENE: TitleScenePrss(tick); break;
	case TEST_SCENE: BattleScenePrss(tick); break;
	case FIRST_BATTLE_SCENE: BattleScenePrss(tick); break;
	case SECOND_BATTLE_SCENE: BattleScenePrss(tick); break;
	case THIRD_BATTLE_SCENE: BattleScenePrss(tick); break;
	}
}

void CSceneManager::DeleteScene()
{
	delete[] s_scene.predator;
	delete[] s_scene.slayer;
	delete[] s_scene.dominator;
	delete[] s_scene.devastator;
}

void CSceneManager::DelayToNextScene(DWORD tick, SCENETYPE type)
{
	DWORD delay = 3000;
	s_nextSceneInterval += tick;
	if (s_nextSceneInterval >= delay)
	{
		s_nextSceneInterval = 0;
		if (type == TITLE_SCENE)
			LoadTitleScene();
		else
			LoadBattleScene(type);
	}
}

void CSceneManager::CollisionPrss()
{
	DWORD amount = 0;
	amount = s_scene.player.GetNumBullet();
	for (DWORD i = 0; i < amount; i++)	// 플레이어 총알 충돌
	{
		DWORD num = 0;
		num = s_scene.num_pr;
		for (DWORD j = 0; j < num; j++)
		{
			if (s_scene.player.GetGun()->GetBullet(i)->CheckCollision(s_scene.predator[j].GetCollisionRect()) &&
				s_scene.predator[j].GetActive())
			{
				TurnEffect(KNIGHT_BULLET_EFFECT, s_scene.player.GetGun()->GetBullet(i)->GetPosition());
				s_scene.player.GetGun()->GetBullet(i)->SetActive(false);
				s_scene.predator[j].SetHp(s_scene.predator[j].GetHp() - 1);
			}
		}
		num = s_scene.num_sl;
		for (DWORD j = 0; j < num; j++)
		{
			if (s_scene.player.GetGun()->GetBullet(i)->CheckCollision(s_scene.slayer[j].GetCollisionRect()) &&
				s_scene.slayer[j].GetActive())
			{
				TurnEffect(KNIGHT_BULLET_EFFECT, s_scene.player.GetGun()->GetBullet(i)->GetPosition());
				s_scene.player.GetGun()->GetBullet(i)->SetActive(false);
				s_scene.slayer[j].SetHp(s_scene.slayer[j].GetHp() - 1);
			}
		}
		num = s_scene.num_dm;
		for (DWORD j = 0; j < num; j++)
		{
			if (s_scene.player.GetGun()->GetBullet(i)->CheckCollision(s_scene.dominator[j].GetCollisionRect()) &&
				s_scene.dominator[j].GetActive())
			{
				TurnEffect(KNIGHT_BULLET_EFFECT, s_scene.player.GetGun()->GetBullet(i)->GetPosition());
				s_scene.player.GetGun()->GetBullet(i)->SetActive(false);
				s_scene.dominator[j].SetHp(s_scene.dominator[j].GetHp() - 1);
			}
		}
		num = s_scene.num_dv;
		for (DWORD j = 0; j < num; j++)
		{
			if (s_scene.player.GetGun()->GetBullet(i)->CheckCollision(s_scene.devastator[j].GetCollisionRect()) &&
				s_scene.devastator[j].GetActive())
			{
				TurnEffect(KNIGHT_BULLET_EFFECT, s_scene.player.GetGun()->GetBullet(i)->GetPosition());
				s_scene.player.GetGun()->GetBullet(i)->SetActive(false);
				s_scene.devastator[j].SetHp(s_scene.devastator[j].GetHp() - 1);
			}
		}
	}
	if (s_scene.player.GetHp() <= 0)
		s_scene.player.SetHp(0);
	for (DWORD i = 0; i < s_scene.num_pr; i++) // predator 충돌
	{
		if (s_scene.predator[i].CheckCollision(s_scene.player.GetCollisionRect()) &&
			s_scene.player.GetActive())
		{
			s_scene.predator[i].SetHp(0);
			s_scene.player.SetHp(s_scene.player.GetHp() - 20);
		}
	}
	for (DWORD i = 0; i < s_scene.num_pr; i++)	// predator 총알 충돌
	{
		amount = s_scene.predator[i].GetNumBullet();
		for (DWORD j = 0; j < amount; j++)
		{
			if (s_scene.predator[i].GetGun()->GetBullet(j)->CheckCollision(s_scene.player.GetCollisionRect()) &&
				s_scene.player.GetActive())
			{
				TurnEffect(PREDATOR_BULLET_EFFECT, s_scene.predator[i].GetGun()->GetBullet(j)->GetPosition());
				s_scene.predator[i].GetGun()->GetBullet(j)->SetActive(false);
				s_scene.player.SetHp(s_scene.player.GetHp() - 5);
			}
		}
	}
	for (DWORD i = 0; i < s_scene.num_sl; i++) // slayer 충돌
	{
		if (s_scene.slayer[i].CheckCollision(s_scene.player.GetCollisionRect()) &&
			s_scene.player.GetActive())
		{
			s_scene.slayer[i].SetHp(0);
			s_scene.player.SetHp(s_scene.player.GetHp() - 50);
		}
	}
	for (DWORD i = 0; i < s_scene.num_dm; i++) // dominator 충돌
	{
		if (s_scene.dominator[i].CheckCollision(s_scene.player.GetCollisionRect()) &&
			s_scene.player.GetActive())
		{
			s_scene.dominator[i].SetHp(0);
			s_scene.player.SetHp(s_scene.player.GetHp() - 20);
		}
	}
	for (DWORD i = 0; i < s_scene.num_dm; i++)	// dominator 총알 충돌
	{
		amount = s_scene.dominator[i].GetNumBullet();
		for (DWORD j = 0; j < amount; j++)
		{
			if (s_scene.dominator[i].GetGun()->GetBullet(j)->CheckCollision(s_scene.player.GetCollisionRect()) &&
				s_scene.player.GetActive())
			{
				TurnEffect(DOMINATOR_BULLET_EFFECT, s_scene.dominator[i].GetGun()->GetBullet(j)->GetPosition());
				s_scene.dominator[i].GetGun()->GetBullet(j)->SetActive(false);
				s_scene.player.SetHp(s_scene.player.GetHp() - 20);
			}
		}
	}
	for (DWORD i = 0; i < s_scene.num_dv; i++) // devastator 충돌
	{
		if (s_scene.devastator[i].CheckCollision(s_scene.player.GetCollisionRect()) &&
			s_scene.player.GetActive())
		{
			s_scene.devastator[i].SetHp(0);
			s_scene.player.SetHp(0);
		}
	}
	for (DWORD i = 0; i < 50; i++)
	{
		if (s_effect[i].CheckCollision(s_scene.player.GetCollisionRect()) &&
			s_effect[i].GetEffectType() == DEVASTATOR_EXPOLSION_EFFECT && s_scene.player.GetActive())
		{
			s_scene.player.SetHp(0);
		}
	}
}

void CSceneManager::Start()
{
	LoadTitleScene();
	CreateSign();
	CreateEffTable();
	DAllocEff();

	s_scene.background.Start();

	s_scene.hpBar.Start();

	s_scene.player.Start();

	for (DWORD i = 0; i < s_scene.num_pr; i++)
		s_scene.predator[i].Start();
	for (DWORD i = 0; i < s_scene.num_sl; i++)
		s_scene.slayer[i].Start();
	for (DWORD i = 0; i < s_scene.num_dm; i++)
		s_scene.dominator[i].Start();
	for (DWORD i = 0; i < s_scene.num_dv; i++)
		s_scene.devastator[i].Start();
}

void CSceneManager::OnUpdate(HWND hWnd, DWORD tick)
{
	if (hWnd == NULL)
		return;

	Color color(0, 0, 0);
	s_BackBuffer->Clear(color);

	ScenePrss(tick);
	ShowSign(tick);

	s_scene.background.Update(s_BackBuffer, tick);

	s_scene.hpBar.Update(s_BackBuffer, tick);

	s_scene.player.Update(s_BackBuffer, tick);
	
	for (DWORD i = 0; i < s_scene.num_pr; i++)
		s_scene.predator[i].Update(s_BackBuffer, tick);
	for (DWORD i = 0; i < s_scene.num_sl; i++)
		s_scene.slayer[i].Update(s_BackBuffer, tick);
	for (DWORD i = 0; i < s_scene.num_dm; i++)
		s_scene.dominator[i].Update(s_BackBuffer, tick);
	for (DWORD i = 0; i < s_scene.num_dv; i++)
		s_scene.devastator[i].Update(s_BackBuffer, tick);
	for (DWORD i = 0; i < 50; i++)
		s_effect[i].Update(s_BackBuffer, tick);

	for (DWORD i = 0; i < 3; i++)
		s_sign[i].Update(s_BackBuffer, tick);

	CollisionPrss();
}

void CSceneManager::MessageLoof(HWND hwnd, HDC hDC)
{
	MSG msg;
	DWORD tick = GetTickCount();
	while (1)
	{
		//윈도우 메세지가 있을경우 메세지를 처리한다.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else //메세지가 없을 경우 게임 루프를 실행한다.
		{
			DWORD curTick = GetTickCount();
			OnUpdate(hwnd, curTick - tick);
			tick = curTick;

			s_MainBuffer->DrawImage(s_Bitmap, 0, 0);
		}
		if (!GetGameLoop())
			break;
	}

	DeleteEff();

	ReleaseBuffer(hwnd, hDC);

	DeleteScene();
}
