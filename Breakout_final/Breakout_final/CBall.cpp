#pragma once
#include "stdafx.h"
#include "CBall.h"
#include "CBar.h"


CBall::CBall(CDC*pDC)
{
	m_pos.x = 0;
	m_pos.y = 0;

	m_hBitmap = LoadImage(0, TEXT("Pelota Chingona.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	CBitmap bmp;
	bmp.Attach(reinterpret_cast<HBITMAP>(m_hBitmap));

	BITMAP bitmap;
	bmp.GetBitmap(&bitmap);

	m_size.cx = bitmap.bmWidth;
	m_size.cy = bitmap.bmHeight;

	m_bmDC.CreateCompatibleDC(pDC);
	CBitmap* oldBMP = m_bmDC.SelectObject(&bmp);
}

CBall::~CBall() {}

void CBall::Movement(RECT areaLimit, CBar* bar)
{
	if ((m_pos.x + m_size.cx) > areaLimit.right)
	{
		m_pos.x = areaLimit.right - m_size.cx;
	}

	m_pos.x += m_speed.x;
	m_pos.y += m_speed.y;
}

void CBall::Collision(RECT areaLimit)
{
	if (m_pos.y < areaLimit.top)
	{
		m_speed.y = -m_speed.y;
	}

	if (m_pos.x < areaLimit.left || (m_pos.x + m_size.cx) > areaLimit.right)
	{
		m_speed.x = -m_speed.x;
	}
}

void CBall::Paint(CDC* pDC)
{
	pDC->BitBlt(m_pos.x, m_pos.y, m_size.cx, m_size.cx, &m_bmDC, 0, 0, SRCCOPY);
}