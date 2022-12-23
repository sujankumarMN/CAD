struct _node_
{
	int vertex_no;  // vertex number
	int pd1,pd2;  // predessor 
	int e;  // in which level the vetrex has to place
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

Node * get_node(int,int,int);

int insert_node(List *,int,int,int);

int asap(List *);

int get_e(List *,int);

int max(int a,int b);
