// stdafx.h: включаемый файл дл€ стандартных системных включаемых файлов
// или включаемых файлов дл€ конкретного проекта, которые часто используютс€, но
// не часто измен€ютс€
//

#pragma once
#define UNDEBUG

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



#include <cstdlib>
#include <errno.h>
#include <iostream>
#include <locale>
#include <cassert>
//#include <alloc.h>
char** InitText(int* count, int key);
int mlStrcmp(char* string1, char* string2);
int mlStrcmpEnd(char* string1, char* string2);
void swapPtr(char** first, char** second);
int sortTextHead(char*** text, int*count);
int min(int a, int b);
const int Ok = 1;
//const char FileName[] = "input.txt";