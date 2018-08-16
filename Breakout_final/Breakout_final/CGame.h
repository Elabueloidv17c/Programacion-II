#pragma once
#include "Headers.h"
#include "CLevel.h"
#include "CBlock.h"
#include "CBall.h"
#include "CBar.h"

class CGame
{
public:

	vector <CLevel*> m_level;
	
	RECT m_areaLimit;
	CPoint m_initBallSpeed;

	int m_collitionCounter;
	int m_hitCounter;
	int m_speedBoost;
	int m_lifes;
	int m_index;

	bool m_isCreating;
	bool m_isPlaying;
	bool m_levelComplete;
	bool m_lose;
	bool m_win;

	void EditorMovement(CPoint point, bool isClic);
	void LoadGame(CDC* DC);
	void Movement(CDC* DC);
	void PlayConditions();
	void Paint(CDC* DC);
	void LevelChanger();
	void LifeChecker();
	void CenterCalc();
	void Collision();
	void Destroyer();
	void BallInit();
	void SaveGame();

	CGame(int ballSpeed, int boost, int lifes);
	~CGame();
};