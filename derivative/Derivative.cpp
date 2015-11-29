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
	node() :data{}, type{}, left(NULL), right(NULL){}
};

enum Types { T_var = 1, T_op = 2, T_num = 3, T_func = 4 };

const char *s = NULL;
const int LENGTHOFWORD = 5;
const double EPS = 0.001;
const int Radix = 10;
//node* NodeCtor(int type, const char op, node* left, node* right);
node* GetG0(const char* buffer);
int PrintTree(node* top, int* count);
int Print(node* top, FILE* fout);
int ÑreateTeXFile(FILE *fout);
int IsFunc(char* val);
node* Cleaning(node* top, int* WasCleaned);
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


	node* Tree = GetG0(buffer);
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
	return 0;
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
			int count = 0;
			strcpy(top->data, "cos");
			
			node* left = new node;
			node* right = new node;
			NODECTOR(right, LD, T_op, TL->left, TL->right);		
			NODECTOR(left, TD, T_func, top->left, right);		
			node* RightDer = Derivation(top->left);
			
			node* top = new node;
			NODECTOR(top, "*", T_op, left, RightDer);
			
			TL->left = NULL;
			return top;
		}
		if (IS(TD, "cos"))
		{
			strcpy(top->data, "sin");
			node* left = new node;
			node* right = new node;
			NODECTOR(right, LD, T_op, TL->left, TL->right);

			NODECTOR(left, TD, T_func, top->left, right);
			node* RightDer = Derivation(top->left);

			node* NewLeft = new node;
			CREATEDATA(NewLeft);
			NODECTOR(NewLeft, "-", T_op, NULL, left);

			node* top = new node;
			NODECTOR(top, "*", T_op, NewLeft, RightDer);
			TL->right->left = NULL;
			return top;
		}
	default: return top;
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
					top->data = new char[LENGTHOFWORD];
					top->data = FTOA(LD, RD, *);
					NODECTOR(top, top->data, T_num, NULL, NULL);
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
					top->data = new char[LENGTHOFWORD];
					top->data = FTOA(LD, RD, / );
					NODECTOR(top, top->data, T_num, NULL, NULL);
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
					float tmp = pow(atof(LD), atof(RD));
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
