#pragma once
#include "Headers.h"

class CBlock
{
public:

	CPoint m_pos;
	CPoint m_center;

	SIZE m_size;

	int m_resistance;
	
	bool m_breakable;
	
	HANDLE m_hBitmap;
	CDC m_bmDC;

	void Collision(vector <CBall*> ball, int &hitCounter);
	void Paint(CDC* pDC);

	CBlock(CDC*pDC, int type);
	~CBlock();
};

