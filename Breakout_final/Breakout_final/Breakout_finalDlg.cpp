#pragma once
#include "stdafx.h"
#include "Breakout_finalDlg.h"
#include "Breakout_final.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/*Pendientes:
- Mejorar las colisiones
- Que los objetos no se acoplen cuando pasan uno encima del otro
*/

CBreakoutfinalDlg::CBreakoutfinalDlg(CWnd* pParent)
	: CDialog(IDD_BREAKOUT_FINAL_DIALOG, pParent)
	, m_nivelActual(_T(""))
	, m_ultimoNivel(_T(""))
	, m_vidas(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBreakoutfinalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMAGE, m_playArea);
	DDX_Control(pDX, IDC_BUTTON2, m_editar);
	DDX_Control(pDX, IDC_BUTTON1, m_jugar);
	DDX_Control(pDX, IDC_BUTTON3, m_crearNivel);
	DDX_Control(pDX, IDC_BUTTON4, m_crearBloque);
	DDX_Control(pDX, IDC_BUTTON5, m_crearPelota);
	DDX_Control(pDX, IDC_BUTTON6, m_guardarCambios);
	DDX_Control(pDX, IDC_BUTTON7, m_crearBloqueResistente);
	DDX_Control(pDX, IDC_BUTTON8, m_crearBloqueIrrompible);
	DDX_Control(pDX, IDC_BUTTON9, m_anterior);
	DDX_Control(pDX, IDC_BUTTON10, m_siguiente);
	DDX_Text(pDX, IDC_EDIT1, m_nivelActual);
	DDX_Text(pDX, IDC_EDIT2, m_ultimoNivel);
	DDX_Text(pDX, IDC_EDIT3, m_vidas);
	DDX_Control(pDX, IDC_BUTTON11, m_crear);
}

BEGIN_MESSAGE_MAP(CBreakoutfinalDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDOK, &CBreakoutfinalDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CBreakoutfinalDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CBreakoutfinalDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CBreakoutfinalDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CBreakoutfinalDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CBreakoutfinalDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CBreakoutfinalDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CBreakoutfinalDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CBreakoutfinalDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CBreakoutfinalDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CBreakoutfinalDlg::OnBnClickedButton10)
	ON_EN_CHANGE(IDC_EDIT1, &CBreakoutfinalDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CBreakoutfinalDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CBreakoutfinalDlg::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_BUTTON11, &CBreakoutfinalDlg::OnBnClickedButton11)
END_MESSAGE_MAP()

HCURSOR CBreakoutfinalDlg::OnQueryDragIcon()
{
	return static_cast <HCURSOR> (m_hIcon);
}

//Aqui empieza mi codigo
#include "Headers.h"
#include "CGame.h"

//Creo un objeto juego y un indice para determinar en qué nivel me encuentro
CGame juego(10, 1, 5);

//Cuando inicia el programa
BOOL CBreakoutfinalDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	//Oculta los botones del editor de niveles
	m_anterior.ShowWindow(SW_HIDE);
	m_siguiente.ShowWindow(SW_HIDE);
	m_crearNivel.ShowWindow(SW_HIDE);
	m_crearBloque.ShowWindow(SW_HIDE);
	m_crearPelota.ShowWindow(SW_HIDE);
	m_guardarCambios.ShowWindow(SW_HIDE);
	m_crearBloqueResistente.ShowWindow(SW_HIDE);
	m_crearBloqueIrrompible.ShowWindow(SW_HIDE);

	//Obtiene el contexto del dispositivo actual
	m_DC = this->GetDC();

	//Asigna el tamaño del area del area de juego
	m_playArea.GetClientRect(&juego.m_areaLimit);

	//Crea un primer nivel vacio
	juego.m_level.push_back(new CLevel(juego.m_areaLimit, m_DC));

	//Carga la partida guardada
	juego.LoadGame(m_DC);

	//Establece la cantidad de veces que se ejecutará todo el código en un segundo
	SetTimer(1, 33, NULL);

	return TRUE;
}

//Cuando se mueve el mouse
void CBreakoutfinalDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	//Si el modo edicion está activo
	if (juego.m_isCreating)
	{
		juego.EditorMovement(point, m_isClic);
	}

	//Si el modo juego está activo
	if (juego.m_isPlaying)
	{
		juego.m_level[juego.m_index]->m_bar->Movement(juego.m_areaLimit, point);
	}
}

//En cada frame
void CBreakoutfinalDlg::OnTimer(UINT_PTR nIDEvent)
{
	//Actualiza el nivel en el que se encuentra el jugador y cuantos hay en el juego
	m_nivelActual = to_string(juego.m_index + 1).c_str();
	m_ultimoNivel = to_string(juego.m_level.size()).c_str();
	m_vidas = to_string(juego.m_lifes).c_str();
	UpdateData(FALSE);

	//Calcula el centro de todos los objetos
	juego.CenterCalc();
	
	//Si el jugador está jugando
	if(juego.m_isPlaying)
	{
		//Movimiento
		juego.Movement(m_DC);
		//Colision de las pelotas
		juego.Collision();
		//Y destructor de objetos
		juego.Destroyer();

		//Llamo a la funcion de condicion de triunfo
		juego.PlayConditions();
		//Revisa si el jugador termino con los bloques del nivel y pasa al siguiente
		juego.LevelChanger();

		//Revisa si la ultima pelota salio de rango, se reduce en uno la vida
		juego.LifeChecker();

		//Si todos los bloques del ultimo nivel se destruyeron o el jugador perdió todas las vidas
		if (juego.m_win || juego.m_lose)
		{
			OnBnClickedOk();
		}

	}
	
	OnPaint();
	CDialog::OnTimer(nIDEvent);
}

