// stdafx.cpp: исходный файл, содержащий только стандартные включаемые модули
// C4.pch будет предкомпилированным заголовком
// stdafx.obj будет содержать предварительно откомпилированные сведения о типе

#include "stdafx.h"


int convers(FILE* filein)
{
	char letter = '0', array[1000] = {};//, convArr[1000] = {};
	int count = 0;
	do
	{
		do
		{
			letter = getc(filein);
			array[count] = letter;
			count++;
		} while (letter != ' ' && (int)(letter) != 10 && letter != EOF);

		for (int i = count - 2; i >= 0; i--)
		{
			printf("%c", array[i]);
			//convArr[count - i] = array[i];
			array[i] = 0;
		}
		printf("%c", array[count - 1]);
		//convArr[count] = array[count];
		count = 0;

	} while (letter != EOF);
	printf("\n");
	return 1;
}
