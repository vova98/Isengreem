#pragma once 


#define OK 1
#define BAD -1
#define PRINT(s, line, file) printf("%s failed in \n file - <%s> \n on <%d> string", #s, file, line)

int Error = 0;
const int SIZE = 100;

struct stack_t
{
	int data[SIZE];
	int count;
	int size;
};
struct cpu
{
	int ax;
	struct stack_t Stack;
};



enum commands { tmp, push = 1, pop = 2, add = 3, sub = 4, mul = 5, divi = 6, end = 7, 
out = 8, sqr = 9, push_ax = 10, ja = 11, jae = 12, jb = 13, jbe = 14, je = 15, jne = 16, jmp = 17};

int Stack_ctor(stack_t *This);
int Stack_ctor(cpu *This, stack_t *Stack);
int Stack_dtor(stack_t *This);
int Stack_dtor(cpu *This);
int Stack_push(cpu *This, int val);
int Stack_push_ax(cpu *This);
int Stack_pop(cpu *This);
int Stack_pop_ax(cpu *This);
int Stack_add(cpu *This);
int Stack_sub(cpu *This);
int Stack_mul(cpu *This);
int Stack_divi(cpu *This);
int Stack_sqr(cpu *This);
int Stack_ja(cpu *This, int jump, int current);
int Stack_Dump(stack_t *This);
int Assert_ok(const stack_t* This, int line, const char* file);
int readCommand(stack_t* This, _TCHAR* argv);
int* ReadComm(_TCHAR* argv);

int Stack_add(cpu *This)
{
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	int valFirst = Stack_pop(This);
	int valSecond = Stack_pop(This);
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	Stack_push(This, valFirst + valSecond);
	return OK;
}

int Stack_mul(cpu *This)
{
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	int valFirst = Stack_pop(This);
	int valSecond = Stack_pop(This);
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	Stack_push(This, valFirst * valSecond);
	return OK;
}

