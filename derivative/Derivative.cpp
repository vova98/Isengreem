#include "stdafx.h"
#include <cassert>
#include <cmath>
#include "F_work.h"


#define OK 1

#define VAR "variable"
#define OP "operator"
#define NUM "number"

#define CREATEDATA(vertex)		\
	(char*)vertex->data = (char*)calloc(LENGTHOFWORD, sizeof(char));

#define LD top->left->data
#define RD top->right->data
#define LT top->left->type
#define RT top->right->type
#define TD top->data
#define TR top->right
#define TL top->left

#define IS(Var, vaL) !strcmp(Var, vaL)

#define FTOA(Left, Right, op) top->data = ftoa(atof(Left) op atof(Right));

#define NODECTOR(vertex, Data, Type, Left, Right)	\
	vertex->type = Type;							\
	CREATEDATA(vertex)								\
	strcpy(vertex->data, Data);						\
	vertex->left = Left;							\
	vertex->right = Right;


#define DER_MUL												\
	node* newLeft = new node;								\
	node* newRight = new node;								\
	CREATEDATA(newLeft)										\
	CREATEDATA(newRight)									\
															\
	NODECTOR(newRight, RD, TR->type, TR->left, TR->right);	\
															\
	NODECTOR(newLeft, LD, TL->type, TL->left, TL->right);	\
															\
	top->left = Derivation(top->left);						\
	top->right = Derivation(top->right);					\
															\
	node* LeftMul = new node;								\
	node* RightMul = new node;								\
	CREATEDATA(LeftMul)										\
	CREATEDATA(RightMul)									\
															\
	NODECTOR(LeftMul, "*", T_op, TL, newRight);				\
	NODECTOR(RightMul, "*", T_op, TR, newLeft);	


#define MAKENODE(oper)		\
	top->type = oper;		\
	top->left = leaf;		\
	top->right = leaf2;		\
	top->data[0] = op;		\
	leaf = top;


#define FOLDING(op)


struct node
{
	char* data;
	int type;
	node* left;
	node* right;
	node() :data(""), type(), left(NULL), right(NULL){}
};

struct variable
{
	char* data;
	double value;
	double sigma;
	int count;
	variable() :data(), value(), sigma(), count(){}
};

enum Types { T_var = 1, T_op = 2, T_num = 3, T_func = 4 };

const char *s = NULL;
const int LENGTHOFWORD = 5;
const int VARCOUNT = 10;
const double EPS = 0.001;
const int Radix = 10;
//node* NodeCtor(int type, const char op, node* left, node* right);
node* GetG0(const char* buffer);
int PrintTree(node* top, int* count);
int Print(node* top, FILE* fout);
int ÑreateTeXFile(FILE *fout);
int IsFunc(char* val);
void DestroyTree(node* vert);
node* Cleaning(node* top, int* WasCleaned);
void FindVariables(node* tree, int* count, variable* Vars);
node* CreateTotalDer(variable* Vars, int CountofVars);
node* CreateTreatSumm(node* Left, node* Right, variable* Vars, int* count, int Numb);
void CopyTree(node* dest, node* source);
node* CreatePower(variable* Vars, int* count);
node* GetS();
node* GetN();
node* GetT();
node* GetE();
node* GetP();
node* GetVar();
node* GetFunc(char* val);
node* Derivation(node* top);

