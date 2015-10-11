#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <iostream>
#include <ctime>

/**
*@mainpage
*\brief Poetry Mash program
*\author Kachanov Vova
*\version 1.1.3
*/


#define NOFILE 1
#define MEMERR 2
#define FILEERR 3
#define PTRERR 4
#define STRERR 5
#define STRPOSERR 6

typedef struct Te
{
	int lenghtString;
	char* StringPos;
}Text_t;

int Nerror = 0;

/**
*@ \brief Main part of application.
* Function create array of pointer and read text from file.
*@ \param [in,out] StringCount Count of strings in text.
*@ \param [in,out] Textlen Count of all symbols in text.
*@ \return All of input parameters and array of pointers.
*/
Text_t* InitText(int* StringCount, size_t *Textlen);

/**
*@ \brief Sorting function for one of the hallmarks.
* Function will sort array of pointer start to compare from the begin or from the end.
*@ \param [in,out] text Array of pointer.
*@ \param [in] key Key use as hallmarks for sorting
*@ \param [in] StringCount Count of string
*@ \param [in] Textlen Count of text symbols
*@ \return Ok if all right
*/
int sortText(Text_t *text, int key, int *StringCount, size_t Textlen);

/**
*@ \breif Function for cutting rubbish
*@ \param [in] text Array of pointer with text.
*@ \param [in] StringCount Count of strings in text.
*@ \param [in] Textlen Count of text symbols.
*@ \param [in] key Hallmark for sorting.
*/
void findEnd(Text_t *text, int* StringCount, size_t Textlen, int key);

/**
*@ \breif Print text function.
*@ \param [in] text Array of pointer with text.
*@ \param [in] StringCount Count of strings in text.
*@ \param [in] key Hallmarks for sorting and printing
*@ \return Ok if all right
*/
int printText(Text_t *text, int StringCount, int key);

/**
*@ \breif The liberation of used memory.
*@ \return Ok if all right.
*/
int Struct_Destrucktor(Text_t *This);

/**
* \brief Print string function.
* \param [in,out] fout file, where string will be print
* \param [in] string string which will be print
*/
void printStr(FILE* fout, char* string);

/**
*@ \breif The liberation of used memory.
*@ \return Ok if all right.
*/
int Struct_Destrucktor(Text_t*);

/**
*@ \brief My little string compare
*@ \param [in] string1, string2 String what will be compare
*@ \return -1 if string1 > string2, if string1 = string2 - return 0.
*/
int mlStrcmp(char* string1, char* string2);

/**
*@ \brief My little string compare from the string end
*@ \param [in] string1, string2 String what will be compare
*@ \return -1 if string1 > string2, if string1 = string2 - return 0.
*/
int mlStrcmpEnd(Text_t string1, Text_t string2);

/**
*@ \breif Function which check the symbol if it punctuation
*@ \param [in] string, numb Checking symbol
*@ \return -1 if symbol if punctuaion, 0  if it isn't punctuation.
*/
int IsPunct(char* string, int numb);

/**
*@ \brief Swap pointer
*@ \param [in,out] first,second Pointers which will be swapped.
*@ \return Swapped pointers.
*/
void swapPtr(Text_t *first, Text_t *second); 

/**
*@ \breif Error Print
*@ \param [in] Nerror Key for unlock the problem
*/
void ErrPrint(int Nerror);


int main()
{
	int key = 0;
	setlocale(LC_ALL, "rus");
	printf("Enter '1' if you want to sort poem in forward order \n"
		"Enter '2' if you want to sort poem in reverse order and get new part of poem \n"
		"You choise > ");
	if (!scanf_s("%d", &key) || (key != 1 && key != 2))
	{
		printf("Wrong format. Try again (maybe without brackets)\n"
			"> ");
		key = getchar();
		if (!scanf_s("%d", &key)) printf("Sorry, I'm closing.\n");
	}
	//unsigned int start_time = clock();

	int StringCount = 0;
	size_t Textlen = 0;
	Text_t *text = InitText(&StringCount, &Textlen);

	int isOkSort = sortText(text, key, &StringCount, Textlen);
	assert(isOkSort);
	int isOkPrint = printText(text, StringCount, key);
	assert(isOkPrint);
	int isOkMemory = Struct_Destrucktor(text);
	assert(isOkMemory);

	//unsigned int end_time = clock();
	//unsigned int search_time = end_time - start_time;
	//printf("%u\n", search_time);
	return 0;
}

void ErrPrint(int Nerror)
{
	FILE* ferr;
	errno_t err = fopen_s(&ferr, "Error.txt", "w");
	switch (Nerror)
	{
	case 1: fprintf(ferr, "You haven't input file!\n");
	case 2: fprintf(ferr, "You have problems with memmory allocation\n");
	case 3: fprintf(ferr, "Text was not read or file is empty\n");
	case 4: fprintf(ferr, "Asking for fail pointer\n");
	case 5: fprintf(ferr, "Asking for Fail string\n");
	case 6: fprintf(ferr, "Asking for fail strings` symbol\n");
	}
}

