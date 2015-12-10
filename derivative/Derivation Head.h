
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

//Checking is word - function
int IsFunc(char* val);
#include "TreeBuilder.h"

//Print text in TeX file
int PrintInTex(node* top, FILE* );

//Print Tree in console
int PrintTree(node* top, int* count);

//Print Tree in file
int Print(node* top, FILE* fout);

//Creating TeX file 
int ÑreateTeXFile(FILE *fout);

//Destroying Tree
void DestroyTree(node* vert);

//Cleaning Tree(constant folding, mulling Null...)
node* Cleaning(node* top, int* WasCleaned);

//Find all variables in Tree
void FindVariables(node* tree, int* count, variable* Vars);

//Creating Tree for total derivicator
node* CreateTotalDer(variable* Vars, int CountofVars);

//Creating Summ vertex for Total derivcator
node* CreateTreatSumm(node* Left, node* Right, variable* Vars, int* count, int Numb);

//Copying Tree from source to dest
void CopyTree(node* dest, node* source);

//Create Power from array Vars
node* CreatePower(variable* Vars, int* count);

//Create Derivation Tree
node* Derivation(node* top);