int _tmain(int argc, _TCHAR* argv[])
{
	int count = 0;
	const char* buffer = NULL;
	if (argv[1] == NULL)
		buffer = ReadFile(L"RecursParser.txt");
	else buffer = ReadFile(argv[1]);
	//s = (char*)buffer;

	FILE* fout = NULL;
	errno_t err = fopen_s(&fout, "Print.txt", "a");

	//if (!ÑreateTeXFile(fout)) return 0;


	node* Tree = GetG0(buffer);//Taking tree
	if (Tree == NULL) { printf("Syntax ERROR\n"); return 0; }
	PrintTree(Tree, &count);
	printf("\n-----------------------\n\n");
	count = 0;
	fprintf(fout, "\nSTART OF PROGRAMM AT <%s>\n", __TIME__);
	Print(Tree, fout);
	fprintf(fout, "\n\n");

	printf("CLEANING ORIGINAL TREE\n\n");
	int WasCleaned = 1;
	node* Cleared_tree = Tree;
	while (WasCleaned)
	{
		WasCleaned = 0;
		Cleared_tree = Cleaning(Cleared_tree, &WasCleaned);
		count = 0;
		PrintTree(Cleared_tree, &count);
		printf("\n-----------------------\n\n");
	}
		variable* Vars = new variable[10];
		int CountOfVars = 0;
		FindVariables(Cleared_tree, &CountOfVars, Vars);
		printf("\n\nVARIABLES\n\n");
		for (int i = 0; i < CountOfVars; i++)
			printf("<%s> count = %d\n", Vars[i].data, Vars[i].count);
		printf("\n\n");

		char Key = '\0';
		printf("What do you want to do with your function:\n"
			"1. Take a partial derivative (P)\n"
			"2. Take a total derivative (T)\n"
			">");
		scanf("%c", &Key);

		if (Key == 'P')
		{

			printf("TAKING THE DERIVATIVE\n\n");
			node* Derivated_tree = Derivation(Cleared_tree);
			PrintTree(Derivated_tree, &count);
			printf("\n-----------------------\n\n");
			Print(Derivated_tree, fout);
			fprintf(fout, "\n\n");

			printf("CLEANING DERIVATIVE TREE\n\n");
			WasCleaned = 1;
			node* Cleared_Derivated_tree = Derivated_tree;
			while (WasCleaned)
			{
				WasCleaned = 0;
				Cleared_Derivated_tree = Cleaning(Cleared_Derivated_tree, &WasCleaned);
				count = 0;
				PrintTree(Cleared_Derivated_tree, &count);
				printf("\n-----------------------\n\n");
			}
			count = 0;
			printf("CLEANED DERIVATIVE TREE\n\n");
			PrintTree(Cleared_Derivated_tree, &count);
			Print(Cleared_Derivated_tree, fout);
			fprintf(fout, "\nEND OF PROGRAMM\n");
			fclose(fout);
			system("start Print.txt");
			system("pause");
			return 0;
		}
		else
		{
			printf("Enter values:\n");
			for (int i = 0; i < CountOfVars; i++)
			{
				printf("\n\t%s = ", Vars[i].data);
				scanf_s("%lg", &Vars[i].value);
				printf("\n\terror %s = ", Vars[i].data);
				scanf_s("%lg", &Vars[i].sigma);
			}
			
			node* TDerivTree = CreateTotalDer(Vars, CountOfVars);
			count = 0;
			printf("\n-----------------------\n\n");
			PrintTree(TDerivTree, &count);
			printf("\n-----------------------\n\n");
			printf("CLEANING DERIVATIVE TREE\n\n");
			WasCleaned = 1;
			while (WasCleaned)
			{
				WasCleaned = 0;
				TDerivTree = Cleaning(TDerivTree, &WasCleaned);
				count = 0;
				PrintTree(TDerivTree, &count);
				printf("\n-----------------------\n\n");
			}

		}

	}

