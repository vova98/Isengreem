// stdafx.cpp: �������� ����, ���������� ������ ����������� ���������� ������
// �3.pch ����� ������������������� ����������
// stdafx.obj ����� ��������� �������������� ����������������� �������� � ����

#include "stdafx.h"

int lagrange(int mas[],int num)
{
	for (int i = ceil(sqrt(num)); i > 0; i--)
	{
		int sqrI = i*i;
		if (count<4)
		{
			if (num > sqrI)
			{
				mas[count] = sqrI;
				//printf("%d ", sqrI);
				count++;
				lagrange(mas,num - sqrI);
				return 1;
			}
			else if (num == sqrI)
			{
				mas[count] = sqrI;
				//printf("%d ", sqrI);
				count = 5;

			}
		}
	}
}
