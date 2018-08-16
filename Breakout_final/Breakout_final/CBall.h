#pragma once
#include "Headers.h"

class CBall
{
public:
	CPoint m_speed;
	CPoint m_center;
	CPoint m_pos;
	SIZE m_size;

	HANDLE m_hBitmap;
	CDC m_bmDC;

	CBall(CDC*pDC);
	~CBall();

	void Collision(RECT areaLimit);
	void Movement(RECT areaLimit, CBar* bar);
	void Paint(CDC* pDC);
};