node* CreateTotalDer(variable* Vars, int CountofVars)
{
	
	//node* Summ = new node;
	
	//node* leftVar  = new node;
	
	//node* rightVar = new node;
	//node* Div = new node;
	//node* Power = new node;
	//node* Two = new node;
	////LeftSumm->left  = (node*)malloc(sizeof(node));
	////LeftSumm->right = (node*)malloc(sizeof(node));
	//CREATEDATA(Two);
	//CREATEDATA(Temp);
	//CREATEDATA(Power);
	//CREATEDATA(Div);
	//CREATEDATA(leftVar);
	//CREATEDATA(rightVar);
	//CREATEDATA(Summ);
	//NODECTOR(Two, "2", T_num, NULL, NULL);
	node* RightSumm = new node;
	node* LeftSumm = new node;
	node* Temp = new node;
	node* newtop = new node;
	CREATEDATA(newtop);
	int count = 0;
	switch (CountofVars)
	{
	case 0: return 0; break;
	case 1: LeftSumm = CreatePower(Vars, &count); newtop = LeftSumm; break;
	case 2:
		LeftSumm = CreatePower(Vars, &count);
		RightSumm = CreatePower(Vars, &count);
		NODECTOR(Temp, "+", T_op, LeftSumm, RightSumm);
		newtop = Temp;
		break;
	default:
		LeftSumm = CreatePower(Vars, &count);
		RightSumm = CreatePower(Vars, &count);
		Temp = CreatePower(Vars, &count);
	/*	node* newtop = new node;
		CREATEDATA(newtop);*/
		NODECTOR(newtop, "+", T_op, LeftSumm, RightSumm);

		newtop = CreateTreatSumm(newtop, Temp, Vars, &count, CountofVars);
	}
	node* Sqrt = new node;
	CREATEDATA(Sqrt);
	node* degree = new node;
	CREATEDATA(degree);
	NODECTOR(degree, "0.5", T_num, NULL, NULL);
	NODECTOR(Sqrt, "^", T_op, newtop, degree);
	return Sqrt;
}
	/*NODECTOR(leftVar, ftoa(Vars[0].sigma), T_num, NULL, NULL);
	NODECTOR(rightVar, ftoa(Vars[0].value), T_num, NULL, NULL);
	NODECTOR(Div, "/", T_op, leftVar, rightVar);
	NODECTOR(Power, "^", T_op, Div, Two);
	CopyTree(RightSumm, Power);*/



	//NODECTOR(leftVar, ftoa(Vars[1].sigma), T_num, NULL, NULL);
	//NODECTOR(rightVar, ftoa(Vars[1].value), T_num, NULL, NULL);
	//NODECTOR(Div, "/", T_op, leftVar, rightVar);
	//NODECTOR(Power, "^", T_op, Div, Two);
	//CopyTree(LeftSumm, Power);

	//NODECTOR(leftVar, ftoa(Vars[2].sigma), T_num, NULL, NULL);
	//NODECTOR(rightVar, ftoa(Vars[2].value), T_num, NULL, NULL);
	//NODECTOR(Div, "/", T_op, leftVar, rightVar);
	//NODECTOR(Power, "^", T_op, Div, Two);
	//CopyTree(Temp, Power);
	

	//CopyTree(LeftSumm, Power);
	//for (int i = 1; i < CountofVars; i++)
	//{
	//	/*NODECTOR(leftVar,  ftoa(Vars[i].sigma), T_num, NULL, NULL);
	//	NODECTOR(rightVar, ftoa(Vars[i].value), T_num, NULL, NULL);
	//	NODECTOR(Div, "/", T_op, leftVar, rightVar);
	//	NODECTOR(Power, "^", T_op, Div, Two);
	//	CopyTree(RightSumm, Power);
	//	NODECTOR(Summ, "+", T_op, LeftSumm, RightSumm);*/

	//	node* temp = new node;
	//	//temp->left  = (node*)malloc(sizeof(node));
	//	//temp->right = (node*)malloc(sizeof(node));
	//	CREATEDATA(temp);
	//	CopyTree(temp, Summ);

	//	CopyTree(LeftSumm, temp);


	//}
	


node* CreateTreatSumm(node* Left, node* Right, variable* Vars, int* count, int Numb)
{
	node* newtop = new node;
	CREATEDATA(newtop);
	NODECTOR(newtop, "+", T_op, Left, Right);

	if (*count < Numb)
	{
		node* Temp = new node;
		CREATEDATA(Temp);

		Temp = CreatePower(Vars, count);

		newtop = CreateTreatSumm(newtop, Temp, Vars, count, Numb);
	}
	return newtop;
	
}

