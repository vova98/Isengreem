
FILE* ftrans = NULL;
int ISEND = 0;
int IFcount = 0;
int flag = 0;
char* nameOfFunc = (char*)calloc(LENGTHOFWORD, sizeof(char));


int Translate(node* top, int countOfJump, int *pop, int flag)
{
	
	if (!top) return NULL;
	switch (top->type)
	{
	case T_num: fprintf(ftrans, "push %d\n", atoi(top->data));
	case T_func:
		if (IS(TD, "sqrt"))
		{
			Translate(TL, countOfJump, pop, flag);
			fprintf(ftrans, "sqrt\n");
		}
	case T_op:
		if (IS(TD, "+"))
		{
			Translate(TL, countOfJump, pop, flag);
			Translate(TR, countOfJump, pop, flag);
			fprintf(ftrans, "add\n");
		}
		if (IS(TD, "-"))
		{
			Translate(TL, countOfJump, pop, flag);
			Translate(TR, countOfJump, pop, flag);
			fprintf(ftrans, "sub\n");
		}
		if (IS(TD, "*"))
		{
			Translate(TL, countOfJump, pop, flag);
			Translate(TR, countOfJump, pop, flag);
			fprintf(ftrans, "mul\n");
		}
		if (IS(TD, "/"))
		{
			Translate(TL, countOfJump, pop, flag);
			Translate(TR, countOfJump, pop, flag);
			fprintf(ftrans, "div\n");
		}
		if (IS(TD, "="))
		{
			if (flag == 3) fprintf(ftrans, "%s%d:\n", nameOfFunc, countOfJump - 1);
			else fprintf(ftrans, "%d:\n", countOfJump-1);
			Translate(TR, countOfJump, pop, flag);
			fprintf(ftrans, "pop ");
			*pop = 1;
			Translate(TL, countOfJump, pop, flag);
			if (flag == 3) fprintf(ftrans, "jmp stop%s%d\n",nameOfFunc, countOfJump - 1);
			else fprintf(ftrans, "jmp stop%d\n", countOfJump - 1);
		}
		if (IS(TD, ">"))
		{
			Translate(TL, countOfJump, pop, flag);
			Translate(TR, countOfJump, pop, flag);
			fprintf(ftrans, "ja %d\n", countOfJump);
		}
		if (IS(TD, "<"))
		{
			Translate(TL, countOfJump, pop, flag);
			Translate(TR, countOfJump, pop, flag);
			fprintf(ftrans, "jb %d\n", countOfJump);
		}
		if (IS(TD, "@"))
		{
			Translate(TL, countOfJump, pop, flag);
			Translate(TR, countOfJump, pop, flag);
			fprintf(ftrans, "je %d\n", countOfJump);
		}
		if (IS(TD, "!"))
		{
			Translate(TL, countOfJump, pop, flag);
			Translate(TR, countOfJump, pop, flag);
			fprintf(ftrans, "jne %d\n", countOfJump);
		}
		if (IS(TD, "Op"))
		{
			if (flag == 3)
			{
				fprintf(ftrans, "jmp %s%d\n", nameOfFunc,countOfJump);
				fprintf(ftrans, "stop%s%d:\n", nameOfFunc, countOfJump);
			}
			else
			{
				fprintf(ftrans, "jmp %d\n", countOfJump);
				fprintf(ftrans, "stop%d:\n", countOfJump);
			}

			if (IS(RD,"\0"))
			if (!ISEND){ fprintf(ftrans, "end\n"); ISEND = 1; }
			else
				if (flag == 1)fprintf(ftrans, "jmp stop%d\n", (countOfJump)/100 - 1);
				else if(flag == 2) fprintf(ftrans, "jmp %d\n", (countOfJump) / 100 - 1);
				else if (flag == 3) fprintf(ftrans, "ret\n");
			countOfJump++;
			Translate(TR, countOfJump, pop, flag);
			
			//if (!ISEND) { fprintf(ftrans, "end\n"); ISEND = 1; }
			Translate(TL, countOfJump, pop, flag);
			//fprintf(ftrans, "ja %d\n", ++countOfJump);
		}
		if (IS(TD, "Func"))
		{
			
			Translate(TR, countOfJump, pop, flag);
			strcpy(nameOfFunc, TL->data);
			fprintf(ftrans, "%s:\n", nameOfFunc);
			//flag = 3;
			Translate(TL->left, countOfJump, pop, flag);
		}
		if (IS(TD, "main"))
		{
			Translate(TL, countOfJump, pop, flag);
			flag = 3;
			Translate(TR, countOfJump, pop, flag);
		}
		break;
	case T_var:
		for (int i = 0; i < Var.count; i++)
		if (IS(Var.vars[i], TD))
		{
			if (*pop)
			{
				fprintf(ftrans, "%cx\n", i + 97);
				*pop = 0;
			}
			else
				fprintf(ftrans, "push %cx\n", i + 97);
		}
		break;
	case T_Mop:
		if (IS(TD, "read"))
		{
			fprintf(ftrans, "%d:\n", countOfJump-1);
			fprintf(ftrans, "in\n");
			fprintf(ftrans, "pop ");
			*pop = 1;
			Translate(TL, countOfJump, pop, flag);
			fprintf(ftrans, "jmp stop%d\n", countOfJump - 1);
		}
		if (IS(TD, "write"))
		{
			fprintf(ftrans, "%d:\n", countOfJump-1);
			Translate(TL, countOfJump, pop, flag);
			fprintf(ftrans, "out\n");
			fprintf(ftrans, "jmp stop%d\n", countOfJump - 1);
		}
		if (IS(TD, "call"))
		{
			fprintf(ftrans, "%d:\n", countOfJump-1);
			fprintf(ftrans, "call %s\n", LD);
			//(countOfJump)++;
			//Translate(TL, countOfJump, pop, flag);
			fprintf(ftrans, "jmp stop%d\n", countOfJump - 1);
			//fprintf(ftrans, "out\n");
		}
		if (IS(TD, "while"))
		{
			flag = 2;
			IFcount = 100 * (countOfJump);
			fprintf(ftrans, "%d:\n", countOfJump - 1);

			Translate(TL, IFcount, pop, flag);
			fprintf(ftrans, "jmp stop%d\n", countOfJump - 1);

			Translate(TR, IFcount, pop, flag);
			fprintf(ftrans, "jmp %d\n", countOfJump - 1);
			flag = 0;
		}
		if (IS(TD, "if"))
		{
			flag = 1;
			IFcount = 100 * (countOfJump);
			fprintf(ftrans, "%d:\n", countOfJump-1);

			Translate(TL, IFcount, pop, flag);
			fprintf(ftrans, "jmp stop%d\n", countOfJump - 1);

			Translate(TR, IFcount, pop, flag);
			fprintf(ftrans, "jmp stop%d\n", countOfJump - 1);
			flag = 0;
		}
	}
	return OK;
}