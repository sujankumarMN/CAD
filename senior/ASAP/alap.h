struct _node_
{
	int data;
	int sc;
	int l;
	struct _node_ *ptr;
};

typedef struct _node_ Node;

struct _list_
{
	Node *head,*tail;
	int count;
};

typedef struct _list_ List;

List * initialize_list();
Node * get_node(int,int);
int insert_node(List *,int,int);
int alap(List *,int);
int get_l(List *,int);
//int max(int a,int b);
