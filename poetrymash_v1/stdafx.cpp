// stdafx.cpp: исходный файл, содержащий только стандартные включаемые модули
// PoetryMash.pch будет предкомпилированным заголовком
// stdafx.obj будет содержать предварительно откомпилированные сведения о типе

#include "stdafx.h"

char** InitText(int* count, int key)
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

		buffer[len] = '\r';
		buffer[len+1] = '\r';

		*count = 0;

		for (int i = 0; i <= (int)len; i++)
		if (buffer[i] == '\r')
		{
			*count += 1;
		}
			
		char** text = new char*[*count];
		
		int n = 1, nOld = 1, countSpace = 0;

		text[0] = buffer;

		int i = 1;
		while (i< *count - countSpace)
		{
			while (buffer[n] != '\r')
				n++;
				assert(0 <= i && i < *count);
				text[i] = buffer + (n + 2)*sizeof(char);
				i++;
				n++;
		}

		if (key == 1)
		{
			int jump = *count;
			bool swapped = true;
			while (jump > 1 || swapped)
			{
				if (jump > 1)
					jump /= 1.24733;
				swapped = false;
				for (int i = 0; i + jump < *count - countSpace; ++i)
				if (mlStrcmp(text[i + jump], text[i]) == -1)
				{
					swapPtr(&text[i], &text[i + jump]);
					swapped = true;
				}
			}
		}
		else if (key == 2)
		{

				int jump = *count;
				bool swapped = true;
				while (jump > 1 || swapped)
				{
					if (jump > 1)
						jump /= 1.24733;
					swapped = false;
					for (int i = 0; i + jump < *count-countSpace; ++i)
					if (mlStrcmpEnd(text[i + jump], text[i]) == -1)
					{
						swapPtr(&text[i], &text[i + jump]);
						swapped = true;
					}
				}
		}

		n += 3;
		*count = *count - countSpace;
		return text;
	}
}

int mlStrcmp(char* string1, char* string2)
{
	int i = 0, j = 0;
	
	while (string1[i] != '\r' && string2[j] != '\r')
	{
		if ((int)string1[i] > 32 && (int)string1[i] < 48 || (int)string1[i] > 57 && (int)string1[i] < 64 || (int)string1[i] < 32 && (int)string1[i] > 0)
			i++;
		if ((int)string2[j] > 32 && (int)string2[j] < 48 || (int)string2[j] > 57 && (int)string2[j] < 64 || (int)string2[j] < 32 && (int)string2[j] > 0)
			j++;
		else
		{
			assert(string1[i] && string2[j]);
			if (string1[i] == string2[j])
			{
				i++;
				j++;
			}
			else if (string1[i] > string2[j])
				return 1;
			else if (string1[i] < string2[j])
				return -1;
			return 0;
		}
	}
}

int mlStrcmpEnd(char* string1, char* string2)
{
	int i = 0, len1 = 0, len2 = 0;
  	while (string1[i] != '\r')
	{
		len1++;
		i++;
	}
	int j = 0;
	while (string2[j] != '\r')
	{
		len2++;
		j++;
	}

	i = 1;
	j = 1;

	while (len1 - i - 1 > 0 && len2 - j - 1> 0)
	{
		if ((int)string1[len1 - i] > 32 && (int)string1[len1 - i] < 48 || (int)string1[len1 - i] > 57 && (int)string1[len1 - i] < 64)
			i++;
		if ((int)string2[len2 - j] > 32 && (int)string2[len2 - j] < 48 || (int)string2[len2 -j] > 57 && (int)string2[len2 - j] < 64)
			j++;
		else
		{
			if (string1[len1 - i] == string2[len2 - j])
			{
				i++;
				j++;
			}
			else if (string1[len1 - i] > string2[len2 - j])
				return 1;
			else if (string1[len1 - i] < string2[len2 - j])
				return -1;
			else return 0;
		}
	}
}

int min(int a, int b)
{
	if (a>b) return b;
	else return a;
}

void swapPtr(char** first, char** second)
{
	char* tmp = *first;
	*first = *second;
	*second = tmp;
}

