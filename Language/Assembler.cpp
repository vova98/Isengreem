#include "stdafx.h"
#include <iostream>
#include <cassert>
#include <stdlib.h>
#include <cstring>


#define OK 1
#define BAD -1
#define INFI 100

#define JUMP_ASM(num)									\
commandBuff[(*j)++] = num;								\
(*k) = 0;												\
while (buffer[++(*i)] != '\r')							\
currname[(*k)++] = buffer[(*i)];						\
Flag = false;											\
for (int l = 0; l < SIZEOFMARKARRAY; l++)				\
{														\
	if (!strcmp(arrayOfMarker[l].name, currname))		\
	{													\
		commandBuff[(*j)++] = arrayOfMarker[l].numb;	\
		Flag = true;									\
		break;											\
	}													\
}														\
for (int q = 0; q < 10;  q++)							\
	currname[q] = '\0';									\
if (!Flag) Nerror = BUCELL;								\
	break;	

const int SIZEOFMARKER = 30;
const int SIZEOFMARKARRAY = 500;
FILE* flog = NULL;
errno_t err1 = fopen_s(&flog, "LOG.txt", "w");

struct markers
{
	char name[SIZEOFMARKER];
	int numb;
};


/**
Here will be doxygen comment soon
*/

void PrintHelp();
void PrintVersion();
void PrintError(int line, char* buffer);
char* ReadComm(_TCHAR* argv);
char* ReadFile(_TCHAR* argv);
int* assembl(const char* buffer, int* j);
int* moreSize(int* commandBuff, int size);
void ErrPrint(int Nerror);
int printInFile(int* commandBuff, int j, _TCHAR* argv);
int choseCommand(char* comm, int* i, int* j, const char* buffer, int val, int* commandBuff, markers* arrayOfMarker, int* Step, int* k, char* currname, int* arrayOfFunc, int* NumFunc, int* returns, int* numCalls);
const char* wtoc(const wchar_t* w_string);
void code();

int Nerror = 0;

enum ErrorNum { NOFILE = 1, MEMERR = 2, FILEERR = 3, BUCELL = 4, PTRERR = 5 };
enum commands_str {
	push = 'push', pop = 'pop', add = 'add', mul = 'mul', sub = 'sub', divi = 'div',
	end = 'end', out = 'out', sqr = 'sqr', root = 'sqrt', ja = 'ja', jae = 'jae', jb = 'jb', jbe = 'jbe',
	je = 'je', jne = 'jne', jmp = 'jmp', call = 'call', ret = 'ret', err = 'err', in = 'in', inf = 'inf'
};



int _tmain(int argc, _TCHAR* argv[])
{
	//code();
	const char* help = "--help";
	const char* version = "--version";
	const char* argv1 = "commands.txt";
	int j = 0;
	int Is_Print_Ok = 0;

	if (argc < 2)
	{
		printf("Give me a name of file, please. \n");
		return 0;
	}

	const char* argvName = wtoc(argv[1]);

	if (!strcmp(argvName, help))
		PrintHelp();
	else if (!strcmp(argvName, version))
		PrintVersion();
	else
	{
		const char *buffer = ReadFile(argv[1]);
		int* commandBuffer = assembl(buffer, &j);

		if (argc >= 2)
			Is_Print_Ok = printInFile(commandBuffer, j, *argv);
		else
		{
			_TCHAR* argv2 = L"commands.asm";
			Is_Print_Ok = printInFile(commandBuffer, j, argv2);
		}

		if (Is_Print_Ok == -1) printf("Error\n");
	}
	fclose(flog);  
	return 0;
}

const char* wtoc(const wchar_t* w_string)
{
	const char* argvName = (char*)calloc(wcslen(w_string), sizeof(argvName));
	size_t len = wcstombs((char*)argvName, w_string, wcslen(w_string));
	return argvName;
}

int printInFile(int* commandBuff, int countOfCommands, _TCHAR* argv)
{
	const char* argvName = wtoc(argv);
	//const char* argvName = (char*)calloc(wcslen(argv), sizeof(argvName));
	//size_t len = wcstombs((char*)argvName, argv, wcslen(argv));

	argvName = "commands.asm";
	FILE *fileout = NULL;
	errno_t err = fopen_s(&fileout, argvName, "w");

	fprintf(fileout, "%d\n", countOfCommands);
	for (int i = 0; i < countOfCommands; i++)
		fprintf(fileout, "%d ", commandBuff[i]);

	PrintError(__LINE__, "");
	if (fclose(fileout) == -1) return BAD;
	return OK;
}