Text_t* InitText(int* StringCount, size_t *Textlen)
{
	setlocale(LC_ALL, "rus");
	FILE *filein;
	errno_t err = fopen_s(&filein, "input.txt", "rb");

	if (filein == NULL)
		Nerror = NOFILE;

	else
	{
		fseek(filein, 0, SEEK_END);
		*Textlen = ftell(filein);
		if (!(*Textlen)) perror("Ftell Error");
		rewind(filein);

		char *buffer = (char*)calloc(*Textlen + 1, sizeof(*buffer));
		assert(!buffer);
		if (buffer == NULL)
			Nerror = MEMERR;

		fread((char*)buffer, *Textlen, sizeof(*buffer), filein);
		if (buffer == 0) Nerror = FILEERR;
		ErrPrint(Nerror);
		if (fclose(filein) == -1) perror("Error with closing file\n");


		buffer[*Textlen] = '\0';

		*StringCount = 0;
		int i;
		for (i = 0; i <= (int)*Textlen; i++)
		{
			if (buffer[i] == '\r')
				*StringCount += 1;
			while (buffer[i] == '\r' || buffer[i] == '\n')
				i++;
		}

		Text_t *text = new Text_t[*StringCount + 1];

		assert(text);
		if (!text) Nerror = MEMERR;
		ErrPrint(Nerror);
		//perror("array of pointers was not create");

		int n = 0, nOld = 1;
		i = 1;
		while (buffer[n++] != '\r');
		(&text[0])->StringPos = buffer;
		(&text[0])->lenghtString = n - 1;
		n = n + 2;

		while (i < *StringCount)
		{
			int k = n;

			while (buffer[n] != '\r')
				n++;

			assert(0 <= i && i < *StringCount);
			if (!(0 <= i && i < *StringCount))
				Nerror = PTRERR;
			ErrPrint(Nerror);
			//perror("Asking for fail pointer");
			(&text[i])->StringPos = buffer + (k - 1)*sizeof(buffer[0]);
			(&text[i])->lenghtString = n - k + 1;
			i++;
			while (buffer[n] == '\r' || buffer[n] == '\n')
				n++;
			n = n + 1;
		}
		return text;
	}
	return NULL;
}

int sortText(Text_t *text, int key, int *StringCount, size_t Textlen)
{
	assert(text);
	if (!text) Nerror = MEMERR;
	ErrPrint(Nerror);
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
				if (!(&text[i]) && !(&text[i + jump])) Nerror = STRERR;
				if (mlStrcmp((&text[i + jump])->StringPos, (&text[i])->StringPos) == -1)
				{
					if (!(&text[i]) && !(&text[i + jump])) Nerror = STRERR;
					assert(&text[i] && &text[i + jump]);
					swapPtr(&text[i], &text[i + jump]);
					swapped = true;
				}
				ErrPrint(Nerror);
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
			{
				if (!(&text[i]) && !(&text[i + jump])) Nerror = STRERR;
				if (mlStrcmpEnd(text[i + jump], text[i]) == -1)
				{
					assert(&text[i] && &text[i + jump]);
					if (!(&text[i]) && !(&text[i + jump])) Nerror = STRERR;
					swapPtr(&text[i], &text[i + jump]);
					swapped = true;
				}
				ErrPrint(Nerror);
			}
		}
	}
	findEnd(text, StringCount, Textlen, key);
	return 1;
}

void findEnd(Text_t *text, int* StringCount, size_t Textlen, int key)
{
	if (key == 1)
	{
		for (int i = 0; i < *StringCount; i++)
		{
			if (!text[i].StringPos)
				Nerror = STRPOSERR;
			assert(text[i].StringPos);
			ErrPrint(Nerror);

			if (text[i].StringPos[0] >= '1' && text[i].StringPos[0] <= '9')
				*StringCount = i;
		}
	}
	else
	{
		for (int i = 1; i < *StringCount; i++)
		{
			if (*(char*)text[i].StringPos - 3 >= '1' && *(char*)text[i].StringPos - 3 <= '9')
				*StringCount = i;
		}
	}
}

int printText(Text_t *text, int StringCount, int key)
{
	FILE* fout;
	errno_t err = fopen_s(&fout, "output.txt", "w");
	int numStr = 0;

	int a = 0, b = 0; /*! Using for rhyme*/

	if (key == 2)
	{
		for (int i = 0; i < 1; i++)
		{
			srand(time(0));
			a = rand() % (StringCount - 1);
			printStr(fout, text[a].StringPos);
			b = rand() % (StringCount - 1);
			printStr(fout, text[b].StringPos);
			a += rand() % (5) + 1;
			printStr(fout, text[a].StringPos);
			b += rand() % (5) + 1;
			printStr(fout, text[b].StringPos);

			a = rand() % (StringCount - 1);
			printStr(fout, text[a].StringPos);
			a += rand() % (5) + 1;
			printStr(fout, text[a].StringPos);
			b = rand() % (StringCount - 1);
			printStr(fout, text[b].StringPos);
			b += rand() % (5) + 1;
			printStr(fout, text[b].StringPos);

			a = rand() % (StringCount - 1);
			printStr(fout, text[a].StringPos);
			b = rand() % (StringCount - 1);
			printStr(fout, text[b].StringPos);
			b += rand() % (5) + 1;
			printStr(fout, text[b].StringPos);
			a += rand() % (5) + 1;
			printStr(fout, text[a].StringPos);

			a = rand() % (StringCount - 1);
			printStr(fout, text[a].StringPos);
			a += rand() % (5) + 1;
			printStr(fout, text[a].StringPos);

			fprintf(fout, "\n");
		}
	}
	else
	while (numStr < StringCount - 1)
	{
		printStr(fout, text[numStr].StringPos);
		numStr++;
	}

	fclose(fout);
	return 1;
}

