#pragma once
#include "stdafx.h"
#include "CBlock.h"
#include "CBall.h"

CBlock::CBlock(CDC*pDC, int type)
{
	m_pos.x = 0;
	m_pos.y = 0;

	if (type == 0)
	{
		m_hBitmap = LoadImage(0, TEXT("Bloque placozo.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		m_breakable = true;
		m_resistance = 1;
	}

	else if (type == 1)
	{
		m_hBitmap = LoadImage(0, TEXT("Bloque placozo resistente.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		m_breakable = true;
		m_resistance = 2;
	}

	else
	{
		m_hBitmap = LoadImage(0, TEXT("Bloque placozo irrompible.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		m_breakable = false;
		m_resistance = 3;
	}

	CBitmap bmp;
	bmp.Attach(reinterpret_cast<HBITMAP>(m_hBitmap));

	BITMAP bitmap;
	bmp.GetBitmap(&bitmap);

	m_size.cx = bitmap.bmWidth;
	m_size.cy = bitmap.bmHeight;

	m_bmDC.CreateCompatibleDC(pDC);
	CBitmap* oldBMP = m_bmDC.SelectObject(&bmp);
}

CBlock::~CBlock()
{
}

void CBlock::Collision(vector <CBall*> ball, int &hitCounter)
{
	CPoint blockMid;
	CPoint ballMid;
	int collitionX;
	int collitionY;
	int x;
	int y;

	blockMid.x = m_pos.x + (m_size.cx / 2);
	blockMid.y = m_pos.y + (m_size.cy / 2);

	for (int i = 0; i < ball.size(); i++)
	{
		ballMid.x = ball[i]->m_pos.x + (ball[i]->m_size.cx / 2);
		ballMid.y = ball[i]->m_pos.y + (ball[i]->m_size.cy / 2);

		x = abs(blockMid.x - ballMid.x);
		y = abs(blockMid.y - ballMid.y);

		collitionX = (m_size.cx + ball[i]->m_size.cx) / 2;
		collitionY = (m_size.cy + ball[i]->m_size.cy) / 2;

		if (x < collitionX && y < collitionY)
		{
			if (abs(x - collitionX) < abs(y - collitionY))
			{
				if (m_breakable)
				{
					m_resistance--;
				}

				ball[i]->m_speed.x = -ball[i]->m_speed.x;

				hitCounter++;
				return;
			}

			else
			{
				if (m_breakable)
				{
					m_resistance--;
				}

				ball[i]->m_speed.y = -ball[i]->m_speed.y;

				hitCounter++;
				return;
			}


		}
	}
}

void CBlock::Paint(CDC* pDC)
{
	pDC->BitBlt(m_pos.x, m_pos.y, m_size.cx, m_size.cx, &m_bmDC, 0, 0, SRCCOPY);
}
