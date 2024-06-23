using namespace std;

typedef vector<CMatrix> CVecMatrix;
typedef vector<CVecMatrix> CMasMatrix;
typedef vector<CPoint> CVecPoint;
typedef vector<CVecPoint> CMatrPoint;
typedef double(*pfunc2)(double, double);// ��������� �� �������

class CPlot3D
{
private:
	pfunc2 pFunc;          // ��������� �� ������� f(x,y), ����������� ����������� 
	CRectD SpaceRect;      // ������������� �������, �� ������� ��������� �����������
	CMasMatrix MatrF;      // ������� ��� �������� ��������� ����� (x,y,z,1) �����������
	CMasMatrix MatrView;   // ������� ��� �������� ��������� ����� (x,y,1) �������� XY ������� ��
	CRectD ViewRect;       // ������������� �������, ������������ �������� ����������� ������� ��
	CRect WinRect;         // ������������� ������� � ������� ������� ��������� ���
	CMatrix ViewPoint;     // ������ (3x1) � ���������� ����� ���������� � ������� ����������� �� (r,fi,q)
	CMatrPoint MatrWindow; // ������� ��� �������� ������� ���������

public:

};

void DrawLightSphere(CDC& dc, double Radius, CMatrix& PView, CMatrix& PSourceLight, CRect RW, COLORREF Color, int Index)
// Index=0 �  ������������ ������ ��������� �����
// Index=1 �  ���������� ������ ��������� �����
{
	BYTE red = GetRValue(Color);
	BYTE green = GetGValue(Color);
	BYTE blue = GetBValue(Color);

	CMatrix VSphere(3), VSphereNorm(3), V0(3), PV(4);
	COLORREF Col;
	double df = 0.54;                              // ��� �� �������
	double dq = 0.54;                              // ��� ����	
	double kLight;
	VSphere(0) = 3;
	CMatrix VR = SphereToCart(PView);				//�.������ � ������
	CMatrix VS = SphereToCart(PSourceLight);		//�.����� � ������
	CRectD  RV(-Radius, Radius, Radius, -Radius); // ��� �������� ���� �� XY � ���
	CMatrix MW = SpaceToWindow(RV, RW);		      // �-�� ��� -> ���
	CMatrix MV = CreateViewCoord(PView(0), PView(1), PView(2));	//�-�� -> ���

	V0(0) = RV.left;	// � ���, xL 
	V0(1) = RV.bottom;	// � ���, yL
	///V0(2)=0 - � ������������	


	// �������� �� ������ �����
	for (double fi = 0; fi < 360.0; fi += df)		  // ������
		for (double q = 0; q <= 180.0; q += dq)		  // q = 90 - ���� �����
		{
			VSphere(1) = fi;
			VSphere(2) = q;
			CMatrix VCart = SphereToCart(VSphere);	  // �.����� � ������                                     
			VSphereNorm = VCart;				      // �-� �������
			double cos_RN = CosV1V2(VR, VSphereNorm); // cos (�-� �.������. ; �-� N)

			if (cos_RN > 0) // ���� ����� ������ �����������
			{
				///��� -��� - ���
				PV(0) = VCart(0);
				PV(1) = VCart(1);
				PV(2) = VCart(2);
				PV(3) = 1;
				PV = MV * PV;         // ����� ����� -> ���
				VCart(0) = PV(0);   // Xv
				VCart(1) = PV(1);   // Yv
				VCart(2) = 1;
				VCart = VCart - V0; // Xv-xL, Yv-yL, 1
				VCart = MW * VCart;   // ����� ����� -> ���

				CMatrix VP = VS - VR;       // ���� �� �������� ����� ��� ������� � �.�������
				double cos_PN = CosV1V2(VP, VSphereNorm); // cos ���� ������� ����


				if (cos_PN > 0) // ���� ����� ����� ����������
				{
					if (Index == 0)				///������
						kLight = cos_PN;   
					else		///������
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