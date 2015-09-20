// stdafx.cpp: исходный файл, содержащий только стандартные включаемые модули
// B4.pch будет предкомпилированным заголовком
// stdafx.obj будет содержать предварительно откомпилированные сведения о типе

#include "stdafx.h"
int fileFilter(FILE* filein)
{
	char letter = '0', prevletter = '0';
	int lettercode = 0;
	do
	{
		letter = getc(filein);
		lettercode = (int)(letter);
		if (lettercode > 64 && lettercode < 91)
		{
			lettercode += 32;
			printf("%c", (char)(lettercode));
			prevletter = letter;
		}
		else if (lettercode > 47 && lettercode < 58)
		{
			lettercode = 35;
			printf("%c", (char)(lettercode));
			prevletter = letter;
		}
		else if (lettercode == 32)
		{
			if (prevletter != ' ')
			{
				printf("%c", letter);
				prevletter = letter;
			}
		}
		else if (lettercode > 96 && lettercode < 123)
		{
			printf("%c", (char)(lettercode));
			prevletter = letter;
		}
		else if (lettercode == 10)
			printf("\n");

	} while (letter != EOF);
	printf("\n");
	fclose(filein);
	return 1;
	}

