// ChildView.cpp: реализация класса CChildView
//

#include "stdafx.h"
#include "Lab08.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CChildView::CChildView()
{		
	Index = 0;
}

CChildView::~CChildView()
{
}

// Реализация карты сообщений
BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	// сообщения меню выбора

	ON_COMMAND(ID_Lines_Lagr, &CChildView::OnLagr)
	ON_COMMAND(ID_Lines_Bezier, &CChildView::OnBezier)
	ON_COMMAND(ID_Lines_Bezier1, &CChildView::OnBezier1)
	ON_COMMAND(ID_Lines_Bezier2, &CChildView::OnBezier2)
	ON_COMMAND(ID_Lines_Bezier3, &CChildView::OnBezier3)
END_MESSAGE_MAP()



// Обработчики сообщений CChildView

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint()
{
	CPaintDC dc(this); // контекст устройства для рисования

	if (Index == 1)
	{
		PenLine.Set(PS_SOLID, 1, RGB(0, 255, 0));
		Graph.SetPenLine(PenLine);
		Graph.Draw(dc, 1, 1);

		PenLine.Set(PS_SOLID, 1, RGB(255, 0, 0));
		Graph.SetPenLine(PenLine);
		//Graph.Draw(dc, 1, 1);
		Graph.DrawLagr(dc);
	}
	if (Index == 2)
	{
		Graph.Draw(dc, 0, 0);
		PenLine.Set(PS_SOLID, 1, RGB(0, 0, 255));
		Graph.SetPenLine(PenLine);
		Graph.DrawBezier(dc, 20);//кол-во сторон контуров
	}
}

void CChildView::OnLagr()
{
	double dx = pi / 4;
	double xL = 0;
	double xH = pi;
	int N = (xH - xL) / dx;
	X.RedimMatrix(N + 1);
	Y.RedimMatrix(N + 1);
	for (int i = 0; i <= N; i++)
	{
		X(i) = xL + i * dx;
		Y(i) = pow(2 + cos(X(i)), sin(2 * X(i)));
	}
	PenAxis.Set(PS_SOLID, 2, RGB(0, 0, 0));
	Graph.SetPenAxis(PenAxis);
	RW.SetRect(100, 50, 500, 350);
	Graph.SetParams(X, Y, RW);
	Index = 1;
	Invalidate();
}

void CChildView::OnBezier()
{

	RW.SetRect(100, 20, 700, 400);
	Bezier();
	Index = 2;
	this->Invalidate();
}

void CChildView::OnBezier1()
{
	RW.SetRect(100, 20, 700, 400);
	Bezier2();
	Index = 2;
	this->Invalidate();
}

void CChildView::OnBezier2()
{
	RW.SetRect(100, 20, 700, 400);
	Bezier3();
	Index = 2;
	this->Invalidate();
}

void CChildView::OnBezier3()
{
	RW.SetRect(100, 20, 700, 400);
	Bezier4();
	Index = 2;
	this->Invalidate();
}

//void CChildView::OnBezier4()
//{
//	double dt = pi / 4;
//	int N = 4;
//	X.RedimMatrix(N);
//	Y.RedimMatrix(N);
//	X(0) = 2*dt;
//	Y(0) = 0;
//	X(1) = 7 * dt;
//	Y(1) = 3;
//	X(2) = 0;
//	Y(2) = 3;
//	X(3) = 5 * dt;
//	Y(3) = 0;
//	N_Bezier = 50;
//	RW.SetRect(100, 50, 500, 350);
//	Graph.SetParams(X, Y, RW);
//	Index = 6;
//	this->Invalidate();
//}

void CChildView::Bezier() //координаты для безье
{

	CMatrix X(3);//в точке х
	CMatrix Y(3);
	X(0) = 0;
	Y(0) = 0;
	X(1) = -15; //	X(1) = 5; //для равномерной кривой
	Y(1) = 5;
	X(2) = 10; //	X(2) = 0; //для прямой безье
	Y(2) = 0;


	PenLine.Set(PS_SOLID, 1, RGB(255, 0, 0));//цвет графика

	//задаем параметры
	Graph.SetParams(X, Y, RW);
	Graph.SetPenLine(PenLine);
	Graph.SetPenAxis(PenAxis);
}

void CChildView::Bezier2() //координаты для безье
{

	//Квадратичная с п1=п2
	CMatrix X(3);//в точке х
	CMatrix Y(3);
	X(0) = 0;
	Y(0) = 0;
	X(1) = 5; //для равномерной кривой
	Y(1) = 5;
	X(2) = 10; //	X(2) = 0; //для прямой безье
	Y(2) = 0;

	PenLine.Set(PS_SOLID, 1, RGB(255, 0, 0));//цвет графика

											 //задаем параметры
	Graph.SetParams(X, Y, RW);
	Graph.SetPenLine(PenLine);
	Graph.SetPenAxis(PenAxis);
}

void CChildView::Bezier3() //координаты для безье
{
	//на подобии синусоиды

	CMatrix X(4);//в точке х
	CMatrix Y(4);
	X(0) = 0;
	Y(0) = 0;
	X(1) = 5;
	Y(1) = 10;
	X(2) = 10;
	Y(2) = -10;
	X(3) = 15;
	Y(3) = 0;

	PenLine.Set(PS_SOLID, 1, RGB(255, 0, 0));//цвет графика

											 //задаем параметры
	Graph.SetParams(X, Y, RW);
	Graph.SetPenLine(PenLine);
	Graph.SetPenAxis(PenAxis);
}

void CChildView::Bezier4() //координаты для безье
{
	//Закорючка

	CMatrix X(4);//в точке х
	CMatrix Y(4);
	X(0) = 0;
	Y(0) = 0;
	X(1) = 20;
	Y(1) = 10;
	X(2) = -5;
	Y(2) = 10;
	X(3) = 15;
	Y(3) = 0;

	PenLine.Set(PS_SOLID, 1, RGB(255, 0, 0));//цвет графика
											 //задаем параметры
	Graph.SetParams(X, Y, RW);
	Graph.SetPenLine(PenLine);
	Graph.SetPenAxis(PenAxis);
}
