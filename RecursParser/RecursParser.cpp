// RecursParser.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <cassert>

#include "F_work.h"

#define OK 1

const char *s = NULL;
int GetG0(const char* buffer);
int GetN();
int GetT();
int GetE();
int GetP();

int _tmain(int argc, _TCHAR* argv[])
{
	const char* buffer = NULL;
	if (argv[1] == NULL)
		buffer = ReadFile(L"RecursParser.txt");
	else buffer = ReadFile(argv[1]);
	//s = (char*)buffer;

	int val = GetG0(buffer);

	printf("eval = <%d> \n", val);

	return 0;
}


int GetG0(const char* buffer)
{
	s = buffer;
	int val = GetE();
	if (*s == NULL) return val;
	else return OK;
}

int GetE()
{
	int val = GetT();
	while (*s == '-' || *s == '+')
	{
		int op = *s++;
		int val2 = GetT();
		if (op == '+') val += val2;
		if (op == '-') val -= val2;
	}
	return val;
}

int GetN()
{
	int val = 0;
	while (*s >= '0' && *s <= '9')
	{
		val = val * 10 + *s - '0';
		*s++;
	}
	return val;
}

int GetT()
{
	int val = GetP();
	while (*s == '/' || *s == '*')
	{
		int op = *s++;
		int val2 = GetP();
		if (op == '/') val /= val2;
		if (op == '*') val *= val2;
	}
	return val;
}

int GetP()
{
	if (*s == '(')
	{
		s++;
		int val = GetE();
		if (*s == ')') { s++; return val; }
	}
	else return GetN();
}

