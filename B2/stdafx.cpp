// stdafx.cpp: �������� ����, ���������� ������ ����������� ���������� ������
// B2.pch ����� ������������������� ����������
// stdafx.obj ����� ��������� �������������� ����������������� �������� � ����

#include "stdafx.h"

int normalroot(int num, int* A, int* B)
{
	for (int i = 1; i <= ceil(sqrt(num)); i++)
	{
		int sqrI = i*i;
		if (num%sqrI == 0)
			*B = i;
	}
	*A = num / (*B*(*B));
	return Happy;
}
