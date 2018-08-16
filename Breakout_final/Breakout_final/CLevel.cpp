#pragma once
#include "stdafx.h"
#include "Headers.h"
#include "CLevel.h"
#include "CBall.h"
#include "CBar.h"

CLevel::CLevel(CRect areaLimit, CDC* DC)
{
	//Crea la barra
	m_bar = new CBar(areaLimit.bottom, DC);

	m_bar->m_pos.x = (areaLimit.left - (m_bar->m_size.cx / 2)) + (areaLimit.right / 2);
	m_bar->m_pos.y = m_bar->m_pos.y - m_bar->m_size.cy * 2;

	//Crea la pelota inicial y la posiciona encima de la barra
	m_ball.push_back(new CBall(DC));
	m_ball[0]->m_pos.x = (m_bar->m_pos.x + m_bar->m_size.cx) - m_ball[0]->m_size.cx;
	m_ball[0]->m_pos.y = m_bar->m_pos.y - m_bar->m_size.cy * 2;
}

CLevel::~CLevel() 
{
	delete m_bar;
	delete m_ball[0];
}

void CLevel::PaintCanvas(CDC* pDC, CRect areaLimit)
{
	pDC->MoveTo(areaLimit.left, areaLimit.top);
	pDC->Rectangle(areaLimit.left, areaLimit.top, areaLimit.right, areaLimit.bottom);
}

void CLevel::Collition(RECT areaLimit)
{
	for (int i = 0; i < m_ball.size(); i++)
	{
		if (m_ball[i]->m_pos.x <= areaLimit.left || (m_ball[i]->m_pos.x + m_ball[i]->m_size.cx) >= areaLimit.right)
		{
			m_ball[i]->m_speed.x = -m_ball[i]->m_speed.x;
		}

		if (m_ball[i]->m_pos.y <= areaLimit.top)
		{
			m_ball[i]->m_speed.y = -m_ball[i]->m_speed.y;
		}

		if (m_ball[i]->m_pos.x < areaLimit.left && m_ball[i]->m_speed.x > 0)
		{
			m_ball[i]->m_pos.x = areaLimit.left;
		}

		if (m_ball[i]->m_pos.x > areaLimit.right && m_ball[i]->m_speed.x < 0)
		{
			m_ball[i]->m_pos.x = areaLimit.right - m_ball[i]->m_size.cx;
		}

		if (m_ball[i]->m_pos.y < areaLimit.top && m_ball[i]->m_speed.y > 0)
		{
			m_ball[i]->m_pos.y = areaLimit.top;
		}
	}
}
