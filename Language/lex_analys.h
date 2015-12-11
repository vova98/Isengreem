
const int SIZEOFLIST = 256;
//const int LENGTHOFWORD = 30;

//#define LEXCTOR(rule, type)				\
//while (myIsOper(*buffer))				\
//tmpbuf[i++] = (*buffer)++;				
//lexic[numOfLex].pos = buffer;
//strcpy(lexic[numOfLex].val, tmpbuf);
//lexic[numOfLex].type = T_op;
//numOfLex++;

#define IS(Var, vaL) !strcmp(Var, vaL) 

int myIsOper(char c);
int IsOperator(char c);
int IsOper(char* buf);
int IsTab(char c);

lex* Lexer(char* buffer, int* numOfLex)
{
	//char c = buffer[0];
	lex* lexic = new lex[SIZEOFLIST];
	int i = 0, Num = 0, Len = 0;
	char* tmpbuf = (char*)calloc(LENGTHOFWORD, sizeof(char));
	while (*buffer != '\0')
	{
		//text operator and variables
		if (isalpha(*buffer))
		{	
			lexic[*numOfLex].pos = buffer;
			while (isalpha(*buffer))
				tmpbuf[i++] = *buffer++;
			tmpbuf[i] = '\0';
			if (IsOper(tmpbuf))
			{
				Len = strlen(tmpbuf);
				lexic[*numOfLex].val = (char*)calloc(Len, sizeof(char));
				strcpy(lexic[*numOfLex].val, tmpbuf);
				lexic[*numOfLex].type = T_op;
				(*numOfLex)++;
			}
			else
			{
				//lexic[*numOfLex].pos = buffer;
				lexic[*numOfLex].val = (char*)calloc(Len, sizeof(char));
				strcpy(lexic[*numOfLex].val, tmpbuf);
				lexic[*numOfLex].type = T_var;
				(*numOfLex)++;
			}
				//LEXCTOR()
		}
		//numbers
		else if (isdigit(*buffer))
		{
			lexic[*numOfLex].pos = buffer;
			while (isdigit(*buffer))
				tmpbuf[i++] = *buffer++;
			tmpbuf[i] = '\0';
			lexic[*numOfLex].val = (char*)calloc(Len, sizeof(char));
			strcpy(lexic[*numOfLex].val, tmpbuf);
			lexic[*numOfLex].type = T_num;
			(*numOfLex)++;
		}
		//operator nontext arithm
		else if (myIsOper(*buffer))
		{
			lexic[*numOfLex].pos = buffer;
			while (myIsOper(*buffer))
				tmpbuf[i++] = *buffer++;
			tmpbuf[i] = '\0';
			lexic[*numOfLex].val = (char*)calloc(Len, sizeof(char));
			strcpy(lexic[*numOfLex].val, tmpbuf);
			lexic[*numOfLex].type = T_op;
			(*numOfLex)++;
		}
		//operator nontext 
		else if (IsOperator(*buffer))
		{
			lexic[*numOfLex].pos = buffer;
				tmpbuf[i++] = *buffer++;
			tmpbuf[i] = '\0';
			lexic[*numOfLex].val = (char*)calloc(Len, sizeof(char));
			strcpy(lexic[*numOfLex].val, tmpbuf);
			lexic[*numOfLex].type = T_op;
			(*numOfLex)++;
		}
		//tabulation
		if (IsTab(*buffer))
		while (IsTab(*buffer))
			*buffer++;

		memset(tmpbuf, '\0', LENGTHOFWORD);
		i = 0;
	}
	lexic[*numOfLex].pos = "\0";
	lexic[*numOfLex].type = -1;
	lexic[*numOfLex].val = "\0";

	(*numOfLex)++;


	return lexic;
}

int myIsOper(char c)
{
	if (c == '*' || c == '-' || c == '+' || c == '/' || c == '>' || c == '<' || c == '=')
		return 1;
	else return 0;
}

int IsOperator(char c)
{
	if (c == '(' || c == ')' || c == '#' || c == '[' || c == ']')
		return 1;
	else return 0;
}

int IsTab(char c)
{
	if (c == '\n' || c == ' ' || c == '\t' || c == '\r')
		return 1;
	else return 0;
}

int IsOper(char* buf)
{
	if (IS("if", buf)) return OK;
	else if (IS("while", buf)) return OK;
	else if (IS("var", buf)) return OK;
	else if (IS("call", buf)) return OK;
	else if (IS("begin", buf)) return OK;
	else if (IS("end", buf)) return OK;
	else return 0;
}