int Stack_divi(cpu *This)
{
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	int valFirst = Stack_pop(This);
	int valSecond = Stack_pop(This);
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	Stack_push(This, valSecond / valFirst);
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

int Stack_print(cpu *This)
{
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	int value = Stack_pop(This);
	Stack_push(This, value);
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	return value;
}

int Stack_ja(cpu *This, int jump, int current)
{
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	int valFirst = Stack_pop(This);
	int valSecond = Stack_pop(This);
	int newStep = 0;
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	if (valSecond > valFirst) newStep = jump;
	else newStep = current;
	Stack_push(This, valSecond);
	Stack_push(This, valFirst);
	return newStep;
}


int Stack_ja_1(cpu *This, int jump, int* current , int* i , const int* commandbuff)
{
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	int valFirst = Stack_pop(This);
	int valSecond = Stack_pop(This);
	int newStep = 0;
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	if (valSecond > valFirst)
	{
		int t = 0;
		int flag = 0;
		for (int q = 0; q < jump; q++)
		{
			switch (commandbuff[t])
			{
			case 1: t += 2; break;
			case 11: t += 2; break;
			case 12: t += 2; break;
			case 13: t += 2; break;
			case 14: t += 2; break;
			case 15: t += 2; break;
			case 16: t += 2; break;
			case 17: t += 2; break; 
			case 7: q = jump; flag = 1; break;
			default: t++; break;
			}
		}
		if (!flag)
		{
			*i = t - 1;
			*current = jump - 1;
		}

	}
	Stack_push(This, valSecond);
	Stack_push(This, valFirst);
	return 0;
}

int Stack_jae(cpu *This, int jump, int current)
{
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	int valFirst = Stack_pop(This);
	int valSecond = Stack_pop(This);
	int newStep = 0;
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	if (valSecond >= valFirst) newStep = jump;
	else newStep = current;
	Stack_push(This, valSecond);
	Stack_push(This, valFirst);
	return newStep;
}
int Stack_jb(cpu *This, int jump, int current)
{
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	int valFirst = Stack_pop(This);
	int valSecond = Stack_pop(This);
	int newStep = 0;
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	if (valSecond < valFirst) newStep = jump;
	else newStep = current;
	Stack_push(This, valSecond);
	Stack_push(This, valFirst);
	return newStep;
}
int Stack_jbe(cpu *This, int jump, int current)
{
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	int valFirst = Stack_pop(This);
	int valSecond = Stack_pop(This);
	int newStep = 0;
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	if (valSecond <= valFirst) newStep = jump;
	else newStep = current;
	Stack_push(This, valSecond);
	Stack_push(This, valFirst);
	return newStep;
}
int Stack_je(cpu *This, int jump, int current)
{
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	int valFirst = Stack_pop(This);
	int valSecond = Stack_pop(This);
	int newStep = 0;
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	if (valSecond == valFirst) newStep = jump;
	else newStep = current;
	Stack_push(This, valSecond);
	Stack_push(This, valFirst);
	return newStep;
}
int Stack_jne(cpu *This, int jump, int current)
{
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	int valFirst = Stack_pop(This);
	int valSecond = Stack_pop(This);
	int newStep = 0;
	Assert_ok(&This->Stack, __LINE__, __FILE__);
	if (valSecond != valFirst) newStep = jump;
	else newStep = current;
	Stack_push(This, valSecond);
	Stack_push(This, valFirst);
	return newStep;
}

int doCommand(cpu* This, const int* commandBuff, _TCHAR* argv)
{
	int countOfComm = 0;
	while (commandBuff[countOfComm++] != 7);


	int i = 0, val = 0, Step = 0;
	int* conform = (int*)calloc(SIZE, sizeof(int));
	const char* argv1 = "result.txt";
	FILE* fres = NULL;
	errno_t err1 = fopen_s(&fres, argv1, "w");


	while (commandBuff[i] != end)
	{
		switch (commandBuff[i])
		{
		case push:
		{
					 i++;
					 val = commandBuff[i];
					 Stack_push(This, val);
					 break;
		}
		case pop:	This->ax = Stack_pop_ax(This); break;
		case add:	Stack_add(This); break;
		case sub:	Stack_sub(This); break;
		case mul:	Stack_mul(This); break;
		case divi:	Stack_divi(This); break;
		case end:	fprintf(fres, "Result is - %d \n Goodbye!\n", This->Stack.data[This->Stack.count]);
			return  This->Stack.data[This->Stack.count]; break;
		case out:	fprintf(fres, "%d ", Stack_print(This)); break;
		case sqr:	Stack_sqr(This); break;
		case push_ax:Stack_push_ax(This); break;
		case ja:	//i = Stack_ja(This, conform[commandBuff[i++]], Step); break;
			Stack_ja_1(This, commandBuff[++i], &Step, &i, commandBuff); break;
		case jae:	i = Stack_jae(This, commandBuff[i++], Step); break;
		case jb:	i = Stack_jb(This, commandBuff[i++], Step); break;
		case jbe:	i = Stack_jbe(This, commandBuff[i++], Step); break;
		case je:	i = Stack_je(This, commandBuff[i++], Step); break;
		case jne:	i = Stack_jne(This, commandBuff[i++], Step); break;
		case jmp:	Step = commandBuff[++i]; i = conform[commandBuff[i]] - 1;  break;

		default:
			fclose(fres);
			return 0;	
		}

		/*for (int l = 0; l < This->Stack.size; l++)
			printf("%d ", This->Stack.data[l]);
		printf("\n ax - <%d> \n", This->ax);
*/
		i = (i+1) % countOfComm;
		Step++;
		conform[Step] = i;
	}
	fclose(fres);
	return OK;
}

int* ReadComm(_TCHAR* argv)
{
	const char* argvName = (char*)calloc(wcslen(argv), sizeof(argv));
	size_t len = wcstombs((char*)argvName, argv, wcslen(argv));
	FILE *filein = NULL;
	errno_t err = fopen_s(&filein, argvName, "rb");

	{
		fseek(filein, 0, SEEK_END);
		size_t Textlen = ftell(filein);
		if (!(Textlen)) perror("Ftell Error");
		rewind(filein);

		char *buffer = (char*)calloc(Textlen, sizeof(char));
		assert(buffer);
		
		//fread((char*)buffer, Textlen, sizeof(*buffer), filein);
		//ErrPrint(Nerror);	

		int* numbuffer = (int*)calloc(Textlen*2/3, sizeof(*numbuffer));
		assert(numbuffer);
		int currNum = 0, i = 0;
		while (currNum != 7)
		{
			fscanf(filein, "%d", &currNum);
			numbuffer[i] = currNum;
			i++;
		}

		if (fclose(filein) == -1) perror("Error with closing file\n");
		fclose(filein);
		return numbuffer;
	}
}
