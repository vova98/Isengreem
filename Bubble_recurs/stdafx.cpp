// stdafx.cpp: исходный файл, содержащий только стандартные включаемые модули
// Bubble_recurs.pch будет предкомпилированным заголовком
// stdafx.obj будет содержать предварительно откомпилированные сведения о типе

#include "stdafx.h"

int InitArray(int* sortArray)
{
	srand(time(0));
	for (int i = 0; i < CountELem; i++)
		sortArray[i] = rand() % 10 + 1;

	for (int i = 0; i < CountELem; i++)
		printf("%d ", sortArray[i]);
	printf("\n");

	return allOk;
}

int BubbleSort(int *sortArray, int curElem, int* LastElem)
{

	if (sortArray[curElem] > sortArray[curElem + 1])
		Swap(&sortArray[curElem], &sortArray[curElem + 1]);

	if (*LastElem == 0) 
		return *sortArray;

	if (curElem<(*LastElem)-2)
	BubbleSort(sortArray, curElem+1,LastElem);
	else
	{
		(*LastElem)--;
		curElem = 0;
		BubbleSort(sortArray, curElem, LastElem);
	}
}

void Swap(int* First, int* Second)
{
	int Tmp = 0;
	Tmp = *First;
	*First = *Second;
	*Second = Tmp;
}
