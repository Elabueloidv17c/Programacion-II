#pragma once
#include "stdafx.h"
#include "CBall.h"
#include "CBar.h"

CBar::CBar(CDC*pDC)
{
	m_pos.x = 0;
	m_pos.y = 0;

	m_hBitmap = LoadImage(0, TEXT("Barra Perrona.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	CBitmap bmp;
	bmp.Attach(reinterpret_cast<HBITMAP>(m_hBitmap));

	BITMAP bitmap;
	bmp.GetBitmap(&bitmap);

	m_size.cx = bitmap.bmWidth;
	m_size.cy = bitmap.bmHeight;

	m_bmDC.CreateCompatibleDC(pDC);
	CBitmap* oldBMP = m_bmDC.SelectObject(&bmp);
}

CBar::CBar(int posY, CDC*pDC)
{
	m_pos.y = posY;

	m_hBitmap = LoadImage(0, TEXT("Barra Perrona.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	CBitmap bmp;
	bmp.Attach(reinterpret_cast<HBITMAP>(m_hBitmap));

	BITMAP bitmap;
	bmp.GetBitmap(&bitmap);

	m_size.cx = bitmap.bmWidth;
	m_size.cy = bitmap.bmHeight;

	m_bmDC.CreateCompatibleDC(pDC);
	CBitmap* oldBMP = m_bmDC.SelectObject(&bmp);
}

CBar::~CBar(){}

void CBar::Movement(RECT areaLimit, CPoint point)
{
	if (m_pos.x < areaLimit.left)
	{
		m_pos.x = areaLimit.left;
	}

	else if ((m_pos.x + m_size.cx) > areaLimit.right)
	{
		m_pos.x = areaLimit.right - m_size.cx;
	}

	else
	{
		m_pos.x = point.x;
		m_pos.x = m_pos.x - (m_size.cx / 2);
	}
}

void CBar::Collision(vector <CBall*> ball)
{
	CPoint barMid;
	CPoint ballMid;

	int collitionX;
	int collitionY;
	int x;
	int y;

	for (int i = 0; i < ball.size(); i++)
	{
		barMid.x = m_pos.x + (m_size.cx / 2);
		barMid.y = m_pos.y + (m_size.cy / 2);

		ballMid.x = ball[i]->m_pos.x + (ball[i]->m_size.cx / 2);
		ballMid.y = ball[i]->m_pos.y + (ball[i]->m_size.cy / 2);

		x = abs(barMid.x - ballMid.x);
		y = abs(barMid.y - ballMid.y);

		collitionX = (m_size.cx + ball[i]->m_size.cx) / 2;
		collitionY = (m_size.cy + ball[i]->m_size.cy) / 2;

		if ((x + ball[i]->m_speed.y) < collitionX && y < collitionY)
		{
			if ((ball[i]->m_pos.y + ball[i]->m_size.cy) > m_pos.y)
			{
				ball[i]->m_speed.y = -ball[i]->m_speed.y;
			}

			if (ball[i]->m_speed.x > 0 && ballMid.x < barMid.x)
			{
				ball[i]->m_speed.x = -ball[i]->m_speed.x;
				return;
			}

			if (ball[i]->m_speed.x < 0 && ballMid.x > barMid.x)
			{
				ball[i]->m_speed.x = -ball[i]->m_speed.x;
				return;
			}
		}
	}
}

void CBar::Paint(CDC* pDC)
{
	pDC->BitBlt(m_pos.x, m_pos.y, m_size.cx, m_size.cx, &m_bmDC, 0, 0, SRCCOPY);
}