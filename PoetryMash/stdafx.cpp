// stdafx.cpp: исходный файл, содержащий только стандартные включаемые модули
// PoetryMash.pch будет предкомпилированным заголовком
// stdafx.obj будет содержать предварительно откомпилированные сведения о типе

#include "stdafx.h"

void InitText()
{
	setlocale(LC_ALL, "rus");
	FILE *filein;
	errno_t err = fopen_s(&filein, "input.txt", "rb");
	if (filein == NULL) 
	{
		printf("You haven`t text!");	
	}
	else
	{
		fseek(filein, 0, SEEK_END);
		size_t len = ftell(filein);
		rewind(filein);
	    char *buffer = (char*)calloc(len, sizeof(*buffer));
		fread((char*)buffer, len, sizeof(*buffer), filein);
		fclose(filein);

		int count = 0;

		for (int i = 0; i <= len; i++)
		if (buffer[i] == '\r') 
			count++;

		char** text = (char**)calloc(count, sizeof(*buffer));
		
		int n = 1;

		text[0] = buffer;

		for (int i = 1; i <= count; i++)
		{
			while (buffer[n] != '\r') n++;

			text[i] = buffer+(n+2)*sizeof(char);
			n++;
		}

		int direct = 0;
		printf("%s\n%s\n", text[0], text[1]);
		direct = mlStrcmp(text[0], text[1]);

		if (direct < 0) 
			swapPtr(&text[0], &text[1]);

		printf("%s\n%s\n", text[0], text[1]);
	}
}

int mlStrcmp(char* string1, char* string2)
{
	int i = 0;
	while (string1[i] != '\r' && string2[i] != '\r')
	if (string1[i] == string2[i]) i++;
	else if (string1[i] > string2[i])
		return 1;
	else if (string1[i] < string2[i])
		return -1;
	return 0;
	
}

void swapPtr(char** first, char** second)
{
	char* tmp = *first;
	*first = *second;
	*second = tmp;
}

