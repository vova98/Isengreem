// stdafx.cpp: �������� ����, ���������� ������ ����������� ���������� ������
// C5.pch ����� ������������������� ����������
// stdafx.obj ����� ��������� �������������� ����������������� �������� � ����

#include "stdafx.h"

StudAndMark* InputData(int count)
{
	int j = 0;
	char letter = '0';
	StudAndMark* arrayStud = new StudAndMark[count];
	//if (!arrayStud) { errno = enomem; return NULL; }
	for (int i = 0; i < count; i++)
	{
		while (letter != ' ')
		{
			scanf_s("%c", &letter);
			arrayStud[i].surname[j] = letter;
			j++;
		}
		arrayStud[i].surnlength = j;
		j = 0;
		scanf_s("%d", &arrayStud[i].mark);
	}
	return arrayStud;
}
