// stdafx.h: включаемый файл дл€ стандартных системных включаемых файлов
// или включаемых файлов дл€ конкретного проекта, которые часто используютс€, но
// не часто измен€ютс€
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