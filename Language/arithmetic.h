#pragma once 
#include <cassert>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <cmath>

#define OK 1
#define BAD -1
#define INF 1000
#define PRINT(s, line, file) printf("%s failed in \n file - <%s> \n on <%d> string", #s, file, line)

#define ASSERT_OK()													\
	if (This->Stack.count < 0 || This->Stack.count > This->Stack.size)	\
	{																	\
		Stack_Dump((stack_t*)This);										\
		PRINT(Stack, __LINE__, __FILE__);								\
	}																	\
	return OK;															\

#define JUMP_IF_1(op)													\
		Assert_ok(&This->Stack, __LINE__, __FILE__);			        \
		int valFirst = Stack_pop(This);								    \
		int valSecond = Stack_pop(This);							    \
		int newStep = 0;											    \
		Assert_ok(&This->Stack, __LINE__, __FILE__);				    \
		if (valSecond op valFirst)										\
			findStep(jump, current, i, commandbuff);					\
		Stack_push(This, valSecond);									\
		Stack_push(This, valFirst);										\
		return 0;													

#define ARITHM_1(op)													\
		Assert_ok(&This->Stack, __LINE__, __FILE__);					\
		int valFirst = Stack_pop(This);									\
		int valSecond = Stack_pop(This);								\
		Assert_ok(&This->Stack, __LINE__, __FILE__);					\
		Stack_push(This, valFirst op valSecond);						\
		return OK;



int Error = 0;
const int SIZE = 500;

struct stack_t
{
	int data[SIZE];
	int count;
	int size;
};
struct cpu
{
	int ax;
	int bx;
	int cx;
	int dx;
	struct stack_t Stack;
};



enum commands_num { 
	push = 1, pop = 2, pop_ax = 18, add = 3, sub = 4, mul = 5, divi = 6, end = 7, 
	out = 8, sqr = 9, push_ax = 10, ja = 11, jae = 12, jb = 13, jbe = 14, je = 15, jne = 16, jmp = 17, call = 19,
	ret = 20, pop_bx = 21, pop_cx = 22, pop_dx = 23, push_bx = 24, push_cx = 25, push_dx = 26 , root = 27, err = 28,
	in = 29, inf = 30
};


/**
Here will be doxygen comment soon
*/

int Stack_ctor(stack_t *This);
int Stack_ctor(cpu *This, stack_t *Stack);
int Stack_dtor(stack_t *This);
int Stack_dtor(cpu *This); 
int Stack_push(cpu *This, int val);
int Stack_push_ax(cpu *This);
int Stack_push_bx(cpu *This);
int Stack_push_cx(cpu *This);
int Stack_push_dx(cpu *This);
int Stack_pop_Nx(cpu *This);
int Stack_pop(cpu *This);
int Stack_pop_ax(cpu *This);
int Stack_add(cpu *This);
int Stack_sub(cpu *This);
int Stack_mul(cpu *This);
int Stack_divi(cpu *This);
int Stack_sqr(cpu *This);
int Stack_root(cpu *This);
int Stack_ja(cpu *This, int jump, int current);
int Stack_Dump(stack_t *This);
int Assert_ok(const stack_t* This, int line, const char* file);
int readCommand(stack_t* This, _TCHAR* argv);
int findStep(int jump, int* current, int* i, const int* commandbuff);
int* ReadComm(_TCHAR* argv);

int Stack_add(cpu *This)
{
	ARITHM_1(+);
}
int Stack_mul(cpu *This)
{
	ARITHM_1(*);
}
int Stack_divi(cpu *This)
{
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	int valFirst = Stack_pop(This);
	int valSecond = Stack_pop(This);
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	if (valFirst != 0) 
	Stack_push(This, valSecond / valFirst);
	else return BAD;
	return OK;
}
int Stack_sub(cpu *This)
{
	Assert_ok(&This->Stack, __LINE__, __FILE__);					
		int valFirst = Stack_pop(This);									
		int valSecond = Stack_pop(This);	
		Assert_ok(&This->Stack, __LINE__, __FILE__);					
		Stack_push(This, valSecond - valFirst);						
		return OK;
}

int Stack_sqr(cpu *This)
{
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	int valFirst = Stack_pop(This);
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	Stack_push(This, valFirst * valFirst);
	return OK;
}

int Stack_root(cpu *This)
{
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	int valFirst = Stack_pop(This);
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	Stack_push(This, (int)sqrt(valFirst));
	return OK;
}

int Stack_print(cpu *This)
{
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	int value = Stack_pop(This);
	Stack_push(This, value);
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	return value;
}

