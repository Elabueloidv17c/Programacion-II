#pragma once
#include "stdafx.h"
#include "CGame.h"

void CGame::Paint(CDC* DC)
{
	//Pinto el fondo
	m_level[m_index]->PaintCanvas(DC, m_areaLimit);

	for (int j = 0; j < m_level[m_index]->m_ball.size(); j++)
	{
		if ((m_level[m_index]->m_ball[j]->m_pos.x + m_level[m_index]->m_ball[j]->m_size.cx) <= m_areaLimit.right)
		{
			//Pinto las pelotas
			m_level[m_index]->m_ball[j]->Paint(DC);
		}
	}

	for (int k = 0; k < m_level[m_index]->m_block.size(); k++)
	{
		if ((m_level[m_index]->m_block[k]->m_pos.x + m_level[m_index]->m_block[k]->m_size.cx) <= m_areaLimit.right)
		{
			//Pinto los bloques
			m_level[m_index]->m_block[k]->Paint(DC);
		}
	}

	if ((m_level[m_index]->m_bar->m_pos.x + m_level[m_index]->m_bar->m_size.cx) <= m_areaLimit.right)
	{
		//Pinto la barra
		m_level[m_index]->m_bar->Paint(DC);
	}
}

void CGame::CenterCalc()
{
	//Calculo el centro de la barra
	m_level[m_index]->m_bar->m_center.x = m_level[m_index]->m_bar->m_pos.x + (m_level[m_index]->m_bar->m_size.cx / 2);
	m_level[m_index]->m_bar->m_center.y = m_level[m_index]->m_bar->m_pos.y + (m_level[m_index]->m_bar->m_size.cy / 2);

	for (int j = 0; j < m_level[m_index]->m_ball.size(); j++)
	{
		//Calculo el centro de las pelotas
		m_level[m_index]->m_ball[j]->m_center.x = m_level[m_index]->m_ball[j]->m_pos.x + (m_level[m_index]->m_ball[j]->m_size.cx / 2);
		m_level[m_index]->m_ball[j]->m_center.y = m_level[m_index]->m_ball[j]->m_pos.y + (m_level[m_index]->m_ball[j]->m_size.cy / 2);
	}

	for (int k = 0; k < m_level[m_index]->m_block.size(); k++)
	{
		//Calculo el centro de los bloques
		m_level[m_index]->m_block[k]->m_center.x = m_level[m_index]->m_block[k]->m_pos.x + (m_level[m_index]->m_block[k]->m_size.cx / 2);
		m_level[m_index]->m_block[k]->m_center.y = m_level[m_index]->m_block[k]->m_pos.y + (m_level[m_index]->m_block[k]->m_size.cy / 2);
	}
}

void CGame::EditorMovement(CPoint point, bool isClic) 
{
	//Verifico si el clic está activo
	if (isClic)
	{
		//Reviso si el puntero está encima de alguna pelota
		for (int j = 1; j < m_level[m_index]->m_ball.size(); j++)
		{
			if (abs(m_level[m_index]->m_ball[j]->m_center.x - point.x) < (m_level[m_index]->m_ball[j]->m_size.cx / 2) &&
				abs(m_level[m_index]->m_ball[j]->m_center.y - point.y) < (m_level[m_index]->m_ball[j]->m_size.cy / 2))
			{
				//Muevo la pelota a la posicion del puntero del mouse
				m_level[m_index]->m_ball[j]->m_pos.x = point.x - m_level[m_index]->m_ball[j]->m_size.cx / 2;
				m_level[m_index]->m_ball[j]->m_pos.y = point.y - m_level[m_index]->m_ball[j]->m_size.cy / 2;

				//Si el objeto sale del limite derecho de la pantalla, lo acomoda justo a la orilla
				if ((m_level[m_index]->m_ball[j]->m_pos.x + m_level[m_index]->m_ball[j]->m_size.cx) > m_areaLimit.right)
				{
					m_level[m_index]->m_ball[j]->m_pos.x = m_areaLimit.right - m_level[m_index]->m_ball[j]->m_size.cx;
					return;
				}
			}
		}

		//Reviso si el puntero está encima de algun bloque
		for (int k = 0; k < m_level[m_index]->m_block.size(); k++)
		{
			if (abs(m_level[m_index]->m_block[k]->m_center.x - point.x) < (m_level[m_index]->m_block[k]->m_size.cx / 2) &&
				abs(m_level[m_index]->m_block[k]->m_center.y - point.y) < (m_level[m_index]->m_block[k]->m_size.cy / 2))
			{
				//Muevo el bloque a la posicion del puntero del mouse
				m_level[m_index]->m_block[k]->m_pos.x = point.x - m_level[m_index]->m_block[k]->m_size.cx / 2;
				m_level[m_index]->m_block[k]->m_pos.y = point.y - m_level[m_index]->m_block[k]->m_size.cy / 2;
				
				//Si el objeto sale del limite derecho de la pantalla, lo acomoda justo a la orilla
				if ((m_level[m_index]->m_block[k]->m_pos.x + m_level[m_index]->m_block[k]->m_size.cx) > m_areaLimit.right)
				{
					m_level[m_index]->m_block[k]->m_pos.x = m_areaLimit.right - m_level[m_index]->m_block[k]->m_size.cx;
					return;
				}
			}
		}
	}
}

