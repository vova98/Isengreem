// Assembler.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <cassert>
#include <stdlib.h>
#include <cstring>


#define OK 1
#define BAD -1

void PrintHelp();
void PrintVersion();
char* ReadComm(const char* argv1);
int* assembl(const char* buffer);
int* moreSize(int* commandBuff, int size);
void ErrPrint(int Nerror);
int printInFile(int* commandBuff, _TCHAR* argv);
void code();

int Nerror = 0;

enum ErrorNum { NOFILE, MEMERR, FILEERR, BUCELL};
enum commands { push = 'push', pop = 'pop', add = 'add', mul = 'mul', sub = 'sub', divi = 'div',
	end = 'end', out = 'out', sqr = 'sqrt', ja = 'ja', jae = 'jae', jb = 'jb', jbe = 'jbe',
	je = 'je', jne = 'jne', jmp = 'jmp' };

  
int _tmain(int argc, _TCHAR* argv[])
{
	//code();
	const char* help = "--help";
	const char* version = "--version";
	const char* argv1 = "commands.txt";
	int Is_Print_Ok = 0;
	
	if (argc < 2)
	{
		printf("Give me a name of file, please. \n");
		return 0;
	}

	//if (!strcmp(argvName,help))
	//	PrintHelp();
	//else if (!strcmp(argvName,version))
	//	PrintVersion();
	//else
	//{
		const char *buffer = ReadComm(argv1);
		int* commandBuffer = assembl(buffer);
		
		if (argc > 2)
			Is_Print_Ok = printInFile(commandBuffer, *argv);
		else
		{
			_TCHAR* argv2 = L"commands.asm";
			Is_Print_Ok = printInFile(commandBuffer, argv2);
		}

		if (Is_Print_Ok == -1) printf("Error\n");
	 
	return 0;
}

int printInFile(int* commandBuff, _TCHAR* argv)
{
	const char* argvName = (char*)calloc(wcslen(argv), sizeof(argvName));
	size_t len = wcstombs((char*)argvName, argv, wcslen(argv));

	FILE *fileout = NULL;
	errno_t err = fopen_s(&fileout, argvName, "w");

	int i = 0;
	fprintf(fileout, "%d ", commandBuff[i]);
	while (commandBuff[i++] != 7)
		fprintf(fileout, "%d ", commandBuff[i]);

	if(fclose(fileout) == -1) return BAD;
	return OK;
}

