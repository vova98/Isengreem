// stdafx.cpp: �������� ����, ���������� ������ ����������� ���������� ������
// B5.pch ����� ������������������� ����������
// stdafx.obj ����� ��������� �������������� ����������������� �������� � ����

#include "stdafx.h"

long long summaDiv(int numb)
{
	int summa = 0;
	for (int i = 1; i <= (numb + 1) / 2; i++)
	if (numb%i == 0)
		summa += i;

	summa += numb;
	return summa;
}