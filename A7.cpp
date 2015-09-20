// A7.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	FILE* fileout;
	errno_t err = fopen_s(&fileout, "output.txt", "w");
	int arrayNumb[31], number = 0, count = 0;

	scanf_s("%d", &number);
	//int *arrayGrad = makegrad2(fileout);
	//for (int i = 0; i < 31; i++)
	//	printf("%d, ", arrayGrad[i]);

	for (int i = 30; i >= 0; i--)
	if (Grad2[i] <= number)
	{
		arrayNumb[count] = Grad2[i];
		number -= Grad2[i];
		count++;
	}
	
	for (int i = count-1; i >= 0; i--)
		printf("%d ", arrayNumb[i]);
	printf("\n");


	return 0;
}

