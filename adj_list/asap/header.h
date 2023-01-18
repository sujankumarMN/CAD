#define MAX 20
#define INIT_SUCCESS 1
#define INSERTED 2


typedef struct _node_ Node;
struct _node_
{
	
	int no_of_pred;
	int connect;
	Node *ptr;
};

struct _list_
{
	int vertice_no;
	int is_scheduled;
	Node *head;
	Node *tail;
	int edge_count;
};
typedef struct _list_ List;

int count_vertices(char []);
int count_levels(char []);

List * init();
int insert_vertices(List *,char []);
List * search_vertice(List *,int);
int insert_connections(List *my_list,char doc[]);
Node * getnode(int,int);
void asap(List *);

void display_vertices(List *);
void display_list(List *);