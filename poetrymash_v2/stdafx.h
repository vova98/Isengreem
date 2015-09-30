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


void printStr(FILE* fout, char* string);
char** InitText(int* count, size_t* len);
int sortText(char** text, int key, int *count, size_t len);
int mlStrcmp(char* string1, char* string2);
int mlStrcmpEnd(char* string1, char* string2);
void swapPtr(char** first, char** second);
int freeMemory(char** text);
bool Normal(char* string, int numb);
int printText(char** text, int count, int key);
void findEnd(char** text, int* count, size_t len);
int min(int a, int b);
const int Ok = 1;
const int Bad = -1;
char trash1 = 'Ђ';
char trash2 = 'Ч';
