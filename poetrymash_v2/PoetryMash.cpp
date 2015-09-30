// PoetryMash.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
	int key = 0;
	//char codeWord[8] = {};
	printf("Enter '1' if you want to sort poem in forward order \n"
		   "Enter '2' if you want to sort poem in reverse order and get new part of poem \n"
		   "You choise: ");
	scanf_s("%d", &key);

	//unsigned int start_time = clock();

	int count = 0;
	size_t len = 0;
	char** text = InitText(&count,&len);

	int isOkSort = sortText(text, key, &count, len);
	assert(isOkSort);
	int isOkPrint = printText(text, count, key);
	assert(isOkPrint);
	int isOkMemory = freeMemory(text);
	assert(isOkMemory);

	//unsigned int end_time = clock();
	//unsigned int search_time = end_time - start_time;
	//printf("%u\n", search_time);
	return 0;
}