void CGame::PlayConditions()
{
	int counter = 0;

	for (int i = m_index; i < m_level.size(); i++)
	{
		if (m_level[i]->m_block.size() == 0)
		{
			m_levelComplete = true;
		}

		else
		{
			for (int j = 0; j < m_level[i]->m_block.size(); j++)
			{
				if (m_level[i]->m_block[j]->m_breakable == true)
				{
					counter++;
				}
			}
		}
	}

	if (counter == 0)
	{
		m_levelComplete = true;
	}

	if (m_lifes == 0)
	{
		m_lose = true;
	}
}

void CGame::BallInit()
{
	//Asigno la velocidad inicial a la primera pelota
	m_level[m_index]->m_ball[0]->m_speed = m_initBallSpeed;

	//Para cada pelota en el nivel
	for (int i = 1; i < m_level[m_index]->m_ball.size(); i++)
	{
		//La pelota inicial va hacia arriba, por lo tanto cada pelota adicional va en la direccion contraria (abajo)
		m_level[m_index]->m_ball[i]->m_speed.y = -m_level[m_index]->m_ball[0]->m_speed.y;
		
		//Si lapelota está al lado derecho, su desplazamiento en x será hacia la izquierda (movimiento inverso a la pelota inicial)
		if (m_level[m_index]->m_ball[i]->m_center.x > (m_areaLimit.left + (m_areaLimit.right / 2)))
		{
			m_level[m_index]->m_ball[i]->m_speed.x = -m_level[m_index]->m_ball[0]->m_speed.x;
		}

		//Si está en el lado izquierdo, su desplazamiento será hacia la derecha (misma direccion que la pelota inicial)
		else
		{
			m_level[m_index]->m_ball[i]->m_speed.x = m_level[m_index]->m_ball[0]->m_speed.x;
		}
	}
}

void CGame::LevelChanger()
{
	if (m_levelComplete && m_index < m_level.size() - 1) 
	{
		m_levelComplete = false;
		m_collitionCounter = 0;
		m_level[m_index]->m_ball[0]->m_speed = m_initBallSpeed;
		m_index++;
	}

	if (m_levelComplete && (m_index + 1) == m_level.size())
	{
		m_win = true;
	}
}

void CGame::LifeChecker()
{
	if (m_level[m_index]->m_ball.size() == 1 && m_level[m_index]->m_ball[0]->m_pos.y > m_areaLimit.bottom)
	{
		m_lifes -= 1;
		m_level[m_index]->m_ball[0]->m_speed.x = 0;
		m_level[m_index]->m_ball[0]->m_speed.y = 0;
	}

	if (m_lifes == 0)
	{
		m_lose = true;
	}
}

