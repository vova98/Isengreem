// stdafx.cpp: �������� ����, ���������� ������ ����������� ���������� ������
// A2.pch ����� ������������������� ����������
// stdafx.obj ����� ��������� �������������� ����������������� �������� � ����

#include "stdafx.h"

int** InputDynamicAndTranspon(int num)
{
	int  **arr = new int*[num];
	for (int i = 0; i < num; i++)
		arr[i] = new int[num];

	for (int i = 0; i < num; i++)
	for (int j = 0; j < num; j++)
		cin >> arr[j][i];
		//scanf_s("%d", &arr[j][i]);
	return arr;
}
