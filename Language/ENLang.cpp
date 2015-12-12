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


enum Types { T_var = 1, T_op = 2, T_num = 3, T_func = 4, T_Mop = 5, T_Cfunc = 6 };
lex *s = NULL;
FILE* Fdotty = NULL;

#include "TreeBuilder.h"
#include "translator.h"

int PrintTree(node* top, int* count);
int Print(node* top, FILE* fout);
int PrintHelp();
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
	if (!strcmp(wtoc(argv[1]), "-help"))
	{
		PrintHelp();
		system("pause");
		return 0;
	}
	//char* buffer = ReadFile(L"tempLang.txt");
	char* buffer = ReadFile(argv[1]);
	if (buffer == NULL) { printf("NO FILE!!"); return 1; }
	int countOfLexem = 0;
	lex* lexic = Lexer(buffer, &countOfLexem);

	errno_t err1 = fopen_s(&Fdotty, "E:\\C++\\Derivative\\Derivative\\dumpTree.gv", "w");
	fprintf(Fdotty, "graph graphname {");

	errno_t err2 = fopen_s(&ftrans, "FileForASM.txt", "w");

	for (int i = 0; i < countOfLexem; i++)
	{
		printf("lexem number %d :\n"
			"value <%s>\n"
			"type <%d>\n"
			"current pos <%s>\n\n", i, lexic[i].val, lexic[i].type, lexic[i].pos);
	}

	Var.vars = new char*[COUNTOFREGISTER];

	node* top = GetG0(lexic);
	if (!top) printf("SYNTAX ERROR!!!\n"
		"at this symbol %s \n", s->pos);
	s++;
	node* funcTop = GetG0(s);
	node* Main = new node;
	NODECTOR(Main, "main", T_op, top, funcTop);
	if (!top) printf("SYNTAX ERROR!!!\n"
		"at this symbol %s \n", s->pos);
	int count = 0;
	PrintTree(Main, &count);

	FILE* fout = NULL;
	errno_t err = fopen_s(&fout, "Expression.txt", "w");
	Print(Main, fout);
	DottyTree(Main);
	int countOfJump = 0, pop = 0, flag = 0;
	Translate(Main, countOfJump, &pop, flag);
	//fprintf(ftrans, "end");
	//reg regis = {};

	fprintf(Fdotty,"}");
	fclose(Fdotty);
	fclose(ftrans);
	/////////////////////////////////////////////////
	//char* FROM = "C:\\Users\\Vladimir\\Documents\\Visual Studio 2013\\Projects\\ENLang\Debug"

	/////////////////////////////////////////////////
	system("E:\\C++\\Graphviz2.38\\bin\\dotty.exe E:\\C++\\Derivative\\Derivative\\dumpTree.gv");
	system("pause");

	return 0;
}
//печать в консоль
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
//распечатка в доттер
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
//печать в файл правильного скобочного выражения
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

int PrintHelp()
{
	char key = ' ';
	printf("Hello!\n"
		"You are using new language EN\n"
		"if you want to know about history of this language enter 'H'\n"
		"if you want to see some example of syntax enter 'S'\n");
	scanf("%c", &key);
	if (key == 'H')
		printf("This language was created by me, Vova, 12.12.15\n");
	if (key == 'S')
	{
		printf("this language has some function:\n"
			"1. if 'I'\n"
			"2. while 'W'\n"
			"3. call 'C'\n"
			"4. main rules 'M'\n"
			"5. out 'O'\n"
			"Enter comand> ");
		char tmp = ' ';
		while (key != 'O')
		{
			scanf("%c%c", &tmp, &key);
			if (key == 'I') printf("\noperator 'if' working like in others programming languages\n"
				"example : if )x > 4(\n"
				"[\n"
				"x = x + 4#\n"
				"]\n"
				"symbols '[' and ']' are neccesarry\n"
				"brackets must be invert - ') x > 4 ('\n");
			if (key == 'W') printf("\noperator 'while' working like in others programming languages\n"
				"and main rules of syntax are the same as in 'if'\n");
			if (key == 'C') printf("\n'call' using for calling of function\n"
				"example: call func()#\n"
				"....\n"
				"end\n"
				"func()\n"
				"[\n"
				"x = x + 4#\n"
				"]\n");
			if (key == 'M') printf("\nat start you must write 'begin' and 'end' in the end of programm\n"
				"all variables must must be declarete by 'var'\n"
				"simpliest mathematic function like '+' '-' '*' '/' 'sqrt(var)' are here\n"
				"in equation you can use brackets like '(x + 3)'\n"
				"after any equations must be '#'\n"
				"there are operators '>', '<', '@' like '==' in C, '!' like '!=' in C\n"
				"if you want to know more about EN you can phone +79853151865\n");

		}
	}
	return OK;
}

