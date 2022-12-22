#define MAX 20
#define INIT_SUCCESS 1
#define INSERTED 2


typedef struct _node_ Node;
struct _node_
{
	int connect;
	int weight;
	Node *ptr;
};

struct _list_
{
	int vertice_no;
	Node *head;
	Node *tail;
	int edge_count;
};
typedef struct _list_ List;

struct _array_
{
	List vertice[MAX];
	int csize,tsize,op_status;
};
typedef struct _array_ Array;

int count_vertices(char []);
List * init();
int insert_vertices(List *,char []);
List * search_vertice(List *,int);
Node * getnode(int,int);
int insert_connections(List *,char[]);
void display_vertices(List *);
void display_list(List *);