node* CreatePower(variable* Vars, int* count)
{
	node* leftVar = new node;
	node* Temp = new node;
	node* rightVar = new node;
	node* Div = new node;
	node* Power = new node;
	node* Two = new node;
	CREATEDATA(Two);
	CREATEDATA(Temp);
	CREATEDATA(Power);
	CREATEDATA(Div);
	CREATEDATA(leftVar);
	CREATEDATA(rightVar);
	NODECTOR(Two, "2", T_num, NULL, NULL);

	NODECTOR(leftVar, ftoa(Vars[*count].sigma), T_num, NULL, NULL);
	NODECTOR(rightVar, ftoa(Vars[*count].value), T_num, NULL, NULL);
	NODECTOR(Div, "/", T_op, leftVar, rightVar);
	NODECTOR(Power, "^", T_op, Div, Two);
	CopyTree(Temp, Power);
	(*count)++;

	return Temp;

}

void FindVariables(node* tree, int* count, variable* Vars)
{
	int wasFound = 0;
	if (tree->type == T_var)
	{
		for (int i = 0; i < *count; i++)
		if (IS(tree->data,Vars[i].data))
		{
			wasFound = 1;
			Vars[i].count++;
			if (tree->left) FindVariables(tree->left, count, Vars);
			if (tree->right) FindVariables(tree->right, count, Vars);
		}
		if (!wasFound)
		{
			Vars[*count].data = new char[LENGTHOFWORD]{0};
			//memset(Vars[*count].data, 0, LENGTHOFWORD);
			//Vars[*count].data = (char*)calloc(LENGTHOFWORD, sizeof(char));
			Vars[*count].count = 1;
			int len = strlen(tree->data);
			strcpy(Vars[*count].data, tree->data);
			Vars[(*count)++].data[len] = '\0';
		}
	}
	if (tree->left) FindVariables(tree->left, count, Vars);
	if (tree->right) FindVariables(tree->right, count, Vars);
}

int ÑreateTeXFile(FILE *fout)
{
	fprintf(fout, "\documentclass[12pt,a4paper]{scrartcl}"
		"\\usepackage[utf8]{inputenc}"
		"\\usepackage[english, russian]{babel}"
		"\\usepackage{ indentfirst }"
		"\\usepackage{ misccorr }"
		"\\usepackage{ graphicx }"
		"	\\usepackage{ amsmath }");
	return OK;
}
/*VERIFICATOR*/

//int TreeVerificator(node* top)
//{
//	if (top == NULL) return 0;
//
//	if ()
//
//	if (top->left  != NULL) TreeVerificator(top->left);
//	if (top->right != NULL) TreeVerificator(top->right;
//
//}

int PrintTree(node* top, int* count)
{
	if (top == NULL) return 0;

	for (int i = 0; i < *count; i++)
		printf("----");
	if (top->type != T_num)
		printf("<%s>(%d) \n", TD, top->type);
	else printf("<%.3f>(%d) \n", atof(TD), top->type);

	if (top->left  != NULL){ (*count)++; PrintTree(top->left,  count); }
	if (top->right != NULL){ (*count)++; PrintTree(top->right, count); }
	(*count)--;

	return OK;
}

int Print(node* top, FILE* fout)
{
	if (top->type == T_func) 
	{ 
		fprintf(fout, "%s", top->data);
		fprintf(fout, "(");
		if (top->right) Print(top->right, fout);
		else Print(top->left, fout);
		fprintf(fout, ")");
	}
	else
	{
		if (top->left) { fprintf(fout, "("); Print(top->left, fout); }
		fprintf(fout, "%s", top->data);
		if (top->right) { Print(top->right, fout); fprintf(fout, ")"); }
	}

	return OK;
}

node* GetG0(const char* buffer)
{
	s = buffer;
	node* top = GetE();
	int count = 0;
	//int val = PrintTree(top, &count);
	if (*s == NULL) return top;
	else return NULL;
}

