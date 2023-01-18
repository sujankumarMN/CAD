typedef struct
{
	char index[10];
	int connect[100];	
}My_type;

typedef struct 
{
	My_type *my_type;
	int count;
	int size;
}My_arr;

My_arr *init(int size);
void add_data(My_arr *my_arr,int *arr ,char *index);
void display(My_arr *my_arr);

void cluster(My_arr *my_arr,int number_node);
