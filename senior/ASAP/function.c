#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Header.h"


int number_of_vertice_reader()
{ //To read no. of Vertices from the graph file.
	FILE* fp;
	char ch = " ";
	int vertice_number = 0;

	fp = fopen("E:\\Program Files\\Microsoft Visual Studio\\Source\\ASAP\\Circuit_graph_new.txt", "r");

	//fp = fopen("E:\\Program Files\\Microsoft Visual Studio\\Source\\ASAP\\graph2.txt", "r");

	if (fp == NULL) return FAILURE; //Checking whether the file opens correctly.

	fscanf(fp, "%*s"); //Ignoring  the 1st line, since in the graph file 1st file indicates vertices names i.e "V1 V2 V3 V4 V5". 

	while (1) {  //counting no. of lines in the graph file assuming that values are entered in terms of square matrix.

		ch = getc(fp);

		if (ch == EOF)
			break;

		if (ch == '\n')
			vertice_number++; //no. of lines in the graph  file(Ignoring  the 1st line) gives the number of Vertices in the graph. 
	}

	fclose(fp);
	return vertice_number;
}

Vertex_node* add_vertex_node(int vertex_no, int edge_weight, Vertices_list* my_vertice_list)
{ //To Create a vertex node wrt given vertex_no & edge_weight
	Vertex_node* node;

	node = (Vertex_node*)malloc(sizeof(Vertex_node));

	if (node == NULL) return NULL;  //Checking for memory allocation

	node->vertex_no = vertex_no;    //adding vertex number
	node->edge_weight = edge_weight;//adding  edge weight
	node->next_vertex_ptr = NULL;
	node->vertices_info = my_vertice_list;

	return node;
}

Vertices_list* initilize_Vertices_list(int number_of_vertices) //To allocate memory and initialize "Vertices_list"
{
	Vertices_list* my_vertice_list;

	my_vertice_list = (Vertices_list*)malloc(number_of_vertices * sizeof(Vertices_list)); //Allocating memory for "Vertices_list"


	if (my_vertice_list == NULL) return NULL; //Checking for memory allocation

	for (int i = 0; i < number_of_vertices; i++) {

		//Initializing my_vertice_list[i] head & tail with "Vetex_node" pointer of each vertex
		my_vertice_list[i].head = my_vertice_list[i].tail = add_vertex_node(i + 1, -1,NULL); //adding "1" because index 'i" starts 0 and vertex number from "1"

		my_vertice_list[i].outgoing_edge_count = 0;// Setting default outgoing_edge_count,incoming_edge_coun & partitioned_status  as zero
		my_vertice_list[i].incoming_edge_count = 0;
		my_vertice_list[i].scheduled_status = 0;
		my_vertice_list[i].controlStep = 0;
	}


	return my_vertice_list;
}

