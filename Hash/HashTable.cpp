// HashTable.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <cassert>
#include <cstring>
#include "list_t.h"
#include "F_work.h"
#include <iostream>


typedef int (*func)(const char*) ;

const int SIZEOFTABLE = 10;
const int SIZEOFFILENAME = 20;
const unsigned int FNV_PRIME = 115249;
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
char* takeWord(const char* buffer, int* i, char* tmpStr);
int PrintHash(const char* fileout, int* CountOfHashing);

int _tmain(int argc, _TCHAR* argv[])
{
	//List* list1 = new List[SIZEOFTABLE];
	//List* list1 = (List*)calloc(SIZEOFTABLE,sizeof(*list1));
	const char* buffer = ReadFile(argv[1]);
	const char* word = {};
	int* CountOfHahing = (int*)calloc(SIZEOFTABLE, sizeof(CountOfHahing));
	
	const char* fileout = "hash_out.csv";
	FILE *file = NULL;
	errno_t err = fopen_s(&file, fileout, "w");
	fclose(file);
	/*printf("Enter name of output file\n>");
	scanf_s("%s\n", &fileout);*/
	List* table = new List[SIZEOFTABLE];
#define HASHING(num)															\
	if (!(hashing(buffer, CountOfHahing, hash##num))) Nerror = HASHERR;	\
	if (!(PrintHash(fileout, CountOfHahing))) Nerror = FILEERR;					

		HASHING(0);
 		HASHING(1);
		HASHING(2);
		HASHING(3);
		HASHING(4);
		HASHING(5);

#undef HASHING

		/*if (!(hashing(buffer, CountOfHahing, table, hash0))) Nerror = HASHERR;
		if (!(PrintHash(fileout, CountOfHahing))) Nerror = FILEERR;*/
	
	system("start hash_out.csv");
	List* list1 = new List;
	//List* list1 = (List*)calloc(1, sizeof(list1));
	//assert(list1.head || list1.tail);

	/*table[0].addTail(200);
	table[0].addTail(300);
	table[1].addTail(100);*/

	/*list1->show();
	list1->addTail(100);
	list1->addTail(200);
	list1->addTail(300);
	list1->addHead(500);

	list1->show();
	printf("---------------------\n");
	list1->delet(1);
	list1->show();
	printf("---------------------\n");
	list1->show(1);*/
	//table[1].show();
	delete list1;
	delete[]table;
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

int hashing(const char* buffer, int* CountOfHashing, func f)
{

	int i = 0, k = 0, j = 0;
	unsigned int hash = 0;
	char tmpStr[SIZEOFWORD] = "";
	int Firstly = 0;
	List* table = new List[SIZEOFTABLE];
	//printf("----------------------\n");
	while (buffer[j] != '\0' && buffer[j] > 0)
	{
		if (!(takeWord(buffer, &j, tmpStr))) Nerror = PTRERR;

		hash = f(tmpStr) % SIZEOFTABLE;
		hash = hash % SIZEOFTABLE;
		//printf("hash = %d \n", hash);//debug
		if (!(table[hash].addTail(tmpStr))) goto breakpoint;
		//table[hash].show();//debug
		CountOfHashing[hash]++;
		memset(tmpStr, '\0', SIZEOFTABLE);

		while (buffer[j] == ' ' || buffer[j] == '\r' || buffer[j] == '\n')
			j++;
	}

	char* ShowFind = "wei";
	ShowElem(table[f(ShowFind) % SIZEOFTABLE].Find(ShowFind));
	return OK;
breakpoint:
	return BAD;
}

int ShowElem(node* Elem)
{
	assert(Elem);

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
		HashVal *= FNV_PRIME;
		HashVal ^= (unsigned int)word[i];
		HashVal = (HashVal >> 1) | (HashVal << 31);
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
