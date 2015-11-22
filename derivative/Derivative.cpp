// Derivative.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <cassert>
#include "F_work.h"


#define OK 1
#define T_var 1
#define T_op 2
#define T_num 3
#define VAR "variable"
#define OP "operator"
#define NUM "number"

#define MAKENODE(oper)		\
	top->type = oper;		\
	top->left = leaf;		\
	top->right = leaf2;		\
	top->data[0] = op;		\
	leaf = top;				

struct node
{
	char* data;
	int type;
	node* left;
	node* right;
	node() :data{}, type{}, left(NULL), right(NULL){}
};

const char *s = NULL; 
const int LENGTHOFWORD = 5;
const int Radix = 10;
//node* NodeCtor(int type, const char op, node* left, node* right);
int GetG0(const char* buffer);
int PrintTree(node* top, int* count);
node* GetN();
node* GetT();
node* GetE();
node* GetP();
node* GetVar();




//node* NodeCtor(int type, const char op, node* left, node* right)
//{
//	node* top = {};
//	top->type = T_op;
//	top->left = left;
//	top->right = right;
//	top->data = op;
//	return top;
//}

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

/*VERIFICATOR*/

//int TreeVerificator(node* top)
//{
//	if (top == NULL) return 0;
//
//	if ()
//
//	if (top->left != NULL)  TreeVerificator(top->left);
//	if (top->right != NULL) TreeVerificator(top->right;
//
//}

int PrintTree(node* top, int* count)
{
	if (top == NULL) return 0;

		/*printf("value = <%d> \n"
			"   type  - <%d> \n"
			"   curr  - <%d> \n"
			"   left  - <%d> \n"
			"   right - <%d> \n\n", top->data,top->type, top, top->left, top->right);*/

		for (int i = 0; i < *count; i++) 
			printf("----");
		if (top->type != T_num)
			 printf("<%s> \n", top->data);
		else printf("<%d> \n", atoi(top->data));

		if (top->left != NULL) { (*count)++; PrintTree(top->left,  count); }
		if (top->right != NULL){ (*count)++; PrintTree(top->right, count); }
		(*count)--;

	return OK;
}

int GetG0(const char* buffer)
{
	s = buffer;
	node* top = GetE();
	int count = 0;
	int val = PrintTree(top, &count);
	if (*s == NULL) return val;
	else return OK;
}

node *GetE()
{
	node* top = new node;
	node* leaf2 = new node;
	node* leaf = GetT();
	char op = 0;
	while (*s == '+' || *s == '-')
	{
		op = *s++;
		leaf2 = GetT();
		(char*)top->data = (char*)calloc(2, sizeof(char));
		top->data[1] = '\0';
		MAKENODE(T_op);

		/*if (op == '/') val /= val2;
		if (op == '*') val *= val2;*/
	}
	//node* top = NodeCtor(T_op, op, &leaf, &leaf2);
	
	return leaf;
}

node* GetN()
{
	node* leaf = new node;
	int val = 0, count = 0;
	while (*s >= '0' && *s <= '9')
	{

		val = val * 10 + *s - '0';
		*s++;
		count++;
	}
	(char*)leaf->data = (char*)calloc(count+1, sizeof(char));
	itoa(val, leaf->data, Radix);
	leaf->data[count] = '\0';
	leaf->type = T_num;
	return leaf;
}

node *GetT()
{
	node* top = new node;
	node* leaf2 = new node;
	node* leaf = GetP();
	int op = 0;
	while (*s == '/' || *s == '*')
	{
		op = *s++;
		leaf2 = GetP();
		(char*)top->data = (char*)calloc(2, sizeof(char));
		top->data[1] = '\0';
		MAKENODE(T_op);

		/*if (op == '/') val /= val2;
		if (op == '*') val *= val2;*/
	}
	//node* top = NodeCtor(T_op, op, &leaf, &leaf2);

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
	}
	else
	{
		val = GetN();
		if (atoi(val->data) == 0) return GetVar();
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
	(char*)leaf->data = (char*)calloc(count+1, sizeof(char));
	leaf->data[count] = '\0';
	strcpy(leaf->data,val);
	leaf->type = T_var;
	return leaf;
}