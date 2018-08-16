#pragma once
#include "Headers.h"

class CBar
{
public:

	CPoint m_pos;
	CPoint m_center;
	SIZE m_size;
	CString m_mousePosX;
	
	HANDLE m_hBitmap;
	CDC m_bmDC;

	CBar(CDC*pDC);
	CBar(int posY, CDC*pDC);

	~CBar();

	void Movement(RECT areaLimit, CPoint point);
	void Collision(vector <CBall*> ball);
	void Paint(CDC* pDC);
};

