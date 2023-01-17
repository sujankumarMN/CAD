#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
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
	assert(insert_connections(list,doc)==INSERTED);
	//display_vertices(list);
	//printf("levels=%d\n",count_levels(doc));
	//display_list(list);
	asap(list);
	
}