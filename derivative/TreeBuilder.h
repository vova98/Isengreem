
#define CREATEDATA(vertex)		\
	(char*)vertex->data = (char*)calloc(LENGTHOFWORD, sizeof(char));

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


struct node
{
	char* data;
	int type;
	node* left;
	node* right;
	node() :data(""), type(), left(NULL), right(NULL){}
};

//node* NodeCtor(int type, const char op, node* left, node* right);
node* GetG0(const char* buffer);
node* GetS();
node* GetN();
node* GetT();
node* GetE();
node* GetP();
node* GetVar();
node* GetFunc(char* val);

node* GetG0(const char* buffer)
{
	s = buffer;
	node* top = GetE();
	int count = 0;
	//int val = PrintTree(top, &count);
	if (*s == NULL) return top;
	else return NULL;
}

node *GetE()
{
	node* top = new node;
	node* leaf2 = new node;
	node* leaf = GetT();
	if (!leaf) return NULL;
	char op = 0;
	while (*s == '+' || *s == '-')
	{
		top = new node;
		op = *s++;
		leaf2 = GetT();
		if (!leaf2) return NULL;
		CREATEDATA(top);
		top->data[1] = '\0';
		MAKENODE(T_op);

	}
	return leaf;
}

node* GetN()
{
	node* leaf = new node;
	int count = 0;
	char* val = (char*)calloc(SIZEOFNUMBER, sizeof(char));
	while (*s >= '0' && *s <= '9' || *s == '.' || *s == '-')
	{
		val[count++] = *s;
		*s++;
	}
	(char*)leaf->data = (char*)calloc(count + 1, sizeof(char));
	strcpy(leaf->data, val);
	//ftoa(val, leaf->data, Radix);
	leaf->data[count] = '\0';
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
	while (*s == '/' || *s == '*')
	{
		top = new node;
		op = *s++;
		leaf2 = GetS();
		if (!leaf2) return NULL;
		CREATEDATA(top);
		top->data[1] = '\0';
		MAKENODE(T_op);
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
	if (*s == '^')
	{
		top = new node;
		op = *s++;
		leaf2 = GetP();
		if (!leaf2) return NULL;
		CREATEDATA(top);
		top->data[1] = '\0';
		MAKENODE(T_op);
	}
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
		else return NULL;
	}
	else
	{
		val = GetN();
		if (atof(val->data) == NULL) return GetVar();
		else return val;
	}
}

node* GetVar()
{
	node* leaf = new node;
	char val[LENGTHOFWORD] = "";
	int count = 0;
	while (*s >= 'a' && *s <= 'z' || *s >= 'A' && *s <= 'Z')
	{
		val[count++] = *s;
		*s++;
	}
	if (IsFunc(val))
		return GetFunc(val);
	(char*)leaf->data = (char*)calloc(count + 1, sizeof(char));
	leaf->data[count] = '\0';
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


