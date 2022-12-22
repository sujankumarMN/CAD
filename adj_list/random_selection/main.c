#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>
#include "header.h"

int main()
{
	List *list,*temp;
	list=init();
	temp=init();
	char doc[]="graph.txt";
	assert(list->vertice_no==0 );
	assert(list->edge_count==0 );
	assert(insert_vertices(list,doc)==INSERTED);
	//display_vertices(list);
	
	temp=search_vertice(list,3);
	assert(temp->vertice_no==3);
	
	assert(insert_connections(list,doc)==INSERTED);
	assert((list+2)->edge_count==2);
	//display_list(list);

	//random_selection_elements(list,2);
	//display_list(list);
	random_selection_cluster(list,2);
}