node *GetE()
{
	node* top = new node;
	node* leaf2 = new node;
	node* leaf = GetT();
	if (!leaf) return NULL;
	char op = 0;
	while (*s == '+' || *s == '-')
	{
		top = new node;
		op = *s++;
		leaf2 = GetT();
		if (!leaf2) return NULL;
		CREATEDATA(top);
		top->data[1] = '\0';
		MAKENODE(T_op);

	}
	return leaf;
}

node* GetN()
{
	node* leaf = new node;
	int count = 0;
	char* val = (char*)calloc(SIZEOFNUMBER, sizeof(char));
	while (*s >= '0' && *s <= '9' || *s == '.' || *s == '-')
	{
		val[count++] =*s;
		*s++;
	}
	(char*)leaf->data = (char*)calloc(count + 1, sizeof(char));
	strcpy(leaf->data, val);
	//ftoa(val, leaf->data, Radix);
	leaf->data[count] = '\0';
	leaf->type = T_num;
	return leaf;
}

node *GetT()
{
	node* top = new node;
	node* leaf2 = new node;
	node* leaf = GetS();
	if (!leaf) return NULL;
	int op = 0;
	while (*s == '/' || *s == '*')
	{
		top = new node;
		op = *s++;
		leaf2 = GetS();
		if (!leaf2) return NULL;
		CREATEDATA(top);
		top->data[1] = '\0';
		MAKENODE(T_op);
	}
	return leaf;
}

node *GetS()
{
	node* top = new node;
	node* leaf2 = new node;
	node* leaf = GetP();
	if (!leaf) return NULL;
	int op = 0;
	if (*s == '^')
	{
		top = new node;
		op = *s++;
		leaf2 = GetP();
		if (!leaf2) return NULL;
		CREATEDATA(top);
		top->data[1] = '\0';
		MAKENODE(T_op);
	}
	return leaf;
}

node *GetP()
{
	node* val = {};
	if (*s == '(')
	{
		s++;
		node* leaf = GetE();
		if (*s == ')') { s++; return leaf; }
		else return NULL;
	}
	else
	{
		val = GetN();
		if (atof(val->data) == NULL) return GetVar();
		else return val;
	}
}

node* GetVar()
{
	node* leaf = new node;
	char val[LENGTHOFWORD] = "";
	int count = 0;
	while (*s >= 'a' && *s <= 'z')
	{
		val[count++] = *s;
		*s++;
	}
	if (IsFunc(val)) 
		return GetFunc(val);
	(char*)leaf->data = (char*)calloc(count + 1, sizeof(char));
	leaf->data[count] = '\0';
	strcpy(leaf->data, val);
	leaf->type = T_var;

	return leaf;
}

node* GetFunc(char* val)
{
	node* top = new node;
	node* leaf = GetP();
	if (!leaf) return NULL;

	CREATEDATA(top);
	NODECTOR(top, val, T_func, leaf, NULL);
	return top;
}

int IsFunc(char* val)
{
	if (IS("sin", val)) return OK;
	else if (IS("cos", val)) return OK;
	else if (IS("tg" , val)) return OK;
	else if (IS("ctg", val)) return OK;
	else if (IS("ln" , val)) return OK;
	else return 0;
}

