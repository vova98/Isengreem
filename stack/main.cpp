
//#include "stdafx.h"
#include <cassert>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define OK 1
#define print(s) printf("%s failed in \n file - <%s> \n on <%d> string", #s, __FILE__, __LINE__)

int Error = 0;
const int BAD = 0;

struct stack_t
{
	int* data;
	int count;
	int size;
};

int Stack_ctor(stack_t *This);
int Stack_dtor(stack_t *This);
int Stack_push(stack_t *This, int val);
int Stack_pop(stack_t *This);
int Stack_add(stack_t *This);
int Stack_sub(stack_t *This);
int Stack_mul(stack_t *This);
int Stack_divi(stack_t *This);
int Stack_Ok(stack_t* This, int line_count);
int Stack_Dump(stack_t *This);
int Assert_ok(stack_t This);
int readCommand(stack_t* This, const char* argv);
int write_answer(stack_t* This);

enum commands {tmp, push, pop, add, sub, mul, divi, end};
#include <iostream>

int main(int argc, char* argv[])
{
	stack_t stk1;
	Stack_ctor(&stk1);

	for (int i = 0; i < argc; i++)
		printf("#%s# \n", argv[i]);

	const char* argv1 = "commands.asm";
	int ResultOfDo = readCommand(&stk1, (const char*)argv[argc-1]);
	if (ResultOfDo == 0) printf("Wrong Command. \n"
                                "WHAT ARE YOU DOING? READ HELP ONE'S MORE TIME!");

	Stack_dtor(&stk1);

	return 0;
}

int Stack_Ok(stack_t* This, int line_count)
{
	assert(This);
	assert(This->count >= 0 && This->count <= line_count);
	Error = 0;
	return OK;
}

int Stack_Dump(stack_t *This)
{
	FILE* flog = fopen("log.txt", "w");;
	//errno_t err = fopen_s(&flog, "Log.txt", "w");
	if (Error)
		fprintf(flog, "Stack_t(ok) \n");
	else
		fprintf(flog, "%Stack_t(ERROR) \n");

	fprintf(flog, "{ \n"
		"size = %d \n"
		"count = %d \n"
		"data = ", This->size, This->count);

	for (int i = 0; i < This->size; i++)
		fprintf(flog, "[%d] %d \n", i, This->data[i]);
	return OK;
}

int Stack_ctor(stack_t *This)
{
	int* (This->data) = (int*)calloc(2, sizeof(int));
	This->count = 0;
	This->size = 2;
	Assert_ok(*This);
	/*for (int i = 0; i < 100; i++)
		This->data[i] = 0;
    */
	memset(This->data, 0, This->size);
	if (!Stack_Ok(This, 1))
		Assert_ok(*This);
	return OK;

}

int Stack_dtor(stack_t *This)
{
	Assert_ok(*This);
	memset(This->data, -1, This->size);
	This->size = 0;
	This->count = 0;
	return OK;
}

int Assert_ok(stack_t This)
{
	if (This.count < 0 || This.count > This.size)
	{
		Stack_Dump(&This);
		print(Stack);
		abort();
	}
	return OK;
}

int Stack_push(stack_t *This, int val)
{
	Assert_ok(*This);
	if (This->count >= This->size)
		This->size++;
	if (This->size < 100)
	{
		This->data[This->count++] = val;
		Assert_ok(*This);
		return OK;
	}
	printf("Stackoverflow\n");
	return -1;
}

int Stack_pop(stack_t *This)
{
	Assert_ok(*This);
	This->count--;
	Assert_ok(*This);
	return This->data[This->count];
}

int Stack_add(stack_t *This)
{
	Assert_ok(*This);
	assert(This->count - 2 >= 0);
	int valFirst = Stack_pop(This);
	int valSecond = Stack_pop(This);
	Stack_push(This, valFirst + valSecond);
	return OK;
}

int Stack_mul(stack_t *This)
{
	Assert_ok(*This);
	assert(This->count - 2 >= 0);
	int valFirst = Stack_pop(This);
	int valSecond = Stack_pop(This);
	Stack_push(This, valFirst * valSecond);
	return OK;
}

int Stack_divi(stack_t *This)
{
	Assert_ok(*This);
	assert(This->count - 2 >= 0);
	int valFirst = Stack_pop(This);
	int valSecond = Stack_pop(This);
	Stack_push(This, valFirst / valSecond);
	return OK;
}

int Stack_sub(stack_t *This)
{
	Assert_ok(*This);
	assert(This->count - 2 >= 0);
	int valFirst = Stack_pop(This);
	int valSecond = Stack_pop(This);
	Stack_push(This, (-valFirst) + valSecond);
	return OK;
}



int readCommand(stack_t* This, const char* argv)
{
	int command = 1, val = 0;
    printf("%s \n", argv);

	FILE* fcomm = fopen(argv, "rb");
	if (fcomm == NULL) printf("WTF??");
	//errno_t err = fopen_s(&fcomm, argv, "rb");
	const char* argv1 = "result.txt";

	FILE* fres = fopen(argv1, "w");
	//errno_t err1 = fopen_s(&fres, argv1, "w");

	if(!fscanf(fcomm, "%d", &command)) command = 0;

	while (command != end)
	{
		switch (command)
		{
		case push:
		{
            fscanf(fcomm, "%d", &val);
            Stack_push(This, val);
            break;
		}
		case pop:	fprintf(fres,"%d \n", Stack_pop(This)); break;
		case add:	Stack_add(This); break;
		case sub:	Stack_sub(This); break;
		case mul:	Stack_mul(This); break;
		case divi:	Stack_divi(This); break;
		case end:	fprintf(fres, "Result is - &d \n Goodbye!\n", This->data[This->count]); return This->data[This->count]; break;
		default:
		printf("Unknown command \n");
		 fclose(fcomm);
        fclose(fres);
        return BAD;
		}
		if(!fscanf(fcomm, "%d", &command)) command = 0;
	}
    fclose(fcomm);
    fclose(fres);
return OK;
}
