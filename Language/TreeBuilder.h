
#define CREATEDATA(vertex)		\
	(char*)vertex->data = (char*)calloc(LENGTHOFWORD, sizeof(char));

#define IS(Var, vaL) !strcmp(Var, vaL)

#define NODECTOR(vertex, Data, Type, Left, Right)	\
	vertex->type = Type;							\
	CREATEDATA(vertex)								\
	strcpy(vertex->data, Data);						\
	vertex->left = Left;							\
	vertex->right = Right;


#define MAKENODE(oper)		\
	top->type = oper;		\
	top->left = leaf;		\
	top->right = leaf2;		\
	top->data[0] = op;		\
	leaf = top;

#define CREATEEXPRESSION(func)	\
top = new node;					\
op = *s->val;					\
*s++;							\
leaf2 = func;					\
if (!leaf2) return NULL;		\
CREATEDATA(top);				\
top->data[1] = '\0';			\
MAKENODE(T_op);				


struct node
{
	char* data;
	int type;
	node* left;
	node* right;
	node() :data(""), type(), left(NULL), right(NULL){}
};

//node* NodeCtor(int type, const char op, node* left, node* right);
node* GetG0(lex*);
node* GetS();
node* GetN();
node* GetT();
node* GetE();
node* GetP();
node* GetVar();
node* GetEq();
node *GetIf();
node *GetOp();
node *GetCall();
node* GetFunc(char* val);
int IsFunc(char* val);

const int LENGTHOFWORD = 10;

node* GetG0(lex* lexic)
{
	s = new lex;
	s = lexic;

	if (!IS(s->val, "begin")) return NULL;
	s++;

	node* top = NULL;
	top = GetOp();

	if (!top) return NULL;
	if (IS(s->val, "end")) return top;
	else return NULL;
}

node* GetOp()
{
	node* top = new node;
	node* leaf2 = new node;
	node* leaf = NULL;
	if (IS(s->val, "if") || IS(s->val, "while"))
		leaf = GetIf();
	else if (IS(s->val, "call"))
		leaf = GetCall();

	else {
		if (IS(s->val, "var"))
			s++;
		leaf = GetEq();
	}
	if (!leaf) return NULL;

	if (!IS(s->val, "]") && !IS(s->val, "end"))
	{
		leaf2 = GetOp();
		if (!leaf2) return NULL;
	}
	else if (!IS(s->val, "]") && !IS(s->val, "end")) s++;
	CREATEDATA(top);
	NODECTOR(top, "Op", T_op, leaf, leaf2);

	return top;
}


node* GetEq()
{
	node* top = new node;
	node* leaf2 = new node;
	node* leaf = NULL;
	if (s->type == T_var)
	leaf = GetVar();
	if (!leaf) return NULL;

	char op = 0;
	//	top = new node;
	op = *s->val;
	*s++;
	leaf2 = GetE();
	if (!leaf2) return NULL;
	if (!IS(s->val, "#")) return NULL;
	else if (!IS(s->val, "end")) s++;
	CREATEDATA(top);
	MAKENODE(T_op);
	return leaf;
}


node *GetE()
{
	node* top = new node;
	node* leaf2 = new node;
	node* leaf = GetT();
	if (!leaf) return NULL;
	char op = 0;
	while (*s->val == '+' || *s->val == '-')
	{
		CREATEEXPRESSION(GetT());
		/*top = new node;
		op = *s->val;
		*s++;
		leaf2 = GetT();
		if (!leaf2) return NULL;
		CREATEDATA(top);
		top->data[1] = '\0';
		MAKENODE(T_op);*/
	}
	if (*s->val == '>' || *s->val == '<')
	{
		CREATEEXPRESSION(GetE());
		/*top = new node;
		op = *s->val;
		*s++;
		leaf2 = GetE();
		if (!leaf2) return NULL;
		CREATEDATA(top);
		top->data[1] = '\0';
		MAKENODE(T_op);*/
	}
	return leaf;
}

node* GetN()
{
	node* leaf = new node;
	int count = 0;
	char* val = (char*)calloc(SIZEOFNUMBER, sizeof(char));
	(char*)leaf->data = (char*)calloc(count + 1, sizeof(char));
	strcpy(leaf->data, s->val);
	*s++;
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
	while (*s->val == '/' || *s->val == '*')
	{
		CREATEEXPRESSION(GetS());
		//top = new node;
		//op = *(s->val);
		//*s++;
		//leaf2 = GetS();
		//if (!leaf2) return NULL;
		//CREATEDATA(top);
		//top->data[1] = '\0';
		//MAKENODE(T_op);
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
	if (*s->val == '^')
	{
		CREATEEXPRESSION(GetP());
		//top = new node;
		//op = *(s->val);
		//*s++;
		//leaf2 = GetP();
		//if (!leaf2) return NULL;
		//CREATEDATA(top);
		//top->data[1] = '\0';
		//MAKENODE(T_op);
	}
	return leaf;
}

node *GetP()
{
	node* val = {};
	if (*s->val == '(')
	{
		s++;
		node* leaf = GetE();
		if (*s->val == ')')
			s++;
			return leaf;
	}
	else
	{
		if (s->type == T_num)
			return GetN();
		else return GetVar();
	}
}

node *GetIf()
{
	node* top = new node;
	if (IS(s->val, "if") || IS(s->val, "while"))
	{
		char* name = (char*)calloc(strlen(s->val), sizeof(char));
		strcpy(name, s->val);
		s++;
		if (*s->val == ')')
		{
			s++;
			node* leaf = GetE();
			if (IS(s->val, "(")) s++;
			if (IS(s->val, "["))
			{
				s++;
				node* leaf2 = GetOp();
				if (!IS(s->val, "]") || !leaf2) return NULL; s++;
				CREATEDATA(top);
				NODECTOR(top, name, T_Mop, leaf, leaf2);
				return top;
			}
		}
	}
	return NULL;
}

node *GetCall()
{
	node* top = new node;
	if (IS(s->val, "call"))
	{
		s++;
		node* leaf = GetVar();
		if (!IS(s->val, "(") || !leaf) return NULL;
		s++;
		if (IS(s->val, ")"))
		{
			s++;
			if (!IS(s->val, "#")) return NULL;
			else if (!IS(s->val, "end")) s++;
			CREATEDATA(top);
			NODECTOR(top, "call", T_Mop, leaf, NULL);
			return top;
		}
	}
	return NULL;
}


node* GetVar()
{
	node* leaf = new node;
	char val[LENGTHOFWORD] = "";
	int count = 0;
	strcpy(val, s->val);
	*s++;
	if (IsFunc(val))
		return GetFunc(val);
	(char*)leaf->data = (char*)calloc(strlen(val), sizeof(char));
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
	else if (IS("tg", val)) return OK;
	else if (IS("ctg", val)) return OK;
	else if (IS("ln", val)) return OK;
	else return 0;
}


