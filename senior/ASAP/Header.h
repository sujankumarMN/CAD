#define _CRT_SECURE_NO_WARNINGS
#define SUCCESS 1
#define FAILURE 0


typedef struct _vertices_list_ Vertices_list;
typedef struct _vertex_node_ Vertex_node;
struct _vertex_node_ {

	int vertex_no;
	int edge_weight;
	Vertex_node* next_vertex_ptr;
	Vertices_list* vertices_info;
};


struct _vertices_list_ {

	Vertex_node* head;
	Vertex_node* tail;
	int outgoing_edge_count; //to store no. of  outgoing connections
	int incoming_edge_count; //to store no. of  incoming connections
	int scheduled_status; //Specifies wheter a particular edge is scheduled or not 
	int controlStep;

};


typedef struct _scheduled_array_ Scheduled_array;
struct _scheduled_array_ { //Array list to store the partioned vertices

	int* arr;
	int scheduled_node_count; //indicates number of vertex in each partition

};

int number_of_vertice_reader(); //To read no. of Vertices from the graph file. (NOTE: The 1st line of the graph file gives the no. of vertices)

Vertices_list* initilize_Vertices_list(int number_of_vertices); //To allocate memory and initialize "Vertices_list"

Vertex_node* add_vertex_node(int vertex_no, int edge_weight, Vertices_list* my_vertice_list); //To Create a vertex node wrt given vertex_no & edge_weight

int insert_connection_direct(Vertices_list* my_vertice_list); //Mapping the values directly to adjacentcy list

Scheduled_array* initialize_scheduled_array(int number_of_vertices);

int asap_scheduler(Vertices_list* my_vertice_list, Scheduled_array* scheduled);

int all_nodes_scheduler(Vertices_list* my_vertice_list);

int max_contolStep(Vertices_list* my_vertice_list);
