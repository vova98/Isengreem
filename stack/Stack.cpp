// Stack.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <cassert>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "arithmetic.h"
//#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{

	stack_t st1 = {};
	cpu stk1 = {};
	Stack_ctor(&stk1, &st1);


	char* argvName = (char*)calloc(wcslen(argv[0]), sizeof(argvName));
	size_t len = wcstombs(argvName, argv[0], wcslen(argv[0]));

	//for (int i = 0; i < argc; i++)
		//std::cout << argv[i] << std::endl;
	//	wprintf(L"%s \n", argv[i]);

	const char* argv1 = "commands.asm";
	const int* commandBuff = ReadComm(argv[argc - 1]);
	int ResultOfDo = doCommand(&stk1, commandBuff, argv[argc - 1]);
	if (ResultOfDo == 0) printf("Wrong Command. \n"
		"WHAT ARE YOU DOING? READ HELP ONE'S MORE TIME!");

	Stack_dtor(&st1);
	Stack_dtor(&stk1);  
	
	return 0;
}

int Stack_Dump(stack_t *This)
{
	FILE* flog = NULL;
	errno_t err = fopen_s(&flog, "Log.txt", "a+");
	if (Error)
		fprintf(flog, "Stack_t(ok) \n");
	else
		fprintf(flog, "Stack_t(ERROR) \n");

	fprintf(flog, "{ \n"
		"size = %d \n"
		"count = %d \n"
		"data = ", This->size, This->count);

	for (int i = 0; i < This->size; i++)
		fprintf(flog, "[%d] %d \n", i, This->data[i]);

	return OK;
}

///*
//int Stack_ctor(stack_t *This)
//{
//	//(This->data) = (int*)calloc(2, sizeof(int));
//	This->count = 0;
//	This->size = 2;
//	Assert_ok(This, __LINE__, __FILE__);
//	/*
//	for (int i = 0; i < 100; i++)
//		This->data[i] = 0;
//		*/
//	memset(This->data, 0, This->size);
//	Assert_ok(This, __LINE__, __FILE__);
//	return OK;
//}

int Stack_ctor(cpu *This, stack_t* Stack)
{
	for (int i = 0; i < SIZE; i++)
		This->Stack.data[i] = 0;
	This->Stack.count = 0;
	This->Stack.size = 2;
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	memset(This->Stack.data, 0, This->Stack.size);
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	return OK;
}

int Stack_dtor(stack_t *This)
{
	Assert_ok(This, __LINE__, __FILE__);
	memset(This->data, -1, This->size);
	This->size = 0;
	This->count = 0;
	return OK;
}

int Stack_dtor(cpu *This)
{
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	memset(This->Stack.data, -1, This->Stack.size);
	This->Stack.size = 0;
	This->Stack.count = 0;
	return OK;
}

int Assert_ok(const stack_t* This, int line, const char* file)
{
	if (This->count < 0 || This->count > This->size)
	{
		Stack_Dump((stack_t*)This);
		PRINT(Stack, line, file);
		//abort();
	}
	return OK;
}

int Stack_push(cpu *This, int val)
{
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	if (This->Stack.count >= This->Stack.size)
		This->Stack.size++;
	if (This->Stack.size < SIZE)
	{
		This->Stack.data[This->Stack.count++] = val;
		Assert_ok(&This->Stack, __LINE__, __FILE__);
		return OK;
	}
	printf("Stackoverflow\n");
	return -1;
}

int Stack_push_ax(cpu *This)
{
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	if (This->Stack.count >= This->Stack.size)
		This->Stack.size++;
	if (This->Stack.size < SIZE)
	{
		This->Stack.data[This->Stack.count++] = This->ax;
		Assert_ok(&This->Stack, __LINE__, __FILE__);
		return OK;
	}
	printf("Stackoverflow\n");
	return -1;
}

int Stack_pop_ax(cpu *This)
{
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	This->Stack.count--;
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	return This->Stack.data[This->Stack.count++];
}

int Stack_pop(cpu *This)
{
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	This->Stack.count--;
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	int value = This->Stack.data[This->Stack.count];
	This->Stack.data[This->Stack.count] = 0;
	return value;
}
