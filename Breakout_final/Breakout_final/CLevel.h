#pragma once
#include "Headers.h"

class CLevel
{
public:
	vector <CBall*> m_ball;
	vector <CBlock*> m_block;
	CBar* m_bar;

	CLevel(CRect areaLimit, CDC* DC);
	~CLevel();

	void Collition(RECT areaLimit);
	void PaintCanvas(CDC* pDC, CRect areaLimit);
};

