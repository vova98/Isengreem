// ENLang.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <string.h>
#include <cassert>
#include <cmath>
#include <ctype.h>
#include "F_work.h" 

#define OK 1

#define LD top->left->data
#define RD top->right->data
#define LT top->left->type
#define RT top->right->type
#define TD top->data
#define TR top->right
#define TL top->left

struct lex
{
	int type;
	char* val;
	char* pos;
	lex() : type(), val(""), pos(""){}
};

enum Types { T_var = 1, T_op = 2, T_num = 3, T_func = 4, T_Mop = 5};
lex *s = NULL;
FILE* Fdotty = NULL;
#include "TreeBuilder.h"
int PrintTree(node* top, int* count);
int Print(node* top, FILE* fout);
int DottyTree(node* top);

//enum E_TOKEN_TYPES
//{
//	T_ResWord = 0, //ключевое (зарезервированное) слово
//	T_Operator,    //оператор
//	T_StrConstant, //строковая константа
//	T_IntConstant, //числовая константа
//	T_Variable,    //переменная
//	T_Function,    //функция
//	T_Devider,     //разделитель
//	T_Unknown      //тип не определен, либо не известен
//};

#include "lex_analys.h"

int _tmain(int argc, _TCHAR* argv[])
{
	char* buffer = ReadFile(L"tempLang.txt");
	if (buffer == NULL) { printf("NO FILE!!"); return 1; }
	int countOfLexem = 0;
	lex* lexic = Lexer(buffer, &countOfLexem);

	errno_t err1 = fopen_s(&Fdotty, "E:\\C++\\Derivative\\Derivative\\dumpTree.gv", "w");
	fprintf(Fdotty, "graph graphname {");

	for (int i = 0; i < countOfLexem; i++)
	{
		printf("lexem number %d :\n"
			"value <%s>\n"
			"type <%d>\n"
			"current pos <%s>\n\n", i, lexic[i].val, lexic[i].type, lexic[i].pos);
	}

	node* top = GetG0(lexic);
	if (!top) printf("SYNTAX ERROR!!!\n"
		"at this symbol %s \n", s->pos);
	int count = 0;
	PrintTree(top, &count);

	FILE* fout = NULL;
	errno_t err = fopen_s(&fout, "Expression.txt", "w");
	Print(top, fout);
	DottyTree(top);

	fprintf(Fdotty,"}");
	fclose(Fdotty);
	system("E:\\C++\\Graphviz2.38\\bin\\dotty.exe E:\\C++\\Derivative\\Derivative\\dumpTree.gv");
	system("pause");

	return 0;
}

int PrintTree(node* top, int* count)
{
	if (top == NULL) return 0;

	for (int i = 0; i < *count; i++)
		printf("----");
	if (top->type != T_num)
		printf("<%s>(%d) \n", TD, top->type);
	else printf("<%.3f>(%d) \n", atof(TD), top->type);

	if (top->left != NULL){ (*count)++; PrintTree(top->left, count); }
	if (top->right != NULL){ (*count)++; PrintTree(top->right, count); }
	(*count)--;

	return OK;
}

int DottyTree(node* top)
{
	if (!top) return NULL;

	if (top->left) { fprintf(Fdotty, "%d -- %d;\n", top, top->left); DottyTree(top->left); }

	fprintf(Fdotty, "%d[fontsize = 25", top);
	if (top->type == T_op) fprintf(Fdotty, ",color = blue");
	if (top->type == T_Mop) fprintf(Fdotty, ",color = red, shape = box");
	if (top->type == T_func) fprintf(Fdotty, ",color = green");
	if (top->type == T_var) fprintf(Fdotty, ",color = grey");
	fprintf(Fdotty, ",label=\"%s\"];\n", top->data);
	if (top->right) { fprintf(Fdotty, "%d -- %d;\n", top, top->right); DottyTree(top->right); }
}

int Print(node* top, FILE* fout)
{
	if (!top || !fout) return NULL;
	if (top->type == T_func)
	{
		fprintf(fout, "%s", top->data);
		fprintf(fout, "(");
		if (top->right) Print(top->right, fout);
		else Print(top->left, fout);
		fprintf(fout, ")");
	}
	else if (top->type == T_Mop)
	{
		fprintf(fout, "%s", top->data);
		if (top->left) { fprintf(fout, " ("); Print(top->left, fout); fprintf(fout, ") "); }
		//fprintf(fout, "(");
		if (top->right) Print(top->right, fout);
		else Print(top->left, fout);
		fprintf(fout, "\n");
	}
	else
	{
		if (top->left) { fprintf(fout, " "); Print(top->left, fout); }
		fprintf(fout, "%s", top->data);
		if (top->right) { Print(top->right, fout); fprintf(fout, " "); }
	}

	return OK;
}