void CGame::SaveGame()
{
	ofstream* writter = new ofstream;

	writter->open("partida");

	*writter << m_level.size() << '\n';

	for (int i = 0; i < m_level.size(); i++)
	{
		*writter << m_level[i]->m_block.size() << '\n';

		for (int j = 0; j <  m_level[i]->m_block.size(); j++)
		{
			if (m_level[i]->m_block[j]->m_resistance == 1)
			{
				*writter << 0 << '\n';
			}

			else if (m_level[i]->m_block[j]->m_resistance == 2)
			{
				*writter << 1 << '\n';
			}

			else
			{
				*writter << 2 << '\n';
			}

			*writter << m_level[i]->m_block[j]->m_pos.x << '\n';
			*writter << m_level[i]->m_block[j]->m_pos.y << '\n';
		}
	}

	for (int i = 0; i < m_level.size(); i++)
	{
		*writter << m_level[i]->m_ball.size() << '\n';

		for (int j = 1; j < m_level[i]->m_ball.size(); j++)
		{
			*writter << m_level[i]->m_ball[j]->m_pos.x << '\n';
			*writter << m_level[i]->m_ball[j]->m_pos.y << '\n';
		}
	}

	writter->close();
}

//Cargar juego
void CGame::LoadGame(CDC* DC)
{
	//Creo una variable para leer el archivo y otras para almacenar los datos
	ifstream* reader = new ifstream;
	reader->open("partida");
	vector <short> datos;
	short dato;

	//Leo cada dato del archivo y lo almaceno
	while (!reader->eof())
	{
		*reader >> dato;
		datos.push_back(dato);
	}

	reader->close();

	//Si no se leyeron datos suficuentes (si no hay una partida guardada)
	if (datos.size() < 2)
	{
		//Salgo del metodo
		return;
	}

	//Creo un indice para recorrer el vector de los datos que leí (en cada acción realizada incremento dicho indice)
	int index = 0;

	//Le doy el tamaño leido en el archivo al vector de niveles
	m_level.resize(datos[index++]);

	//Para cada nivel del juego
	for (int i = 0; i < m_level.size(); i++)
	{
		//Si el nivel no ha sido creado
		if (m_level[i] == NULL)
		{
			//Lo crea
			m_level[i] = new CLevel(m_areaLimit, DC);
		}

		//Le doy el tamaño leido en el archivo al vector de bloques del nivel actual
		m_level[i]->m_block.resize(datos[index++]);

		//Para cada bloque del nivel actual
		for (int j = 0; j < m_level[i]->m_block.size(); j++)
		{
			//Crea el objeto
			m_level[i]->m_block[j] = new CBlock(DC, datos[index++]);

			//Y le asigna la posicion leída en el archivo
			m_level[i]->m_block[j]->m_pos.x = datos[index++];
			m_level[i]->m_block[j]->m_pos.y = datos[index++];
		}
	}

	//Para cada nivel del juego
	for (int i = 0; i < m_level.size(); i++)
	{
		//Le doy el tamaño leido en el archivo al vector de pelotas del nivel actual
		m_level[i]->m_ball.resize(datos[index++]);

		//Para cada pelota del nivel actual (desde la segunda)
		for (int j = 1; j < m_level[i]->m_ball.size(); j++)
		{
			//Crea el objeto
			m_level[i]->m_ball[j] = new CBall(DC);

			//Y le asigna la posicion leida en el archivo
			m_level[i]->m_ball[j]->m_pos.x = datos[index++];
			m_level[i]->m_ball[j]->m_pos.y = datos[index++];
		}
	}
}