int assembly_push(int *i, const char* buffer, int* j, int* commandBuff, int val)
{
	char numbuff[12] = "\0";
	int k = 0;
	if (i == NULL || j == NULL || commandBuff == NULL || buffer == NULL)
		Nerror = PTRERR;
	(*i)++;
	if (buffer[(*i)] >= 'a' && buffer[(*i)] <= 'z')
	{
		switch (buffer[*i])
		{
		case 'a':commandBuff[(*j)++] = 10; break;
		case 'b':commandBuff[(*j)++] = 24; break;
		case 'c':commandBuff[(*j)++] = 25; break;
		case 'd':commandBuff[(*j)++] = 26; break;
		}
		while (buffer[*i] != '\r')
			(*i)++;
	}
	else
	{
		while (buffer[(*i)] != '\r')
			numbuff[k++] += buffer[(*i)++];
		val = atoi(numbuff);
		commandBuff[(*j)++] = 1;
		commandBuff[(*j)++] = val;

	}
	val = 0;
	PrintError(__LINE__, (char*)buffer);
	return 0;
}

int FindMarkers(int sizeOfInFile, const char* buffer, markers* arrayOfMarker, int* Step)
{
	if (buffer == NULL || arrayOfMarker == NULL || Step == NULL) Nerror = PTRERR;
	PrintError(__LINE__, (char*)buffer);
	char tmpStr[SIZEOFMARKER] = "";
	int endOfMain = 0;
	int i = -1, k = 0, l = 0;
	while (i < sizeOfInFile)
	{
		
		while (buffer[++i] != '\r' && buffer[i] > 0)
			tmpStr[k++] = buffer[i];
		if (strstr(tmpStr, "end"))
			endOfMain = 1;
		if (strstr(tmpStr, ":"))
		{	
				tmpStr[k - 1] = '\0';
				strcpy(arrayOfMarker[l].name, tmpStr);
				arrayOfMarker[l].numb = *Step;
				(*Step)--;
				l++;
		}
		i += 1;
		k = 0;
		(*Step)++;
		memset(tmpStr, '\0', SIZEOFMARKER);
	}
	return OK;
}

int* assembl(const char* buffer, int* j)
{
	if (buffer == NULL || j == NULL) Nerror = PTRERR;
	PrintError(__LINE__, (char*)buffer);
	int sizeOfInFile = strlen(buffer);
	int FirstComing = 0;
	markers arrayOfMarker[SIZEOFMARKARRAY] = { 0 };
	markers arrayOfCalls[SIZEOFMARKARRAY] = { 0 };
	const char* space = " ";
	const char endl = '\n';
	char comm[SIZEOFMARKER] = {};
	int i = 0, k = 0, NumFunc = 0, numCalls = 0;
	int size = sizeOfInFile;
	char currname[SIZEOFMARKER] = {};
	int returns[SIZEOFMARKARRAY] = {};

	int* commandBuff = (int*)calloc(size, sizeof(*commandBuff));
	if (commandBuff == NULL) Nerror = MEMERR;
	PrintError(__LINE__, (char*)buffer);
	int arrayOfFunc[SIZEOFMARKARRAY] = {};
	const char *buffer_tmp = (const char*)calloc(sizeOfInFile, sizeof(buffer[0]));
	if (buffer_tmp == NULL) Nerror = MEMERR;
	PrintError(__LINE__, (char*)buffer);

	for (i = 0; i < sizeOfInFile; i++)
		(char)buffer_tmp[i] = buffer[i];

	int n_old = 0;
	int val = 0, Step = 0, MarkerNum = 1;

	FindMarkers(sizeOfInFile, buffer, arrayOfMarker, &Step);
	Step = 0;

	for (i = 0; i < sizeOfInFile; i++)
		(char)buffer[i] = buffer_tmp[i];

	i = 0;
	while (buffer[i] != 'Н' && buffer[i] != '\0')
	{
		k = 0;
		if (!(buffer[i] >= 'a' && buffer[i] <= 'z' || buffer[i] == ':' || buffer[i] >= '0' && buffer[i] <= '9')) printf("Unknown symbol /%c/ on <%d> step of your prog\n", buffer[i], Step);
		assert(buffer[i] >= 'a' && buffer[i] <= 'z' || buffer[i] == ':' || buffer[i] >= '0' && buffer[i] <= '9');
		while (buffer[i] >= 'a' && buffer[i] <= 'z' || buffer[i] == ':' || buffer[i] >= '0' && buffer[i] <= '9')
		{
			comm[k] = buffer[i];
			i++;
			k++;
		}
		comm[14] = '\0';
		_strrev(comm);
		choseCommand(comm, &i, j, buffer, val, commandBuff, arrayOfMarker, &Step, &k, currname, arrayOfFunc, &NumFunc, returns, &numCalls);
		k = 0;
		currname[0] = '\0';

		if (*j >= size - 2)
		{
			commandBuff = moreSize(commandBuff, size);
		}
		while (buffer[i] != endl && buffer[i] != '\0')
			i++;
		i++;

		if (!strcmp(comm, "end")) numCalls = 0;
		for (int j = n_old; j < i; j++)
			(char)buffer[j] = 'q';
		n_old = i;
		for (int l = 0; l < 5; l++)
			comm[l] = '\0';
		Step++;
	}

	return commandBuff;
}

