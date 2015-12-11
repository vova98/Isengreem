#include <cstring>
#include <stdlib.h>

const char* wtoc(const wchar_t* w_string);
void PrintError(int line);
int Nerror = 0;
const int SIZEOFNUMBER = 10;
const double EPSIL = 0.001;

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

		buffer[Textlen] = '\0';

		if (fclose(filein) == -1) perror("Error with closing file\n");
		fclose(filein);
		return buffer;
	}
	else
		//fclose(filein);
		Nerror = NOFILE;
	PrintError(__LINE__);
	return NULL;

}

char* PrintFile(char* buffer, _TCHAR* argv)
{
	FILE *fileout = NULL;
	errno_t err = fopen_s(&fileout, wtoc(argv), "a");

	if (buffer == NULL)
		Nerror = MEMERR;
	PrintError(__LINE__);

	if (fileout != NULL)
	{
		size_t Textlen = strlen(buffer);
		fwrite((char*)buffer, Textlen, sizeof(*buffer), fileout);
		if (buffer == 0) Nerror = FILEERR;
		PrintError(__LINE__);
		return buffer;
	}
	else
		Nerror = NOFILE;
	PrintError(__LINE__);
	return "-1";
}


void PrintError(int line)
{
	if (Nerror != 0)
	{
		printf("On <%d> line you have such trouble:\n", line);
		switch (Nerror)
		{
		case 1: printf("No input file. Try again.\n"); break;
		case 2: printf("Problems with memmory alloc.\n"); break;
		case 3: printf("Problems with opening file.\n"); break;
		case 4: printf("Too much same markers.\n"); break;
		case 5: printf("Error with pointers, check transfer.\n"); break;
		default:
			break;
		}
	}
}



char* ftoa(double num)
{
	int len = 0, taillen = 0, tmp = 0, c = 0;
	double tail = 0;
	if (abs(num - round(num) < EPSIL)) num > 0? num += EPSIL: num -=EPSIL;
	num = round(num * 1000) / 1000;
	char* word = (char*)calloc(SIZEOFNUMBER, sizeof(char));
	tmp = int(num);
	itoa(tmp, word, 10);
	len = strlen(word);
	if (num > -1 && num < 0)
	{
		for (int i = len - 1; i >= 0; i--)
			word[i + 1] = word[i];
		word[0] = '-';
		len++;
	}
	tail = num - tmp;
	tail *= 10;
	if (tail < 0) tail *= -1;
	c = int(tail);
	//if (c == 0)return word;
	//else
	word[len++] = '.';
	tail -= c;
	while (c >= 0 && taillen < 4)
	{
		word[len++] = c + '0';
		tail *= 10;
		c = round(tail);
		tail -= c;
		taillen++;
	}
	return word;

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
		(unsigned int)string[numb] == '«' || (unsigned int)string[numb] == '»' || (unsigned int)string[numb] == '\r' || (unsigned int)string[numb] == '\n' ? 1 : 0;
	PrintError(Nerror);
}