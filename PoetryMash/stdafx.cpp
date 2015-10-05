
#include "stdafx.h"

char** InitText(int* StringCount, size_t *Textlen)
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
		*Textlen = ftell(filein);
		rewind(filein);
		char *buffer = (char*)calloc(*Textlen, sizeof(*buffer));
		assert(buffer);
		fread((char*)buffer, *Textlen, sizeof(*buffer), filein);
		fclose(filein);

		buffer[*Textlen] = '\0';

		*StringCount = 0;

		for (int i = 0; i <= (int)*Textlen; i++)
		if (buffer[i] == '\r')
			*StringCount += 1;

		char** text = new char*[*StringCount];
		assert(text);

		int n = 1, nOld = 1, i = 1;

		text[0] = buffer;
		while (i < *StringCount)
		{
			while (buffer[n] != '\r')
				n++;
			assert(0 <= i && i < *StringCount);
			text[i] = buffer + (n + 2)*sizeof(buffer[0]);
			i++;
			n++;
		}
		return text;
	}
}

int sortText(char** text, int key, int *StringCount, size_t Textlen)
{
	assert(text);
	if (key == 1)
	{
		int jump = *StringCount;
		bool swapped = true;
		while (jump > 1 || swapped)
		{
			if (jump > 1)
				jump /= 1.24733;
			swapped = false;
			for (int i = 0; i + jump < *StringCount; ++i)
			{
				assert(&text[i] && &text[i + jump]);
				if (mlStrcmp(text[i + jump], text[i]) == -1)
				{
					swapPtr(&text[i], &text[i + jump]);
					swapped = true;
				}
			}
		}
	}
	else if (key == 2)
	{
		int jump = *StringCount;
		bool swapped = true;
		while (jump > 1 || swapped)
		{
			if (jump > 1)
				jump /= 1.24733;
			swapped = false;
			for (int i = 0; i + jump < *StringCount; ++i)
			if (mlStrcmpEnd(text[i + jump], text[i]) == -1)
			{
				assert(&text[i] && &text[i + jump]);
				swapPtr(&text[i], &text[i + jump]);
				swapped = true;
			}
		}
	}
	findEnd(text, StringCount, Textlen, key);
	return Ok;
}

void findEnd(char** text, int* StringCount, size_t Textlen, int key)
{
	if (key == 1)
	{
		for (int i = 0; i < *StringCount; i++)
		{
			assert(text[i][0]);
			if (text[i][0] >= '1' && text[i][0] <= '9')
				*StringCount = i;
		}
	}
	else
	{
		for (int i = 1; i < *StringCount; i++)
		{
			assert(*(char*)text[i] - 3);

			if (*(char*)text[i] - 3 >= '1' && *(char*)text[i] - 3 <= '9')
				*StringCount = i;
		}
	}
}

int printText(char** text, int StringCount, int key)
{
	FILE* fout;
	errno_t err = fopen_s(&fout, "output.txt", "w");
	int numStr = 0, k = 0;

	int a = 0, b = 0; /*! Using for rhyme*/

	if (key == 2)
	{
		for (int i = 0; i < ParagrafCount; i++)
		{
			srand(time(0));
			a = rand() % (StringCount - 1);
			printStr(fout, text[a]);
			b = rand() % (StringCount - 1);
			printStr(fout, text[b]);
			a += rand() % (5) + 1;
			printStr(fout, text[a]);
			b += rand() % (5) + 1;
			printStr(fout, text[b]);

			a = rand() % (StringCount - 1);
			printStr(fout, text[a]);
			a += rand() % (5) + 1;
			printStr(fout, text[a]);
			b = rand() % (StringCount - 1);
			printStr(fout, text[b]);
			b += rand() % (5) + 1;
			printStr(fout, text[b]);

			a = rand() % (StringCount - 1);
			printStr(fout, text[a]);
			b = rand() % (StringCount - 1);
			printStr(fout, text[b]);
			b += rand() % (5) + 1;
			printStr(fout, text[b]);
			a += rand() % (5) + 1;
			printStr(fout, text[a]);

			a = rand() % (StringCount - 1);
			printStr(fout, text[a]);
			a += rand() % (5) + 1;
			printStr(fout, text[a]);

			fprintf(fout, "\n");
		}
	}
	else
	while (numStr < StringCount)
	{
		printStr(fout, text[numStr]);
		numStr++;
	}

	fclose(fout);
	return Ok;
}

void printStr(FILE* fout, char* string)
{
	int k = 0;
	bool is_text = false;
	
	for (int i = 0; string[i] != '\r'; i++)
	if (!IsPunct(string, i)) 
		is_text = true;

	if (is_text)
	while (string[k] != '\0')
	{

		assert(string[k]);
		if (string[k] != '\r')
		{
			fprintf(fout, "%c", string[k]);
			k += 1;
		}
		else if (string[k]>0 && string[k] < 255)
		{
			fprintf(fout, "\n");
			break;
		}
		else
		{
			printf("What the Fuck!?");
		}
	}
}


int freeMemory(char** text)
{
	assert(text);
	delete[]text;
	return Ok;
}

int mlStrcmp(char* string1, char* string2)
{
	int i = 0, j = 0;

	assert(string1 && string2);

	while (string1[i] != '\r' && string2[j] != '\r')
	{
		while (IsPunct(string1, i))
			i++;
		while (IsPunct(string2, j))
			j++;
		if (!IsPunct(string1, i) && !IsPunct(string2, j))
		{
			assert(string1[i] && string2[j]);
			if (string1[i] == string2[j])
			{
				i++;
				j++;
			}
			else return (string1[i] > string2[j]) ? 1 : (string1[i] < string2[j]) ? -1 : 0;
		}
	} 
}

int IsPunct(char* string, int numb)
{
	assert(string[numb]);
	return (unsigned int)string[numb] > 0 && (unsigned int)string[numb] < 48 || (unsigned int)string[numb] > 57 && (unsigned int)string[numb] < 64 ||
		(unsigned int)string[numb] == '«' || (unsigned int)string[numb] == '»' || (unsigned int)string[numb] == '—' ? 1 : 0;
}

int mlStrcmpEnd(char* string1, char* string2)
{
	int i = 0, lengthStr1 = 0, lengthStr2 = 0;

	assert(string1 && string2);

	while (string1[i] != '\r')
		i++;

	int j = 0;
	while (string2[j] != '\r' )
		j++;

	lengthStr1 = i;
	lengthStr2 = j;
	
	i = 1;
	j = 1;

	if (string2[lengthStr2 - 1] >= 'A' && string2[lengthStr2 - 1] <= 'Z' && string1[lengthStr1 - 1] >= 'A' && string1[lengthStr1 - 1] <= 'Z')
		return 0;
	else while (lengthStr1 - i >= 0 && lengthStr2 - j >= 0)
	{
		while (IsPunct(string1, lengthStr1 - i))
			i++;
		while (IsPunct(string2, lengthStr2 - j))
			j++;
		if (!IsPunct(string1, lengthStr1 - i) && !IsPunct(string2, lengthStr2 - j))
		{
			if (string1[lengthStr1 - i] == string2[lengthStr2 - j])
			{
				i++;
				j++;
			}
			return string1[lengthStr1 - i] > string2[lengthStr2 - j] ? 1 : string1[lengthStr1 - i] < string2[lengthStr2 - j] ? -1 : 0;
		}
	}
	return 0;
}

void swapPtr(char** first, char** second)
{
	assert(first && second && *first && *second);
	char* tmp = *first;
	*first = *second;
	*second = tmp;
}
