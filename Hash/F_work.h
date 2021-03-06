#include <cstring>
#include <stdlib.h>

const char* wtoc(const wchar_t* w_string);
void PrintError(int line);
int Nerror = 0;

enum ErrorNum { NOFILE = 1, MEMERR, FILEERR, BUCELL, PTRERR, HASHERR };

char* ReadFile(_TCHAR* argv)
{
	//const char* argv1 = "hash_works.txt";
	FILE *filein = NULL;
	errno_t err = fopen_s(&filein, wtoc(argv), "rb");
	//errno_t err = fopen_s(&filein, argv1, "rb");

	if (filein != NULL)
	{
		fseek(filein, 0, SEEK_END);
		size_t Textlen = ftell(filein);
		if (!(Textlen)) perror("Ftell Error");
		rewind(filein);

		char *buffer = new char[Textlen + 1];
		//assert(buffer);
		if (buffer == NULL)
			Nerror = MEMERR;
		PrintError(__LINE__);

		fread((char*)buffer, Textlen, sizeof(*buffer), filein);
		if (buffer == 0) Nerror = FILEERR;
		PrintError(__LINE__);

		if (fclose(filein) == -1) perror("Error with closing file\n");
		fclose(filein);
		return buffer;
	}
	else
		Nerror = NOFILE;
	PrintError(__LINE__);
	return "-1";

}

void PrintError(int line)
{
	FILE* ferr = NULL;
	errno_t err = fopen_s(&ferr, "LOG.txt", "a");

	if (Nerror != 0)
	{
		fprintf(ferr,"Time, %s \n"
			"On <%d> line you have such trouble:\n", __TIME__, line);
		switch (Nerror)
		{
		case 1: fprintf(ferr,"No input file. Try again.\n"); break;
		case 2: fprintf(ferr,"Problems with memmory alloc.\n"); break;
		case 3: fprintf(ferr,"Problems with opening file.\n"); break;
		case 4: fprintf(ferr,"Too much same markers.\n"); break;
		case 5: fprintf(ferr,"Error with pointers, check transfer.\n"); break;
		case 6: fprintf(ferr, "Problems in hash-function.\n"); break;
		default:
			break;
		}
	}
	fclose(ferr);
}

const char* wtoc(const wchar_t* w_string)
{
	const char* argvName = (char*)calloc(wcslen(w_string), sizeof(argvName));
	size_t len = wcstombs((char*)argvName, w_string, wcslen(w_string));
	return argvName;
}

int IsPunct(char* string, int numb)
{
	assert(string[numb]);
	if (string[numb])
		Nerror = PTRERR;
	return (unsigned int)string[numb] > 0 && (unsigned int)string[numb] < 48 || (unsigned int)string[numb] > 57 && (unsigned int)string[numb] < 64 ||
		(unsigned int)string[numb] == '�' || (unsigned int)string[numb] == '�' || (unsigned int)string[numb] == '\r' || (unsigned int)string[numb] == '\n' ? 1 : 0;
	PrintError(Nerror);
}