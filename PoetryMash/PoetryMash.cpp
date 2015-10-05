#include "stdafx.h"

/**
*@mainpage
*\brief Poetry Mash program
*\author Kachanov Vova
*\version 1.1.3
*/

int _tmain(int argc, _TCHAR* argv[])
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
	char** text = InitText(&StringCount,&Textlen);

	//int isOkSort = sortText(text, key, &StringCount, Textlen);
	int isOkSort = sortText(text, key, &StringCount, Textlen);
	assert(isOkSort);
	int isOkPrint = printText(text, StringCount, key);
	assert(isOkPrint);
	int isOkMemory = freeMemory(text);
	assert(isOkMemory);

	//unsigned int end_time = clock();
	//unsigned int search_time = end_time - start_time;
	//printf("%u\n", search_time);
	return 0;
}

