// stdafx.h: ���������� ���� ��� ����������� ��������� ���������� ������
// ��� ���������� ������ ��� ����������� �������, ������� ����� ������������, ��
// �� ����� ����������
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



#include <cstdlib>
#include <errno.h>
#include <iostream>
void InitText();
int mlStrcmp(char* string1, char* string2);
void swapPtr(char** first, char** second);
//const char FileName[] = "input.txt";