int choseCommand(char* comm, int* i, int* j, const char* buffer, int val, int* commandBuff, markers* arrayOfMarker, int* Step, int *k, char* currname, int* arrayOfFunc, int* NumFunc, int* returns, int* numCalls)
{
	bool Flag = false;

	switch (*((long*)comm))
	{

#define DEF_CMD(name, num, count)\
	case name: commandBuff[(*j)++] = num; break;
#define JMP_CMD(name, num, count)\
	case name: JUMP_ASM(num);

#include "enum_comm.h"

#undef DEF_CMD
#undef JMP_CMD

	case push:
		assembly_push(i, buffer, j, commandBuff, val);
		break;

	case pop:
		(*i) += 1;
		switch (buffer[(*i)])
		{
		case 'a':commandBuff[(*j)++] = 18; break;
		case 'b':commandBuff[(*j)++] = 21; break;
		case 'c':commandBuff[(*j)++] = 22; break;
		case 'd':commandBuff[(*j)++] = 23; break;
		default: commandBuff[(*j)++] = 2; break;
		}
		(*i)++;
		break;
	case in: commandBuff[(*j)++] = 29; break;
	case inf: commandBuff[(*j)++] = 30; break;
	case out: commandBuff[(*j)++] = 8; break;
	case call:
		arrayOfFunc[(*NumFunc)++] = *j;
		commandBuff[(*j)++] = 19;								
			(*k) = 0;												
		while (buffer[++(*i)] != '\r')							
			currname[(*k)++] = buffer[(*i)];
		returns[(*numCalls)++] = (*Step) + 1;
		for (int l = 0; l < SIZEOFMARKARRAY; l++)				
		{														
		if (!strcmp(arrayOfMarker[l].name, currname))		
		{													
		commandBuff[(*j)++] = arrayOfMarker[l].numb;	
		Flag = true;									
		break;											
		}												
		}													
		if (!Flag)
		{
			Nerror = BUCELL;
			for (int il = 0; il < SIZEOFMARKARRAY; il++)
				fprintf(flog, "%s\n", arrayOfMarker[il].name);
		}
		else
		{
			for (int il = 0; il < SIZEOFMARKARRAY; il++)
				fprintf(flog, "%s\n", arrayOfMarker[il].name);
		}
		PrintError(__LINE__, (char*)buffer);
			break;
	case ret:
		commandBuff[(*j)++] = 17;
		commandBuff[(*j)++] = returns[(*numCalls) - 1];

		i = i;
		break;
	case jmp: 
		
		commandBuff[(*j)++] = 17;								
			(*k) = 0;												
		while (buffer[++(*i)] != '\r')							
			currname[(*k)++] = buffer[(*i)];						
			Flag = false;											
		for (int l = 0; l < SIZEOFMARKARRAY; l++)				
		{														
			if (!strcmp(arrayOfMarker[l].name, currname))		
			{													
				commandBuff[(*j)++] = arrayOfMarker[l].numb;	
				Flag = true;									
				//break;											
			}													
		}														
		for (int q = 0; q < 10; q++)							
			currname[q] = '\0';									
		if (Flag == 0)
		{
			Nerror = BUCELL;
			for (int il = 0; il < SIZEOFMARKARRAY; il++)
				fprintf(flog, "%s\n", arrayOfMarker[il].name);
		}
		else
		{
			for (int il = 0; il < SIZEOFMARKARRAY; il++)
				fprintf(flog,"%s\n", arrayOfMarker[il].name);
		}
		PrintError(__LINE__, (char*)buffer);
			break;


		//JUMP_ASM(17);
	default:
		assert(1); (*Step)--;
		;
	}
	
	return OK;
}

