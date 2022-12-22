#define ROW_SIZE 10
#define COL_SIZE 10
#define INIT_SUCCESS 1
#define SUCCESS 2

struct _array_
{
	int adj[ROW_SIZE][COL_SIZE];
	int vertices,op_status;
};
typedef struct _array_ Array;

Array * init();
int adj_matrix(Array *,char []);
void display_matrix(Array *);