//Renderizado
void CBreakoutfinalDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}

	else
	{
		juego.Paint(m_DC);

		CDialog::OnPaint();
	}
}

//Modo juego
void CBreakoutfinalDlg::OnBnClickedButton1()
{
	juego.m_isPlaying = true;
	juego.m_isCreating = false;

	m_jugar.ShowWindow(SW_HIDE);
	m_crear.ShowWindow(SW_HIDE);
	m_editar.ShowWindow(SW_HIDE);
	m_anterior.ShowWindow(SW_HIDE);
	m_siguiente.ShowWindow(SW_HIDE);
	m_crearNivel.ShowWindow(SW_HIDE);
	m_crearPelota.ShowWindow(SW_HIDE);
	m_crearBloque.ShowWindow(SW_HIDE);
	m_guardarCambios.ShowWindow(SW_HIDE);
	m_crearBloqueResistente.ShowWindow(SW_HIDE);
	m_crearBloqueIrrompible.ShowWindow(SW_HIDE);

	juego.m_index = 0;
}

//Modo editar
void CBreakoutfinalDlg::OnBnClickedButton2()
{
	juego.m_isCreating = true;
	juego.m_isPlaying = false;

	m_crear.ShowWindow(SW_HIDE);
	m_editar.ShowWindow(SW_HIDE);
	m_anterior.ShowWindow(SW_SHOW);
	m_siguiente.ShowWindow(SW_SHOW);
	m_crearNivel.ShowWindow(SW_SHOW);
	m_crearPelota.ShowWindow(SW_SHOW);
	m_crearBloque.ShowWindow(SW_SHOW);
	m_guardarCambios.ShowWindow(SW_SHOW);
	m_crearBloqueResistente.ShowWindow(SW_SHOW);
	m_crearBloqueIrrompible.ShowWindow(SW_SHOW);
}

//Crear nivel
void CBreakoutfinalDlg::OnBnClickedButton3()
{
	juego.m_level.push_back(new CLevel(juego.m_areaLimit, m_DC));
	juego.m_index++;
}

//Crear bloque comun
void CBreakoutfinalDlg::OnBnClickedButton4()
{
	juego.m_level[juego.m_index]->m_block.push_back(new CBlock(m_DC, 0));
}

//Crear bloque resistente
void CBreakoutfinalDlg::OnBnClickedButton7()
{
	juego.m_level[juego.m_index]->m_block.push_back(new CBlock(m_DC, 1));
}

//Crear bloque irrompible
void CBreakoutfinalDlg::OnBnClickedButton8()
{
	juego.m_level[juego.m_index]->m_block.push_back(new CBlock(m_DC, 3));
}

//Crear pelota
void CBreakoutfinalDlg::OnBnClickedButton5()
{
	juego.m_level[juego.m_index]->m_ball.push_back(new CBall(m_DC));
}

//Guardar cambios
void CBreakoutfinalDlg::OnBnClickedButton6()
{
	juego.SaveGame();
}

//Presionar clic
void CBreakoutfinalDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_isClic = true;

	CDialog::OnLButtonDown(nFlags, point);
}

//Soltar clic
void CBreakoutfinalDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (juego.m_isPlaying && juego.m_level[juego.m_index]->m_ball[0]->m_speed.x == 0)
	{
		juego.BallInit();
	}

	m_isClic = false;

	CDialog::OnLButtonUp(nFlags, point);
}

//Cerrar juego
void CBreakoutfinalDlg::OnBnClickedOk()
{
	CDialog::OnOK();
}

//Nivel anterior
void CBreakoutfinalDlg::OnBnClickedButton9()
{
	if (juego.m_index > 0)
	{
		juego.m_index--;
	}
}

//Siguiente nivel
void CBreakoutfinalDlg::OnBnClickedButton10()
{
	if (juego.m_index < juego.m_level.size() - 1)
	{
		juego.m_index++;
	}
}

//Imprimir nivel actual
void CBreakoutfinalDlg::OnEnChangeEdit1()
{

}

//Imprimir nivel maximo
void CBreakoutfinalDlg::OnEnChangeEdit2()
{

}

//Imprimir conteo de vidas
void CBreakoutfinalDlg::OnEnChangeEdit3()
{

}

//Modo crear
void CBreakoutfinalDlg::OnBnClickedButton11()
{
	juego.m_isCreating = true;
	juego.m_isPlaying = false;

	m_crear.ShowWindow(SW_HIDE);
	m_editar.ShowWindow(SW_HIDE);
	m_anterior.ShowWindow(SW_SHOW);
	m_siguiente.ShowWindow(SW_SHOW);
	m_crearNivel.ShowWindow(SW_SHOW);
	m_crearPelota.ShowWindow(SW_SHOW);
	m_crearBloque.ShowWindow(SW_SHOW);
	m_guardarCambios.ShowWindow(SW_SHOW);
	m_crearBloqueResistente.ShowWindow(SW_SHOW);
	m_crearBloqueIrrompible.ShowWindow(SW_SHOW);

	for (int i = 1; i < juego.m_level.size(); i++)
	{
		juego.m_level[i]->~CLevel();
		juego.m_level.erase(juego.m_level.begin() + i);
	}

	for (int i = 1; i < juego.m_level[0]->m_ball.size(); i++)
	{
		juego.m_level[0]->m_ball[i]->~CBall();
		juego.m_level[0]->m_ball.erase(juego.m_level[0]->m_ball.begin() + i);
	}

	for (int i = 0; i < juego.m_level[0]->m_block.size(); i++)
	{
		juego.m_level[0]->m_block[i]->~CBlock();
		juego.m_level[0]->m_block.erase(juego.m_level[0]->m_block.begin() + i);
	}
}
