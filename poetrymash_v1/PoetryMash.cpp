// PoetryMash.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
	
	int key = 0;
	scanf_s("%d", &key);
	unsigned int start_time = clock();
	int count = 0;
	char** text = InitText(&count, key);
	FILE* fout;
	errno_t err = fopen_s(&fout, "output.txt", "w");

	int num = 0, k = 0;
	while (num < count)
	{
		if (text[num][k] != '\r')
		{
			//assert((int)(text[num][k])>0 && (int)(text[num][k])<255);
			fprintf(fout, "%c", text[num][k]);
			k += 1;
		}
		else if ((int)(text[num][k])>0 && (int)(text[num][k]) < 255)
		{
			fprintf(fout, "\n");
			num += 1;
			k = 0;
		}
		else
			printf("What the Fuck!?");
	}

	delete[]text;
	fclose(fout);
	unsigned int end_time = clock();
	unsigned int search_time = end_time - start_time;
	printf("%u\n", search_time);
	return 0;
}

