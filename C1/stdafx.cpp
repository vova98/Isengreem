// stdafx.cpp: �������� ����, ���������� ������ ����������� ���������� ������
// C1.pch ����� ������������������� ����������
// stdafx.obj ����� ��������� �������������� ����������������� �������� � ����

#include "stdafx.h"

bool isWeigh(int num)
{
	while (num > 1)
	{
		if (num % 4 != 2)
		if (num % 4 != 3)
			num = num / 4;
		else num = num / 4 + 1;
		else return true; 
	}
	return false;
}
