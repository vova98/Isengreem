// HashTable.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <cassert>
#include <cstring>
#include "list_t.h"
#include "F_work.h"
#include <iostream>


typedef int (*func)(const char*) ;

struct Table
{
	List* list;
	func f;

};

const int SIZEOFTABLE = 20;
const int SIZEOFFILENAME = 20;
const unsigned int FNV_PRIME = 115249;
const unsigned int MAXINT = (pow(2, sizeof(unsigned int)* 8.0) - 1)/FNV_PRIME;
//stupid
int hash0(const char* word);
//first symbol
int hash1(const char* word);
//length
int hash2(const char* word);
//sum ascii
int hash3(const char* word);
//sum ascii div length
int hash4(const char* word);
//FNV
int hash5(const char* word);

int hashing(const char*, int(*hash1)(const char*), const char*);
int hashing(const char* buffer, int* CountOfHashing, func f);
int hash1(const char* word);

void clearList(List list);
int ShowElem(node* Elem);
int addToTable(Table* table, const char* tmpStr, int* CountOfHashing);
node* FindElem(Table* table, const char* tmpStr);
char* takeWord(const char* buffer, int* i, char* tmpStr);
int PrintHash(const char* fileout, int* CountOfHashing);



int _tmain(int argc, _TCHAR* argv[])
{

	const char* buffer = ReadFile(argv[1]);
	const char* word = {};
	int* CountOfHahing = (int*)calloc(SIZEOFTABLE, sizeof(CountOfHahing));
	
	const char* fileout = "hash_out.csv";
	FILE *file = NULL;
	errno_t err = fopen_s(&file, fileout, "w");
	fclose(file);

	//Table* table = new Table[SIZEOFTABLE];

#define HASHING(num)												\
	if (!(hashing(buffer, CountOfHahing, hash##num)))				\
	{																\
		Nerror = HASHERR;											\
		PrintError(__LINE__);										\
		system("start LOG.txt");									\
		return 0;													\
	}																\
	if (!(PrintHash(fileout, CountOfHahing))) Nerror = FILEERR;					

		HASHING(0);
 		HASHING(1);
		HASHING(2);
		HASHING(3);
		HASHING(4);
		HASHING(5);

#undef HASHING
	
	system("start hash_out.csv");
	//List* list1 = new List;
	//delete list1;
	//delete[]table;
	return 0;
}

int PrintHash(const char* fileout, int* CountOfHashing)
{
	FILE *file = NULL;
	errno_t err = fopen_s(&file, fileout, "a");

	//int count[SIZEOFTABLE] = {};
	for (int i = 0; i < SIZEOFTABLE; i++)
		fprintf(file, "%d; ", CountOfHashing[i]);
	fprintf(file, "\n");

	for (int i = 0; i < SIZEOFTABLE; i++)
		CountOfHashing[i] = 0;
	//memset(CountOfHashing, 0, SIZEOFTABLE);
	fclose(file);
	return OK;
}

int hashing(const char* buffer, int* CountOfHashing, func hashFunc)
{

	int i = 0, k = 0, j = 0;
	unsigned int hash = 0;
	char tmpStr[SIZEOFWORD] = "";
	int Firstly = 0;
	Table* table = new Table;
	List* Listy = new List[SIZEOFTABLE];
	table->f = hashFunc;
	table->list = Listy;
	//printf("----------------------\n");
	while (buffer[j] != '\0' && buffer[j] > 0)
	{
		if (!(takeWord(buffer, &j, tmpStr))) { Nerror = PTRERR; PrintError(__LINE__); }
		
		addToTable(table, tmpStr, CountOfHashing);

		//hash = f(tmpStr) % SIZEOFTABLE;
		//hash = hash % SIZEOFTABLE;
		//printf("hash = %d \n", hash);//debug
		//if (!(table->list[hash].addTail(tmpStr))) return BAD;// goto breakpoint;
		//table[hash].show();//debug
		
		memset(tmpStr, '\0', SIZEOFTABLE);

		while (buffer[j] == ' ' || buffer[j] == '\r' || buffer[j] == '\n')
			j++;
		tmpStr[0] = '\0';
	}
	
	char* ShowFind = "wei";
	if (!ShowElem(FindElem(table, ShowFind)))
		return BAD;// goto breakpoint;
	
	return OK;
//breakpoint:
}

int addToTable(Table* table, const char* tmpStr, int* CountOfHashing)
{
	int hash = table->f(tmpStr) % SIZEOFTABLE;
	hash = hash % SIZEOFTABLE;
	if (!(table->list[hash].addTail((char*)tmpStr))) return BAD;
	CountOfHashing[hash]++;
	return OK;
}

node* FindElem(Table* table, const char* tmpStr)
{
	int index = table->f(tmpStr) % SIZEOFTABLE;
	node* node = table->list[index].Find((char*)tmpStr);
	if (node == NULL)
		return BAD;
	return node;
}

int ShowElem(node* Elem)
{
	if (Elem == NULL) return BAD;// assert(Elem);

	printf("value = <%s> \n"
		"   curr - <%d> \n"
		"   next - <%d> \n"
		"   prev - <%d> \n\n", Elem->val, Elem, Elem->next, Elem->prev);

	return OK;
}

void clearList(List list)
{
	if (list.head == NULL) Nerror = PTRERR;
	while (list.head->next)
	{
		//list.tail = list.head->next;
		memset(list.tail->val,'\0', SIZEOFWORD);
		list.tail->next = NULL;
		//delete list->head;
		list.tail = list.tail->prev;
		//list.show();
	}
	memset(list.head->val, '\0', SIZEOFWORD);
}

int hash0(const char* word)
{
	return 0;
}

int hash1(const char* word)
{
	return (int)word[0];
}

int hash2(const char* word)
{
	return strlen(word);
}

int hash3(const char* word)
{
	int i = 0, sum = 0;
	if (word[0] != '\0')
	while (word[i++] != '\0') sum += (int)word[i];
	return sum;
}

int hash4(const char* word)
{
	int i = 0, sum = 0;
	if (word[0] != '\0')
	while (word[i++] != '\0') sum += (int)word[i];
	return sum/strlen(word);
}

int hash5(const char* word)
{
	unsigned int HashVal = hash3(word);
	int WordLen = strlen(word);
	for (int i = 0; i < WordLen; i++)
	{

		if (HashVal < MAXINT)
			HashVal *= FNV_PRIME;
		HashVal ^= (unsigned int)word[i];
	}
	return HashVal;
}

char* takeWord(const char* buffer, int* j, char* tmpStr)
{
	int k = 0;
	
	while (buffer[*j] != ' ' && buffer[*j] > 0)
	{
		while (IsPunct((char*)buffer, *j))
		(*j)++;
		tmpStr[k++] = buffer[(*j)++];
	}
	
	strstr(buffer, " ");
	return tmpStr;
}