//Movimiento de las pelotas
void CGame::Movement(CDC* DC)
{
	//Si la pelota acaba de caer
	if (m_level[m_index]->m_ball[0]->m_speed.x == 0)
	{
		//La posiciono sobre la barra
		m_level[m_index]->m_ball[0]->m_pos.x = (m_level[m_index]->m_bar->m_pos.x + m_level[m_index]->m_bar->m_size.cx) - 
		m_level[m_index]->m_ball[0]->m_size.cx;

		m_level[m_index]->m_ball[0]->m_pos.y = m_level[m_index]->m_bar->m_pos.y - m_level[m_index]->m_bar->m_size.cy * 2;
	}

	//Para cada pelota en el juego, llamo su funcion de movimiento
	for (int j = 0; j < m_level[m_index]->m_ball.size(); j++)
	{
		m_level[m_index]->m_ball[j]->Movement(m_areaLimit, m_level[m_index]->m_bar);
	}

	//Limitador de velocidad para la pelota
	if (abs(m_level[m_index]->m_ball[0]->m_speed.x) > 18)
	{
		return;
	}

	//Incrementador de velocidad
	if (m_hitCounter > 0 && m_hitCounter % 3 == 0)
	{
		if (m_level[m_index]->m_ball[0]->m_speed.x > 0)
		{
			m_level[m_index]->m_ball[0]->m_speed.x += m_speedBoost;
		}

		else
		{
			m_level[m_index]->m_ball[0]->m_speed.x -= m_speedBoost;
		}

		if (m_level[m_index]->m_ball[0]->m_speed.y > 0)
		{
			m_level[m_index]->m_ball[0]->m_speed.y += m_speedBoost;
		}

		else
		{
			m_level[m_index]->m_ball[0]->m_speed.y -= m_speedBoost;
		}
	}
}

//Colisiones (Necesita trabajo)
void CGame::Collision()
{
	//Colisiones con el escenario
	m_level[m_index]->Collition(m_areaLimit);

	//Colisiones de la barra
	m_level[m_index]->m_bar->Collision(m_level[m_index]->m_ball/*Necesita edicion*/);

	//Colisiones de cada bloque
	for (int i = 0; i < m_level[m_index]->m_block.size(); i++)
	{
		m_level[m_index]->m_block[i]->Collision(m_level[m_index]->m_ball, m_hitCounter/*Necesita edicion*/);
	}
}

//Destructor de bloques y pelotas
void CGame::Destroyer()
{
	//Para cada bloque
	for (int i = 0; i < m_level[m_index]->m_block.size(); i++)
	{
		//Si su resitencia se termina
		if (m_level[m_index]->m_block[i]->m_resistance == 0)
		{
			//Libera la memoria y elimina el indice del vector
			delete(m_level[m_index]->m_block[i]);
			m_level[m_index]->m_block.erase(m_level[m_index]->m_block.begin() + i);
		}
	}

	//Para cada pelota (desde la segunda)
	for (int i = 1; i < m_level[m_index]->m_ball.size(); i++)
	{//La primer pelota no se destruye porque siempre está en juego, aunque pierdas una vida, solo se reubica
		//Si la pelota sobrepasa el limite inferior del area de juego
		if (m_level[m_index]->m_ball[i]->m_pos.y > m_areaLimit.bottom)
		{
			//Libera la memoria y elimina el indice del vector
			delete(m_level[m_index]->m_ball[i]);
			m_level[m_index]->m_ball.erase(m_level[m_index]->m_ball.begin() + i);
		}
	}
}

//Constructor
CGame::CGame(int ballSpeed, int boost, int lifes)
{
	m_levelComplete = false;
	m_isCreating = false;
	m_isPlaying = false;
	m_win = false;

	m_hitCounter = 0;
	m_index = 0;

	m_lifes = lifes;
	m_speedBoost = boost;
	m_initBallSpeed.x = ballSpeed;
	m_initBallSpeed.y = -ballSpeed;
}

//Destructor
CGame::~CGame()
{
	//Para cada nivel
	for (int i = 0; i < m_level.size(); i++)
	{
		//Para cada pelota de ese nivel
		for (int j = 0; j < m_level[i]->m_ball.size(); j++)
		{
			//Libero la memoria
			delete m_level[i]->m_ball[j];
		}

		//Para cada bloque de ese nivel
		for (int k = 0; k < m_level[i]->m_block.size(); k++)
		{
			//Libero la memoria
			delete m_level[i]->m_block[k];
		}

		//Libero la memoria de la barra de ese nivel
		delete m_level[i]->m_bar;
	}
}