node* Derivation(node* top)
{
	switch (top->type)
	{
	case T_num: TD = "0"; return top; break;
	case T_var: TD = "1"; top->type = T_num; return top; break;
	case T_op:
		if (IS(TD, "-")|| IS(TD, "+"))
		{
			top->left = Derivation(top->left);
			top->right = Derivation(top->right);
			return top;
		}
		else if (IS(TD, "*"))
		{
			DER_MUL;

			node* newTop = new node;
			NODECTOR(newTop, "+", T_op, LeftMul, RightMul);

			return newTop;
		}
		else if (IS(TD, "/"))
		{
			DER_MUL;

			node* newTopL = new node;
			NODECTOR(newTopL, "-", T_op, LeftMul, RightMul);

			node* newTopR = new node;
			NODECTOR(newTopR, "*", T_op, newRight, newRight);

			node* newTop = new node;
			NODECTOR(newTop, "/", T_op, newTopL, newTopR);

			return newTop;
		}
		else if (IS(TD, "^"))
		{
			if (RT == T_num)
			{
				node* leftRightPow = new node;
				NODECTOR(leftRightPow, RD, T_num, NULL, NULL);

				node* LeftPow = new node;
				NODECTOR(LeftPow, "*", T_op, top->left, leftRightPow);

				RD = FTOA(RD, "1", -);

				NODECTOR(top, "^", T_op, LeftPow, top->right);

				return top;
			}
		}
		break;
	case T_func:
		if (IS(TD, "sin"))
		{
			node* newtop = new node;

			CREATEDATA(newtop);
			strcpy(newtop->data, "*");

			newtop->left = (node*)malloc(sizeof(node));
			newtop->right = (node*)malloc(sizeof(node));
			CopyTree(newtop->right, top->left);
			CopyTree(newtop->left, top);

			strcpy(newtop->left->data, "cos");

			newtop->right = Derivation(newtop->right);
			DestroyTree(top);

			return newtop;
		}
		if (IS(TD, "cos"))
		{

			node* newtop = new node;

			CREATEDATA(newtop);
			strcpy(newtop->data,"*");
			newtop->type = T_op;
			newtop->left = (node*)malloc(sizeof(node));
			newtop->right = (node*)malloc(sizeof(node));
			CopyTree(newtop->right, top->left);
			CopyTree(newtop->left, top);

			strcpy(newtop->left->data, "sin");

			newtop->right = Derivation(newtop->right);
			DestroyTree(top);

			return newtop;
		}
		if (IS(TD, "ln"))
		{
			node* newtop = new node;

			CREATEDATA(newtop);
			strcpy(newtop->data, "/");
			newtop->type = T_op;
			newtop->left = (node*)malloc(sizeof(node));
			newtop->right = (node*)malloc(sizeof(node));
			CopyTree(newtop->left, top->left);
			CopyTree(newtop->right, top->left);

			newtop->left = Derivation(newtop->left);
			DestroyTree(top);

			return newtop;
		}
		if (IS(TD, "tg"))
		{
			strcpy(top->data, "cos");
			node* newtop = new node;
			CREATEDATA(newtop);

			strcpy(newtop->data, "/");
			newtop->type = T_op;
			newtop->left = (node*)malloc(sizeof(node));
			newtop->right = (node*)malloc(sizeof(node));
			CopyTree(newtop->left, top->left);
			//CopyTree(newtop->right, top->left);

			node* newRight = new node;
			CREATEDATA(newRight);
			strcpy(newRight->data, "^");
			newRight->type = T_op;
			newRight->left = (node*)malloc(sizeof(node));
			newRight->right = (node*)malloc(sizeof(node));
			CopyTree(newRight->left, top);
			CREATEDATA(newRight->right);
			NODECTOR(newRight->right, "2", T_num, NULL, NULL);
			//strcpy(newRight->right->data, "2");

			newtop->right = newRight;

			newtop->left = Derivation(newtop->left);
			DestroyTree(top);

			return newtop;
		}
	default: return top;
	}

}

void DestroyTree(node* vert)
{
	delete[]vert->data;
	vert->type = NULL;
	while (vert->left)  { 
		DestroyTree(vert->left);	
		vert->left  = NULL; 
	}
	while (vert->right) { 
		DestroyTree(vert->right);	
		vert->right = NULL;
	}
	vert = NULL;
}

