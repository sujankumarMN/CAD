#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "alap.h"

int main()
{
	List * test;
	test=initialize_list();
	
	assert(test->head==NULL);
	assert(test->tail==NULL);
	assert(test->count==0);
	
	assert(insert_node(test,1,5));
	assert(insert_node(test,2,5));
	assert(insert_node(test,3,6));
	assert(insert_node(test,4,9));
	assert(insert_node(test,5,7));
	assert(insert_node(test,6,8));
	assert(insert_node(test,7,8));
	assert(insert_node(test,8,0));
	assert(insert_node(test,9,0));
	assert(insert_node(test,10,11));
	assert(insert_node(test,11,0));
	
	assert(alap(test,4)==1);
	
	return 0;
}