void printStr(FILE* fout, char* string)
{
	int num = 0;
	bool is_text = false;

	for (int i = 0; string[i] != '\r'; i++)
	if (!IsPunct(string, i))
		is_text = true;

	if (is_text)
	while (string[num] != '\0')
	{

		assert(string[num]);
		if (!string[num])
			Nerror = STRPOSERR;
		if (string[num] != '\r')
		{
			fprintf(fout, "%c", string[num]);
			num += 1;
		}
		else if (string[num]>0 && string[num] < 255)
		{
			fprintf(fout, "\n");
			break;
		}
		else
		{
			printf("What the %*&#!?");
		}
	}
}


int Struct_Destrucktor(Text_t *This)
{
	assert(This);
	if (This == NULL)
		Nerror = MEMERR;
	delete[]This;
	return 1;
}

int mlStrcmp(char* string1, char* string2)
{
	int i = 0, j = 0;

	if (string1 || string2)
		Nerror = STRERR;
	assert(string1 && string2);
	if (!string1 || !string2) perror("String is fault\n");

	while (string1[i] != '\r' && string2[j] != '\r')
	{
		while (IsPunct(string1, i))
			i++;
		while (IsPunct(string2, j))
			j++;
		if (!IsPunct(string1, i) && !IsPunct(string2, j))
		{
			assert(string1[i] && string2[j]);
			if (string1[i] || string2[j])
				Nerror = STRPOSERR;
			if (!string1[i] || !string2[j]) perror("Symbol is fault\n");
			if (string1[i] == string2[j])
			{
				i++;
				j++;
			}
			else return (string1[i] > string2[j]) ? 1 : (string1[i] < string2[j]) ? -1 : 0;
		}
	}
	ErrPrint(Nerror);
	return 0;
}

int IsPunct(char* string, int numb)
{
	assert(string[numb]);
	if (string[numb])
		Nerror = STRPOSERR;
	return (unsigned int)string[numb] > 0 && (unsigned int)string[numb] < 48 || (unsigned int)string[numb] > 57 && (unsigned int)string[numb] < 64 ||
		(unsigned int)string[numb] == '«' || (unsigned int)string[numb] == '»' || (unsigned int)string[numb] == '—' ? 1 : 0;
	ErrPrint(Nerror);
}

int mlStrcmpEnd(Text_t string1, Text_t string2)
{
	int i = 0;

	assert(string1.StringPos && string2.StringPos);
	if (!string1.StringPos || !string2.StringPos)
		Nerror = STRPOSERR;
	//perror("String is fault\n");

	i = 1;
	int j = 1;

	if (string2.StringPos[string2.lenghtString] >= 'A' && string2.StringPos[string2.lenghtString] <= 'Z' && string1.StringPos[string1.lenghtString] >= 'A' && string1.StringPos[string1.lenghtString] <= 'Z')
		return 0;
	else while (string1.lenghtString - i + 1 >= 0 && string2.lenghtString - j + 1 >= 0)
	{
		while (IsPunct(string1.StringPos, string1.lenghtString + 1 - i))
			i++;
		while (IsPunct(string2.StringPos, string2.lenghtString + 1 - j))
			j++;
		if (!IsPunct(string1.StringPos, string1.lenghtString + 1 - i) && !IsPunct(string2.StringPos, string2.lenghtString + 1 - j))
		{
			if (string1.StringPos[string1.lenghtString + 1 - i] == string2.StringPos[string2.lenghtString + 1 - j])
			{
				i++;
				j++;
			}
			return string1.StringPos[string1.lenghtString + 1 - i] > string2.StringPos[string2.lenghtString + 1 - j] ? 1 : string1.StringPos[string1.lenghtString + 1 - i] < string2.StringPos[string2.lenghtString + 1 - j] ? -1 : 0;
		}
	}
	ErrPrint(Nerror);
	return 0;
}

void swapPtr(Text_t *first, Text_t *second)
{
	assert(first && second);
	if (!first || !second)
		Nerror = PTRERR;
	//	perror("Pointers are damaged \n");
	Text_t tmp = *first;
	*first = *second;
	*second = tmp;
	ErrPrint(Nerror);
}
