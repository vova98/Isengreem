// Stack.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include "arithmetic.h"

int _tmain(int argc, _TCHAR* argv[])
{

	stack_t st1 = {};
	cpu stk1 = {};
	Stack_ctor(&stk1, &st1);


	char* argvName = (char*)calloc(wcslen(argv[1]), sizeof(argvName));
	size_t len = wcstombs(argvName, argv[1], wcslen(argv[1]));
	//const char* argv1 = "commands.asm";
	int CountOfCom = 0;
	const int* commandBuff = ReadComm(argv[argc - 1], &CountOfCom);
	int ResultOfDo = doCommand(&stk1, commandBuff, argv[argc - 1], CountOfCom);

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
	ASSERT_OK(&This->Stack);
	return -1;
}

int Stack_push_ax(cpu *This)
{
	ASSERT_OK(This);
	if (This->Stack.count >= This->Stack.size)
		This->Stack.size++;
	if (This->Stack.size < SIZE)
	{
		This->Stack.data[This->Stack.count++] = This->ax;
		ASSERT_OK(This);
		return OK;
	}
	printf("Stackoverflow\n");
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	return -1;
}

int Stack_push_bx(cpu *This)
{
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	if (This->Stack.count >= This->Stack.size)
		This->Stack.size++;
	if (This->Stack.size < SIZE)
	{
		This->Stack.data[This->Stack.count++] = This->bx;
		Assert_ok(&This->Stack, __LINE__, __FILE__);
		return OK;
	}
	printf("Stackoverflow\n");
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	return -1;
}
int Stack_push_cx(cpu *This)
{
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	if (This->Stack.count >= This->Stack.size)
		This->Stack.size++;
	if (This->Stack.size < SIZE)
	{
		This->Stack.data[This->Stack.count++] = This->cx;
		Assert_ok(&This->Stack, __LINE__, __FILE__);
		return OK;
	}
	printf("Stackoverflow\n");
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	return -1;
}
int Stack_push_dx(cpu *This)
{
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	if (This->Stack.count >= This->Stack.size)
		This->Stack.size++;
	if (This->Stack.size < SIZE)
	{
		This->Stack.data[This->Stack.count++] = This->dx;
		Assert_ok(&This->Stack, __LINE__, __FILE__);
		return OK;
	}
	printf("Stackoverflow\n");
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	return -1;
}

int Stack_pop_Nx(cpu *This)
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
