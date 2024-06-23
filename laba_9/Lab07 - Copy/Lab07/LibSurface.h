using namespace std;

typedef vector<CMatrix> CVecMatrix;
typedef vector<CVecMatrix> CMasMatrix;
typedef vector<CPoint> CVecPoint;
typedef vector<CVecPoint> CMatrPoint;
typedef double(*pfunc2)(double, double);// Указатель на функцию

class CPlot3D
{
private:
	pfunc2 pFunc;          // Указатель на функцию f(x,y), описывающая поверхность 
	CRectD SpaceRect;      // Прямоугольник области, на которую опирается поверхность
	CMasMatrix MatrF;      // Матрица для хранения координат точек (x,y,z,1) поверхности
	CMasMatrix MatrView;   // Матрица для хранения координат точек (x,y,1) проекции XY видовой СК
	CRectD ViewRect;       // Прямоугольная область, охватывающая проекцию поверхности видовой СК
	CRect WinRect;         // Прямоугольная область в оконной системе координат для
	CMatrix ViewPoint;     // Вектор (3x1) – координаты точки наблюдения в мировой сферической СК (r,fi,q)
	CMatrPoint MatrWindow; // Матрица для хранения оконных координат

public:

};

void DrawLightSphere(CDC& dc, double Radius, CMatrix& PView, CMatrix& PSourceLight, CRect RW, COLORREF Color, int Index)
// Index=0 –  Диффузионная модель отражения света
// Index=1 –  Зеркальная модель отражения света
{
	BYTE red = GetRValue(Color);
	BYTE green = GetGValue(Color);
	BYTE blue = GetBValue(Color);

	CMatrix VSphere(3), VSphereNorm(3), V0(3), PV(4);
	COLORREF Col;
	double df = 0.54;                              // Шаг по азимуту
	double dq = 0.54;                              // Шаг угла	
	double kLight;
	VSphere(0) = 3;
	CMatrix VR = SphereToCart(PView);				//т.наблюд в декарт
	CMatrix VS = SphereToCart(PSourceLight);		//т.света в декарт
	CRectD  RV(-Radius, Radius, Radius, -Radius); // Обл проекции шара на XY в ВСК
	CMatrix MW = SpaceToWindow(RV, RW);		      // М-ца МСК -> ОСК
	CMatrix MV = CreateViewCoord(PView(0), PView(1), PView(2));	//М-ца -> ВСК

	V0(0) = RV.left;	// в ОСК, xL 
	V0(1) = RV.bottom;	// в ОСК, yL
	///V0(2)=0 - в конструкторе	


	// Проходим по точкам сферы
	for (double fi = 0; fi < 360.0; fi += df)		  // Азимут
		for (double q = 0; q <= 180.0; q += dq)		  // q = 90 - угол места
		{
			VSphere(1) = fi;
			VSphere(2) = q;
			CMatrix VCart = SphereToCart(VSphere);	  // т.сферы в декарт                                     
			VSphereNorm = VCart;				      // В-р нормали
			double cos_RN = CosV1V2(VR, VSphereNorm); // cos (в-р т.наблюд. ; в-р N)

			if (cos_RN > 0) // Если точка видима наблюдателю
			{
				///дек -вск - оск
				PV(0) = VCart(0);
				PV(1) = VCart(1);
				PV(2) = VCart(2);
				PV(3) = 1;
				PV = MV * PV;         // точка сферы -> ВСК
				VCart(0) = PV(0);   // Xv
				VCart(1) = PV(1);   // Yv
				VCart(2) = 1;
				VCart = VCart - V0; // Xv-xL, Yv-yL, 1
				VCart = MW * VCart;   // точка сферы -> ОСК

				CMatrix VP = VS - VR;       // Напр на источник света отн нормали к т.падения
				double cos_PN = CosV1V2(VP, VSphereNorm); // cos угла падения луча


				if (cos_PN > 0) // Если точка сферы освещается
				{
					if (Index == 0)				///диффуз
						kLight = cos_PN;   
					else		///зеркал
						kLight = CosV1V2(VSphereNorm, VS);

					Col = RGB(kLight * red, kLight * green, kLight * blue);
					dc.SetPixel((int)VCart(0), (int)VCart(1), Col);
				}
				else
				{
					Col = RGB(0, 0, 0);
					dc.SetPixel((int)VCart(0), (int)VCart(1), Col);
				}
			}
		}
}