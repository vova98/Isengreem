// stdafx.cpp: �������� ����, ���������� ������ ����������� ���������� ������
// A3.pch ����� ������������������� ����������
// stdafx.obj ����� ��������� �������������� ����������������� �������� � ����

#include "stdafx.h"

int NOD(int a, int b)
{
	//int x = 0;
	if (a != 0)
		return NOD(b%a,a);
	else return b;

	return b;
}
