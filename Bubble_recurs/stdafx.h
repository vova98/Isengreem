// stdafx.h: ���������� ���� ��� ����������� ��������� ���������� ������
// ��� ���������� ������ ��� ����������� �������, ������� ����� ������������, ��
// �� ����� ����������
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



#include <ctime>
#include <iostream>
int const CountELem = 10;
int const allOk = 1;
int InitArray(int* sortArray);
int BubbleSort(int *sortArray, int curElem, int* LastElem);
void Swap(int* First, int* Second);