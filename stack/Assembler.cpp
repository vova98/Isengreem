// Assembler.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <cassert>
#define OK 1

void PrintHelp();
void PrintVersion();
char* ReadComm(const char* argv1);
int assembl(const char* buffer, const char* argv);
void ErrPrint(int Nerror);
void code();

int Nerror = 0;

enum ErrorNum { NOFILE, MEMERR, FILEERR };
enum commands {push = 13104, pop = 12432, add = 9700, mul = 12753, sub = 13455, divi = 10500, end = 11110};



int main(int argc, char* argv[])
{

	//code();
	const char* help = "--help";
	const char* version = "--version";
	//const char* argv1 = "commands.txt";
	//const char* argv2 = "commands.asm";
	const char* buffer = NULL;
	int Is_Ok = 0;
	

	if (argv[1] == help)
		PrintHelp();
	else if (argv[1] == version)
		PrintVersion();
	else
		buffer = ReadComm(argv[1]);
	//if (argc > 2) 
	if (argc >=2)
	Is_Ok = assembl(buffer, argv[2]);
	else 
	{
		const char* argv2 = "commands.asm";
		Is_Ok = assembl(buffer, argv2);
	}

	if (Is_Ok == 0) printf("Error\n");
	
	 
	return 0;
}

int assembl(const char* buffer, const char* argv)
{

	FILE *fileout = NULL;
	errno_t err = fopen_s(&fileout, argv, "w");
	const char* space = " ";
	const char endl = '\n';

	int i = 0, val = 0;
	while (buffer[i] != '\0')
	{
		switch ((int)buffer[i] * (int)buffer[i + 1])
		{
		case push:  {
						fprintf(fileout, "1 ");
						while (buffer[++i] != ' ');
						while (buffer[++i] != '\n')
							fprintf(fileout, "%c", buffer[i]);
						break;
					}
		case pop: fprintf(fileout, "2 \n"); break;
		case add: fprintf(fileout, "3 \n"); break;
		case mul: fprintf(fileout, "5 \n"); break;
		case sub: fprintf(fileout, "4 \n"); break;
		case divi: fprintf(fileout, "6 \n"); break;
		case end: fprintf(fileout, "7 \n"); break;
		}
		while (buffer[i++] != endl && buffer[i++] != '\0');
	}
	return OK;
	fclose(fileout);
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

