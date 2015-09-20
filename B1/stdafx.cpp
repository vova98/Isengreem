// stdafx.cpp: �������� ����, ���������� ������ ����������� ���������� ������
// B1.pch ����� ������������������� ����������
// stdafx.obj ����� ��������� �������������� ����������������� �������� � ����

#include "stdafx.h"

bool isSimple(int num)
{
	double divdouble = 0;
	int divint = 0, sqnum = 0;

	sqnum = ceil(sqrt(num));
	for (int i = 2; i <= sqnum; i++)
	{
		divdouble = (double)num / (i*i);
		divint = floor(divdouble);

		if (fabs(divint - divdouble) < 0.000001)
			return true;
	}
	return false;
}
