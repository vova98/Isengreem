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
int const MAX_INT = 2147000000;
int const allOk = 1;
int InitArray(int* sortArray);
int SelectSort(int* sortArray, int curFirst);
void Swap(int* First, int* Second);