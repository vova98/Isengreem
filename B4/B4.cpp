// B4.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	FILE * filein;
	errno_t err = fopen_s(&filein,"input.txt", "r");
//	std::ofstream fout("output.txt");
	bool flag = true;
	char letter = '0', prevletter = '0';
	int lettercode = 0;

	if (filein == NULL) perror("Ошибка открытия файла\n");
	else
		int isOK = fileFilter(filein);

	return 0;
}

