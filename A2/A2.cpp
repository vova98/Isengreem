// A2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	int num = 0;
	cin >> num;
	//scanf_s("%d", &num);
	int** mas = InputDynamicAndTranspon(num);
	
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
			cout << mas[i][j] << " ";
			//printf("%d ", mas[i][j]);
		printf("\n");
	}

	return 0;
}