int insert_connection_direct(Vertices_list* my_vertice_list) {


	Vertex_node* node;
	FILE* fp2;
	int number_of_vertices;
	int data;


	if (my_vertice_list == NULL) return FAILURE; //Checking whether "my_vertice_list" have been initialized or not

	number_of_vertices = number_of_vertice_reader(); //reading number of vertices


	fp2 = fopen("E:\\Program Files\\Microsoft Visual Studio\\Source\\ASAP\\Circuit_graph_new.txt", "r"); //Checking whether the file opens correctly.

	//fp2 = fopen("graph2.txt", "r");

	if (fp2 == NULL) return FAILURE; //Checking whether the file opens correctly.


	fscanf(fp2, "%*s %*s %*s %*s %*s"); //Ignoring  the 1st line, since in the graph file 1st file indicates vertices names i.e "V1 V2 V3 V4 V5". 


	for (int row_no = 0; row_no < number_of_vertices; row_no++) {

		fscanf(fp2, "%*s"); /*Ignoring starting String which indicates  "Vertex Number" i.e. "V1.....
																							  V2......
																							  V3...... etc from graph file.*/


		for (int column_no = 0; column_no < number_of_vertices; column_no++) {

			fscanf(fp2, "%d", &data);  //reading the edge_weights from the file

			//printf("\n%d",data);

			if (data != 0) { //Ignoring '0', since  '0' denotes "NO CONNECTION b/w vertices or "SELF CONNECTION b/w same vertex.

				if (data < 0) //'-ve edge weights'  denotes "INCOMING" edges.
					my_vertice_list[row_no].outgoing_edge_count++;

				else {

					//printf("%d%d\n", row_no, column_no);
					node = add_vertex_node(column_no + 1, data,(my_vertice_list+ column_no)); //adding "1" because index 'column_no" starts 0 and vertex number from "1"

					//(NOTE : Similar to add_node_at_end in linked list)
					my_vertice_list[row_no].tail->next_vertex_ptr = node; //connecting the new "node" to the list
					my_vertice_list[row_no].tail = node;              //Updating the tail of the list.
					my_vertice_list[row_no].incoming_edge_count++; //Increasing the outgoing egde count of given vertex;
					//printf("%d %d\n", row_no + 1, my_vertice_list[row_no].incoming_edge_count);
				}

			}
			//printf("\n");
		}
	}

	return 1;
}

Scheduled_array* initialize_scheduled_array(int number_of_vertices)
{
	Scheduled_array* my_scheduled;

	my_scheduled = (Scheduled_array*)malloc(sizeof(my_scheduled));

	my_scheduled->arr = (int*)malloc(number_of_vertices * sizeof(int));

	my_scheduled->scheduled_node_count = 0;

	return my_scheduled;
}

int asap_scheduler(Vertices_list* my_vertice_list, Scheduled_array* scheduled)
{
	int number_of_vertices,control_step=1;

	number_of_vertices = number_of_vertice_reader();

	for (int i = 0; i < number_of_vertices; i++) {
		//printf(" Step: %d V%d\n", control_step, i + 1);

		if (my_vertice_list[i].incoming_edge_count == 0) {

			my_vertice_list[i].controlStep = control_step;
			my_vertice_list[i].scheduled_status = 1;

			scheduled->arr[i] = control_step;
			scheduled->scheduled_node_count++;
			printf("Control Step: %d V%d\n", control_step, i + 1);
		}
	}

	while (scheduled->scheduled_node_count < 5) {

		for (int i = 0; i < number_of_vertices; i++) {
			//printf(" %d Step: %d V%d\n", all_nodes_scheduler(my_vertice_list), control_step, i + 1);
			if (all_nodes_scheduler((my_vertice_list +i))) {

				my_vertice_list[i].controlStep = max_contolStep(my_vertice_list) + 1;
				my_vertice_list[i].scheduled_status = 1;

				scheduled->arr[i] = ++control_step;
				scheduled->scheduled_node_count++;
				printf("Control Step: %d V%d\n", control_step, i + 1);
			}
		}

	}

	return 0;
}

int all_nodes_scheduler(Vertices_list* my_vertice_list)
{
	int flag = 0;
	Vertex_node* temp;

	if (my_vertice_list->scheduled_status)
		return FAILURE;

	temp = my_vertice_list->head->next_vertex_ptr;

	for (; temp != NULL; temp = temp->next_vertex_ptr) {

		if (temp->vertices_info->scheduled_status == 0) { //if any node is not scheduled then return 
			//printf("tep: %d V%d\n", temp->vertex_no, temp->vertices_info->head->vertex_no+1);
			return FAILURE;
		}
	}

	return SUCCESS;
}

int max_contolStep(Vertices_list* my_vertice_list)
{
	Vertex_node* temp;
	int max_control_step=0;

	temp = my_vertice_list->head->next_vertex_ptr;

	for (; temp->next_vertex_ptr != NULL; temp = temp->next_vertex_ptr) {

		if (temp->vertices_info->controlStep > max_control_step)
			max_control_step = temp->vertices_info->controlStep;
	}

	return max_control_step;
}