int* assembl(const char* buffer)
{
	int sizeOfInFile = strlen(buffer);
	int FirstComing = 0;
	int arrayOfMarker[10] = {0};
	const char* space = " ";
	const char endl = '\n';
	char comm[5] = {};
	int i = 0;
	int size = sizeOfInFile * 2 / 3;
	int* commandBuff = (int*)calloc(size, sizeof(*commandBuff));
	
	const char *buffer_tmp = (const char*)calloc(sizeOfInFile, sizeof(buffer[0]));
	for (i = 0; i < sizeOfInFile; i++)
		(char)buffer_tmp[i] = buffer[i];

OneMoreTime:

	for (i = 0; i < sizeOfInFile; i++)
		(char)buffer[i] = buffer_tmp[i];

	int k = 0, n_old = 0;
	int val = 0, j = 0, Step = 1, MarkerNum = 1;
	
	i = 0;
	//while (buffer[i] != '\0')
	while (i < sizeOfInFile-1)
	{
		k = 0;
		assert(buffer[i] >= 'a' && buffer[i] <= 'z' || buffer[i] == ':' || buffer[i] >= '0' && buffer[i] <= '9');
		while (buffer[i]>='a' && buffer[i]<='z' || buffer[i] == ':' || buffer[i]>='0' && buffer[i]<='9')
		{ 
			comm[k] = buffer[i];
			i++;
			k++;
		}
		comm[4] = '\0';
		_strrev(comm);
		//printf("comm");
			switch (*((long*)comm))
		{
			case push:  
							i++;
							if (buffer[i] >= 'a' && buffer[i] <= 'z')
							{
								while (buffer[i] != '\r')
									i++;
								commandBuff[j++] = 10;
							}
							else
							{
								while (buffer[i] != '\r')
								{
									val = val * 10 + (buffer[i] - '0');
									i++;
								}
								commandBuff[j++] = 1;
								commandBuff[j++] = val;
							}
							val = 0;
							break;

			case pop: commandBuff[j++] = 2; break;
			case add: commandBuff[j++] = 3; break;
			case sub: commandBuff[j++] = 4; break;
			case mul: commandBuff[j++] = 5; break;
			case divi: commandBuff[j++] = 6; break;
			case end: commandBuff[j++] = 7; break;
			case out: commandBuff[j++] = 8; break;
			case sqr: commandBuff[j++] = 9; break;
			case ja: 
				commandBuff[j++] = 11; 
				i++;
				if (arrayOfMarker[buffer[i] - '0'] >= 1)
					commandBuff[j++] = arrayOfMarker[buffer[i] - '0'];
				else j++;
				break;
			case jae:
				commandBuff[j++] = 12;
				i++;
				if (arrayOfMarker[buffer[i] - '0'] >= 1)
					commandBuff[j++] = arrayOfMarker[buffer[i] - '0'];
				else j++;
				break;
			case jb:
				commandBuff[j++] = 13;
				i++;
				if (arrayOfMarker[buffer[i] - '0'] >= 1)
					commandBuff[j++] = arrayOfMarker[buffer[i] - '0'];
				else j++;
				break;
			case jbe:
				commandBuff[j++] = 14;
				i++;
				if (arrayOfMarker[buffer[i] - '0'] >= 1)
					commandBuff[j++] = arrayOfMarker[buffer[i] - '0'];
				else j++;
				break;
			case je:
				commandBuff[j++] = 15;
				i++;
				if (arrayOfMarker[buffer[i] - '0'] >= 1)
				commandBuff[j++] = arrayOfMarker[buffer[i] - '0'];
				else j++;
				break;
			case jne:
				commandBuff[j++] = 16;
				i++;
				if (arrayOfMarker[buffer[i] - '0'] >= 1)
				commandBuff[j++] = arrayOfMarker[buffer[i] - '0'];
				else j++;
				break;
			case jmp:
				commandBuff[j++] = 17;
				i++;
				if (arrayOfMarker[buffer[i] - '0'] >= 1)
					commandBuff[j++] = arrayOfMarker[buffer[i] - '0'];
				else j++;
				break;
			default: 
				if (comm[1] == ':')
				{
					Step--;
					if (arrayOfMarker[comm[0]-'0'] != 0) 
						Nerror = BUCELL;
					else arrayOfMarker[comm[0]-'0'] = Step;
				}
		}
			if (j >= size - 2)
			{
				commandBuff = moreSize(commandBuff, size);
			}
			while (buffer[i] != endl && buffer[i] != '\0')
				i++;
			i++;

			for (int j = n_old; j < i; j++)
				(char)buffer[j] = 'q';
			n_old = i;
			for (int l = 0; l < 5; l++)
				comm[l] = '\0';
			Step++;
	}
	if (FirstComing == 0)
	{
		FirstComing = 1;
		goto OneMoreTime;
	}

	return commandBuff;
}


int* moreSize(int* commandBuff, int size)
{
	int i = 0;
	int* commandBuff_old = (int*)calloc(size, sizeof(int));

	while (i < size)
		commandBuff_old[i] = commandBuff[i];
	commandBuff = (int*)realloc(commandBuff, size * 2 * sizeof(int));
	while (i < size)
		commandBuff[i] = commandBuff_old[i];

	return commandBuff;
}

void code()
{
	char* x = "pu";
	printf("push %d \n", (int)x[0] * (int)x[1]);
	x = "po";
	printf("pop %d \n", (int)x[0] * (int)x[1]);
	x = "ad";
	printf("add %d \n", (int)x[0] * (int)x[1]);
	x = "mu";
	printf("mull %d \n", (int)x[0] * (int)x[1]);
	x = "su";
	printf("sub %d \n", (int)x[0] * (int)x[1]);
	x = "div";
	printf("div %d \n", (int)x[0] * (int)x[1]);
	x = "end";
	printf("end %d \n", (int)x[0] * (int)x[1]);
}

void PrintHelp()
{
	printf("This program used for assembling commands for stack \n"
		"For normal working of this programm you should white the \n"
		"commands in file and put name of these file to calling of programm.\n");
}

void PrintVersion()
{
	printf("Version 1.0.0 \n");
}

char* ReadComm(const char* argv1)
{
	FILE *filein = NULL;
	errno_t err = fopen_s(&filein, argv1, "rb");

	if (filein == NULL)
		Nerror = NOFILE;

	else
	{
		fseek(filein, 0, SEEK_END);
		size_t Textlen = ftell(filein);
		if (!(Textlen)) perror("Ftell Error");
		rewind(filein);

		char *buffer = new char[Textlen + 1];
		//char *buffer = (char*)calloc(Textlen + 1, sizeof(*buffer));
		assert(buffer);
		if (buffer == NULL)
			Nerror = MEMERR;

		fread((char*)buffer, Textlen, sizeof(*buffer), filein);
		if (buffer == 0) Nerror = FILEERR;
		//ErrPrint(Nerror);
		if (fclose(filein) == -1) perror("Error with closing file\n");
		fclose(filein);
		return buffer;
	}
}