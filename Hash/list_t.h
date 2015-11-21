

#define OK 1
#define BAD 0
#define SIZEOFWORD 35

int ListError(int line)
{
	FILE* flog = NULL;
	errno_t err = fopen_s(&flog, "Log. txt", "a");

	fprintf(flog,"List was corrupted at <%d> line", line);
	return BAD;
}

struct value
{
	int count;
	char* str;
};

struct node
{
	char val[SIZEOFWORD];
	node* next;
	node* prev;

	node() : val{}, prev(NULL), next(NULL){}
	//node(int val,node* prev, node* next) : val(val), next(next), prev(prev) {}
};

class List
{
public:
	node *head, *tail;
	size_t size;

public:
	List();

	int addHead(char* value);
	int addTail(char* value);
	int show();
	int List_Ok();
	int show(int num);
	int delet(int num);
	node* Find(char* val);
	node* Elem(int num);
	int show(node* Elem);

	~List();
};



List::List()
{
	head = new node;
	tail = new node;
	//head->val[0] = '\0';
	memset(head->val, '\0', SIZEOFWORD);
	head->next = tail;
	head->prev = NULL;
	tail = head;
	/*tail->val = 0;
	tail->next = NULL;
	tail->prev = head;*/
	size = 0;

}

node* List::Elem(int num)
{
	node* tmpElem = new node;
	tmpElem = head;

	if (!List_Ok()) { ListError(__LINE__);  return BAD; }

	for (int i = 0; i < num; i++)
		tmpElem = tmpElem->next;
	return tmpElem;
}

node* List::Find(char* val)
{
	node* tmpElem = new node;

	if (!List_Ok()) { ListError(__LINE__);  return BAD; }

	if (head == NULL) return 0;
	tmpElem = head;
	while (tmpElem != NULL && strcmp(tmpElem->val, val))
		tmpElem = tmpElem->next;
	return tmpElem;
}

int List::addHead(char* value)
{
	node* newElem = new node;

	assert(newElem);
	if (!List_Ok()) { ListError(__LINE__);  return BAD; }

	if (size == 0)
		strcpy(head->val,value);
	else
	{
		strcpy(newElem->val,value);
		head->prev = newElem;
		newElem->next = head;
		head = newElem;
	}
	size++;
	return OK;
}

int List::addTail(char* value)
{
	node* newElem = new node;
	assert(newElem);
	if (!List_Ok()) { ListError(__LINE__);  return BAD; }
		if (size == 0)
			strcpy(tail->val, value);
		else
		{
			tail->next = newElem;
			strcpy(newElem->val, value);
			newElem->prev = tail;
			newElem->next = NULL;
			tail = newElem;
		}
		size++;
	return OK;
	
}

int List::delet(int num)
{
	node* curElem = new node;
	curElem = Elem(num);

	assert(curElem);
	if (!List_Ok()) { ListError(__LINE__);  return BAD; }

	curElem->prev->next = curElem->next;
	curElem->next->prev = curElem->prev;

	curElem->next = NULL;
	curElem->prev = NULL;
	memset(curElem->val, '\0', SIZEOFWORD);
	//curElem->val = "/0";

	delete curElem;

	if (!List_Ok()) { ListError(__LINE__);  return BAD; }

	return OK;
}

int List::List_Ok()
{
	node* curElem = new node;
	curElem = head;
	assert(curElem);
	if (head != tail)
	while (curElem->next != tail)
	{
		if (curElem->next->prev != curElem)
			return BAD;
		curElem = curElem->next;
	}
	return OK;
}

int List::show()
{
	node* curElem = new node;
	curElem = head;

	assert(curElem);
	if (!List_Ok()) { ListError(__LINE__);  return BAD; }

	while (curElem != tail)
	{
		assert(curElem);
		printf("value = <%s> \n"
			"   curr - <%d> \n"
			"   next - <%d> \n"
			"   prev - <%d> \n\n", curElem->val, curElem, curElem->next, curElem->prev);
		curElem = curElem->next;
		
	} 
	//printf("value = <%s> \n"
	//	"   curr - <%d> \n"
	//	"   next - <%d> \n"
	//	"   prev - <%d> \n\n", curElem->val, curElem, curElem->next, curElem->prev);
	return OK;
}

int List::show(int num)
{
	node* curElem = new node;
	curElem = Elem(num);

	assert(curElem);
	if (!List_Ok()) { ListError(__LINE__);  return BAD; }

	printf("value = <%s> \n"
		"   curr - <%d> \n"
		"   next - <%d> \n"
		"   prev - <%d> \n\n", curElem->val, curElem, curElem->next, curElem->prev);

	return OK;
}

List::~List()
{
	assert(head || tail);
	while (head)
	{
		tail = head->next;
		delete head;
		head = tail;
	}
	int a = 0;
}
