#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"list.h"

int main()
{
	List * test;
	test=initialize_list();
	
	assert(test->head==NULL);
	assert(test->tail==NULL);
	assert(test->count==0);
	
	assert(insert_node(test,1,0,0));
	assert(insert_node(test,2,0,0));
	assert(insert_node(test,3,0,0));
	assert(insert_node(test,4,0,0));
	assert(insert_node(test,5,1,2));
	assert(insert_node(test,6,0,3));
	assert(insert_node(test,7,0,5));
	assert(insert_node(test,8,7,6));
	assert(insert_node(test,9,0,4));
	assert(insert_node(test,10,0,0));
	assert(insert_node(test,11,0,10));
	
	//assert(test->tail->data==11);
	
	assert(asap(test)==1);
	
	
	return 0;
}