int* moreSize(int* commandBuff, int size)
{
	int i = 0;
	int* commandBuff_old = (int*)calloc(size, sizeof(int));
	if (commandBuff == NULL) Nerror = MEMERR;
	PrintError(__LINE__, "");
	while (i < size)
		commandBuff_old[i] = commandBuff[i];
	commandBuff = (int*)realloc(commandBuff, size * 2 * sizeof(int));
	if (commandBuff == NULL) Nerror = MEMERR;
	PrintError(__LINE__, "");
	while (i < size)
		commandBuff[i] = commandBuff_old[i];

	return commandBuff;
}

//unlink имя файла

void PrintHelp()
{
	printf("This program used for assembling commands for stack \n"
		"For normal working of this programm you should white the \n"
		"commands in file and put name of these file to calling of programm.\n");
}

void PrintVersion()
{
	printf("Version 1.2.0 \n");
}

//char* ReadComm(_TCHAR* argv)
//{
//	//const char* argv1 = "commands.txt";
//	FILE *filein = NULL;
//	errno_t err = fopen_s(&filein, wtoc(argv), "rb");
//	//errno_t err = fopen_s(&filein, argv1, "rb");
//
//	if (filein != NULL)
//	{
//		fseek(filein, 0, SEEK_END);
//		size_t Textlen = ftell(filein);
//		if (!(Textlen)) perror("Ftell Error");
//		rewind(filein);
//
//		char *buffer = new char[Textlen + 1];
//		if (buffer == NULL)
//			Nerror = MEMERR;
//		PrintError(__LINE__, buffer);
//
//		fread((char*)buffer, Textlen, sizeof(*buffer), filein);
//		if (buffer == 0) Nerror = FILEERR;
//		PrintError(__LINE__, buffer);
//
//		if (fclose(filein) == -1) perror("Error with closing file\n");
//		fclose(filein);
//		printf("%s\n", buffer);
//		return buffer;
//	}
//	else
//		Nerror = NOFILE;
//	PrintError(__LINE__, buffer);
//	return "-1";
//
//}

char* ReadFile(_TCHAR* argv)
{
	//const char* argv1 = "hash_works.txt";
	FILE *filein = NULL;
	errno_t err = fopen_s(&filein, wtoc(argv), "rb");
	//errno_t err = fopen_s(&filein, argv1, "rb");

	if (filein != NULL)
	{
		fseek(filein, 0, SEEK_END);
		size_t Textlen = ftell(filein);
		if (!(Textlen)) perror("Ftell Error");
		rewind(filein);

		char *buffer = new char[Textlen + 1];
		//assert(buffer);
		if (buffer == NULL)
			Nerror = MEMERR;
		PrintError(__LINE__, buffer);

		fread((char*)buffer, Textlen, sizeof(*buffer), filein);
		if (buffer == 0) Nerror = FILEERR;
		PrintError(__LINE__, buffer);

		buffer[Textlen] = '\0';

		if (fclose(filein) == -1) perror("Error with closing file\n");
		fclose(filein);
		return buffer;
	}
	else
		//fclose(filein);
		Nerror = NOFILE;
	PrintError(__LINE__, "");
	return NULL;

}

void PrintError(int line, char* buffer)
{
	if (Nerror != 0)
	{
		printf("On <%d> line you have such trouble:\n", line);
		switch (Nerror)
		{
		case 1: printf("No input file. Try again.\n"); break;
		case 2: printf("Problems with memmory alloc.\n"); break;
		case 3: printf("Problems with opening file.\n"); break;
		case 4: printf("Too much same markers or not enought marker.\n %s", buffer); system("pause"); break;
		case 5: printf("Error with pointers, check transfer.\n"); break;
			default:
				break;
		}
	}
}