int Stack_ja(cpu *This, int jump, int* current, int* i, const int* commandbuff)
{
	JUMP_IF_1(>);//пишеться так
}
int Stack_jae(cpu *This, int jump, int* current, int* i, const int* commandbuff)
{
	JUMP_IF_1(>=);
}
int Stack_jb(cpu *This, int jump, int* current, int* i, const int* commandbuff)
{
	JUMP_IF_1(< );
}
int Stack_jbe(cpu *This, int jump, int* current, int* i, const int* commandbuff)
{
	JUMP_IF_1(<=);
}
int Stack_je(cpu *This, int jump, int* current, int* i, const int* commandbuff)
{
	JUMP_IF_1(==);
}
int Stack_jne(cpu *This, int jump, int* current, int* i, const int* commandbuff)
{
	JUMP_IF_1(!=);
}

int findStep(int jump, int* current, int* i, const int* commandbuff)
{
	int t = 0;
	int flag = 0;
	for (int q = 0; q < jump; q++)
	{
		switch (commandbuff[t])
		{
		case 1: t += 2; break;

#define DEF_CMD(name, num, count) ;
#define JMP_CMD(name, num, count)\
		case num: t += count; break;
#include "enum_comm.h"
#undef JMP_CMD
#undef DEF_CMD

		case 17: t += 2; break;
		case 19: t += 2; break;
		case 20: t += 2; break;
		default: t++; break;
		}
	}
	if (!flag)
	{
		*i = t - 1;
		*current = jump - 1;
	}
	return 0;
}

int doCommand(cpu* This, const int* commandBuff, _TCHAR* argv, int CountOfComm)
{
	int i = 0, val = 0, Step = 0, tmp = 0, argum = 0;
	bool argum_flag = false;
	int* conform = (int*)calloc(SIZE, sizeof(int));
	memset(conform, 0, SIZE);
	const char* argv1 = "result.txt";
	FILE* fres = NULL;
	errno_t err1 = fopen_s(&fres, argv1, "w");

	while(i < CountOfComm)
	{
		switch (commandBuff[i])
		{
		case push:
		{
					 i++;
					 val = commandBuff[i];
					 Stack_push(This, val);
					 argum_flag = true;
					 break;
		}
		case in:		printf("Enter value >"); scanf_s("%d", &val);  printf("\n"); Stack_push(This, val); break;
		case inf:		Stack_push(This, INF); break;
		case pop_ax:	This->ax = Stack_pop_Nx(This); break;
		case pop_bx:	This->bx = Stack_pop_Nx(This); break;
		case pop_cx:	This->cx = Stack_pop_Nx(This); break;
		case pop_dx:	This->dx = Stack_pop_Nx(This); break;
		case pop:	tmp = Stack_pop(This); break;

#define JMP_CMD(name, num, count)\
		case name: Stack_##name(This, commandBuff[++i], &Step, &i, commandBuff); break;
#define DEF_CMD(name, num, count)\
		case name: Stack_##name(This); break;
#include "enum_comm.h"
		case end:	
			return  This->Stack.data[This->Stack.count];
			break;
		case out:	
			fprintf(fres, "%d ", Stack_print(This));
			break;
		case err:	fprintf(fres, "No solutions!\n"); break;
		case push_ax:Stack_push(This, This->ax); break; //Stack_push_ax(This); break;
		case push_bx:Stack_push(This, This->bx); break; //Stack_push_bx(This); break;
		case push_cx:Stack_push(This, This->cx); break; //Stack_push_cx(This); break;
		case push_dx:Stack_push(This, This->dx); break; //Stack_push_dx(This); break;
		case call:	findStep(commandBuff[++i], &Step, &i, commandBuff); break;
		case ret:	findStep(commandBuff[++i], &Step, &i, commandBuff); 
			Step-= 2; break;
		case jmp:	findStep(commandBuff[++i], &Step, &i, commandBuff);   break;
		default:
			fclose(fres);
			return 0;	
		}

		if (argum_flag) argum = 1;
		else argum = 0;
		argum_flag = false;
		i = (i + 1);
		Step++;
		conform[Step] = i;
	}
	fclose(fres);
	return OK;
}

int* ReadComm(_TCHAR* argv, int* CountOfCom)
{
	const char* argvName = (char*)calloc(wcslen(argv), sizeof(argv));
	size_t len = wcstombs((char*)argvName, argv, wcslen(argv));
	FILE *filein = NULL;
	errno_t err = fopen_s(&filein, argvName, "rb");

	fseek(filein, 0, SEEK_END);
	size_t Textlen = ftell(filein);
	if (!(Textlen)) perror("Ftell Error");
	rewind(filein);

	int* numbuffer = (int*)calloc(Textlen * 2 / 3, sizeof(*numbuffer));
	if (numbuffer == NULL) perror("Calloc Error");
	int currNum = 0, i = 1, argum = 0;
	if (!fscanf(filein, "%d", CountOfCom)) perror("Scanf buffer Error");
	numbuffer[0] = currNum;

	for (int i = 0; i < *CountOfCom; i++)
		if (!fscanf(filein, "%d", &numbuffer[i])) perror("Scanf buffer Error");;
		
	if (fclose(filein) == -1) perror("Error with closing file\n");
	fclose(filein);
	return numbuffer;

}
