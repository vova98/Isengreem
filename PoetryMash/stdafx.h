#pragma once
#define NDEBUG
#define Ok 1

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <cstdlib>
#include <errno.h>
#include <iostream>
#include <locale>
#include <cassert>

/**
* \fn void printStr(FILE* fout, char* string);
* \brief Print string function.
* \param [in,out] fout file, where string will be print
* \param [in] string string which will be print
*/
void printStr(FILE* fout, char* string);

/**
*@ \n  brief Main part of application.
* Function create array of pointer and read text from file.
*@ \n  param [in,out] StringCount Count of strings in text.
*@ \n  param [in,out] Textlen Count of all symbols in text.
*@ \n  return All of input parameters and array of pointers.
*/
char** InitText(int* StringCount, size_t* Textlen);

/**
*@ \n  brief Sorting function for one of the hallmarks.
* Function will sort array of pointer start to compare from the begin or from the end.
*@ \n  param [in,out] text Array of pointer.
*@ \n  param [in] key Key use as hallmarks for sorting
*@ \n  param [in] StringCount Count of string
*@ \n  param [in] Textlen Count of text symbols
*@ \n  return Ok if all right 
*/
int sortText(char** text, int key, int *StringCount, size_t Textlen);

/**
*@ \n  brief My little string compare
*@ \n  param [in] string1, string2 String what will be compare
*@ \n  return -1 if string1 > string2, if string1 = string2 - return 0.  
*/
int mlStrcmp(char* string1, char* string2);

/**
*@ \n  brief My little string compare from the string end
*@ \n  param [in] string1, string2 String what will be compare
*@ \n  return -1 if string1 > string2, if string1 = string2 - return 0.
*/
int mlStrcmpEnd(char* string1, char* string2);

/**
*@ \n  brief Swap pointer
*@ \n  param [in,out] first,second Pointers which will be swapped.
*@ \n  return Swapped pointers. 
*/
void swapPtr(char** first, char** second);

/**
*@ \n  breif The liberation of used memory.
*@ \n  return Ok if all right.
*/
int freeMemory(char** text);

/**
*@ \n  breif Function which check the symbol if it punctuation
*@ \n  param [in] string, numb Checking symbol
*@ \n  return -1 if symbol if punctuaion, 0  if it isn't punctuation.
*/
int IsPunct(char* string, int numb);

/**
*@ \n  breif Print text function.
*@ \n  param [in] text Array of pointer with text.
*@ \n  param [in] StringCount Count of strings in text.
*@ \n  param [in] key Hallmarks for sorting and printing
*@ \n  return Ok if all right
*/
int printText(char** text, int StringCount, int key);

/**
*@ \n  breif Function for cutting rubbish
*@ \n  param [in] text Array of pointer with text.
*@ \n  param [in] StringCount Count of strings in text.
*@ \n  param [in] Textlen Count of text symbols.
*@ \n  param [in] key Hallmark for sorting.
*/
void findEnd(char** text, int* StringCount, size_t Textlen, int key);

/*! Count of printing paragrafs*/
const char ParagrafCount = 1;