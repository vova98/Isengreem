// stdafx.h: ���������� ���� ��� ����������� ��������� ���������� ������
// ��� ���������� ������ ��� ����������� �������, ������� ����� ������������, ��
// �� ����� ����������
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>


#include <cerrno>
struct StudAndMark
{
	char surname[29];
	int mark;
	int surnlength;
};

StudAndMark* InputData(int count);