void CopyTree(node* dest, node* source)
{
	//dest = (node*)malloc(sizeof(node));
	CREATEDATA(dest);
	strcpy(dest->data, source->data);
	dest->type = source->type;
	dest->left = NULL;
	dest->right = NULL;
	if (source->left != NULL && source->left->data != NULL)
	{
		dest->left = (node*)malloc(sizeof(node));
		CopyTree(dest->left, source->left);
	}
	if (source->right != NULL && source->left->data != NULL)
	{
		dest->right = (node*)malloc(sizeof(node));
		CopyTree(dest->right, source->right);
	}
}

node* Cleaning(node* top, int* WasCleaned)
{
	if (top != NULL)
	{
		switch (top->type)
		{
		case T_op:
			if (IS(TD, "+")|| IS(TD, "-"))
			{
				//deleting NULL in add or sub
				if (IS(TD, "+") && IS(LD, "0") && !IS(RD, "0"))
				{
					top = top->right;
					*WasCleaned = 1;
				}
				else if (IS(RD, "0")&& !IS(LD, "0"))
				{
					top = top->left;
					*WasCleaned = 1;
				}
				else if (IS(TD, "-") && IS(RD, "0"))
				{
					top = top->left;
					*WasCleaned = 1;
				}
				// constant folding
				else if (TL && TR && LT == T_num && RT == T_num)
				{
					top->type = T_num;
					if (IS(TD, "+"))
					{
						top->data = new char[LENGTHOFWORD];
						FTOA(LD, RD, +);
					}
					else {
						top->data = new char[LENGTHOFWORD];
						FTOA(LD, RD, -); 
					}
					top->left = NULL;
					top->right = NULL;
					*WasCleaned = 1;
				}
			}
			else if (IS(TD, "*"))
			{	
				//deleting NULL in multi
				if (IS(LD, "0") || IS(RD, "0"))
				{
					NODECTOR(top, "0", T_num, NULL, NULL);
					*WasCleaned = 1;
				}
				//deleting multing in 1
				else if (IS(LD, "1") && !IS(RD, "1"))
				{
					top = top->right;
					*WasCleaned = 1;
				}
				else if (!IS(LD, "1") && IS(RD, "1"))
				{
					top = top->left;
					*WasCleaned = 1;
				}

				// constant folding
				else if (LT == T_num && RT == T_num)
				{
					double tmp = atof(LD) * atof(RD);
					char* newData = ftoa(tmp);
					NODECTOR(top, newData, T_num, NULL, NULL);
					*WasCleaned = 1;
				}
			}
			else if (IS(TD, "/"))
			{
				if (IS(LD, "0"))
				{
					NODECTOR(top, "0", T_num, NULL, NULL);
					*WasCleaned = 1;
				}
				else if (LT == T_num && RT == T_num)
				{
					double tmp = atof(LD) / atof(RD);
					char* newData = ftoa(tmp);
					/*top->data = new char[LENGTHOFWORD];
					top->data = FTOA(LD, RD, / );*/
					NODECTOR(top, newData, T_num, NULL, NULL);
					*WasCleaned = 1;
				}
				else if (IS(RD, "1"))
				{
					top = top->left;
					*WasCleaned = 1;
				}
			}
			else if (IS(TD, "^"))
			{
				if (LT == T_num && RT == T_num)
				{
					double tmp = pow(atof(LD), atof(RD));
					char* newData = ftoa(tmp);
					NODECTOR(top, newData, T_num, NULL, NULL);
					*WasCleaned = 1;
				}
				else if (LT != T_num && abs(atof(RD) - 1)<EPS)
				{
					top = top->left;
					*WasCleaned = 1;
				}
				else if (RT != T_num && abs(atof(LD) - 1)<EPS)
				{
					NODECTOR(top, "1", T_num, NULL, NULL);
					*WasCleaned = 1;
				}

			}
			top->left = Cleaning(top->left, WasCleaned);
			top->right = Cleaning(top->right, WasCleaned);
		}
		top->left = Cleaning(top->left, WasCleaned);
		top->right = Cleaning(top->right, WasCleaned);
	}
	return top;
}
