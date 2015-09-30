// stdafx.cpp: èñõîäíûé ôàéë, ñîäåðæàùèé òîëüêî ñòàíäàðòíûå âêëþ÷àåìûå ìîäóëè
// PoetryMash.pch áóäåò ïðåäêîìïèëèðîâàííûì çàãîëîâêîì
// stdafx.obj áóäåò ñîäåðæàòü ïðåäâàðèòåëüíî îòêîìïèëèðîâàííûå ñâåäåíèÿ î òèïå

#include "stdafx.h"

char** InitText(int* count, size_t *len)
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
		*len = ftell(filein);
		rewind(filein);
		char *buffer = (char*)calloc(*len, sizeof(*buffer));
		assert(buffer);
		fread((char*)buffer, *len, sizeof(*buffer), filein);
		fclose(filein);

		buffer[*len] = '\r';
		buffer[*len + 1] = '\r';

		*count = 0;

		for (int i = 0; i <= (int)*len; i++)
		if (buffer[i] == '\r')
			*count += 1;

		char** text = new char*[*count];
		assert(text);

		int n = 1, nOld = 1;

		text[0] = buffer;

		int i = 1;
		while (i < *count)
		{
			while (buffer[n] != '\r')
				n++;
			assert(0 <= i && i < *count);
			text[i] = buffer + (n + 2)*sizeof(char);
			i++;
			n++;
		}
		return text;
	}
}

int sortText(char** text, int key, int *count, size_t len)
{
	if (key == 1)
	{
		int jump = *count;
		bool swapped = true;
		while (jump > 1 || swapped)
		{
			if (jump > 1)
				jump /= 1.24733;
			swapped = false;
			for (int i = 0; i + jump < *count - 1; ++i)
			if (mlStrcmp(text[i + jump], text[i]) == -1)
			{
				assert(&text[i] && &text[i + jump]);
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
			for (int i = 0; i + jump < *count - 1; ++i)
			if (mlStrcmpEnd(text[i + jump], text[i]) == -1)
			{
				assert(&text[i] && &text[i + jump]);
				swapPtr(&text[i], &text[i + jump]);
				swapped = true;
			}
		}
	}
	findEnd(text, count, len);
	return Ok;
}

void findEnd(char** text, int* count, size_t len)
{
	for (int i = 0; i < *count; i++)
	if (text[i][0] == '.')
		*count = i;
}

int printText(char** text, int count, int key)
{
	FILE* fout;
	errno_t err = fopen_s(&fout, "output.txt", "w");
	int num = 0, k = 0;

	int a = 0, b = 0;

	if (key == 2)
	{
		srand(time(0));
		a = rand() % (count - 1);
		printStr(fout, text[a]);
		b = rand() % (count - 1);
		printStr(fout, text[b]);
		a += rand() % (5) + 1;
		printStr(fout, text[a]);
		b += rand() % (5) + 1;
		printStr(fout, text[b]);

		a = rand() % (count - 1);
		printStr(fout, text[a]);
		a -= rand() % (5) + 1;
		printStr(fout, text[a]);
		b = rand() % (count - 1);
		printStr(fout, text[b]);
		b += rand() % (5) + 1;
		printStr(fout, text[b]);

		a = rand() % (count - 1);
		printStr(fout, text[a]);
		b = rand() % (count - 1);
		printStr(fout, text[b]);
		b -= rand() % (5) + 1;
		printStr(fout, text[b]);
		a += rand() % (5) + 1;
		printStr(fout, text[a]);

		a = rand() % (count - 1);
		printStr(fout, text[a]);
		a -= rand() % (5) + 1;

		fprintf(fout, "\n");
	}
	else while (num < count)
	{
		printStr(fout, text[num]);
		num++;
	}

	fclose(fout);
	return Ok;
}

void printStr(FILE* fout, char* string)
{
	int k = 0;
	while (true)
	{
		if (string[k] != '\r')
		{
			assert((int)(string[k])<255);
			fprintf(fout, "%c", string[k]);
			k += 1;
		}
		else if ((int)(string[k])>0 && (int)(string[k]) < 255)
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

	while (string1[i] != '\r' && string2[j] != '\r')
	{
		if (!Normal(string1, i))
			i++;
		if (!Normal(string2, j))
			j++;
		if (Normal(string1, i) && Normal(string2, j))
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

bool Normal(char* string, int numb)
{
	if ((int)string[numb] > 32 && (int)string[numb] < 48 && (int)string[numb] > 57 && (int)string[numb] < 64 && (int)string[numb] < 32 && (int)string[numb] > 0 && (int)string[numb] == trash1 && (int)string[numb] == trash2)

		return true;
}

int mlStrcmpEnd(char* string1, char* string2)
{
	int i = 0, len1 = 0, len2 = 0;
	while (string1[i] != '\r' && string1[i] != 'ý')
	{
		i++;
	}
	int j = 0;
	while (string2[j] != '\r' && string1[i] != 'ý')
	{
		j++;
	}

	len1 = i;
	len2 = j;
	
	i = 1;
	j = 1;

	if (string2[len2 - 1] >= 'A' && string2[len2 - 1] <= 'Z' && string1[len1 - 1] >= 'A' && string1[len1 - 1] <= 'Z')
		return 0;
	else while (len1 - i >= 0 && len2 - j >= 0)
	{
		if (!Normal(string1, i))
			i++;
		if (!Normal(string2, j))
			j++;
		if (Normal(string1, i) && Normal(string2, j))
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
	return 0;
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
