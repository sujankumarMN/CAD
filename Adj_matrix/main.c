#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include "header.h"

int main()
{
	Array *array;
	array=init();
	assert(array->vertices==0);
	assert(adj_matrix(array,"graph.txt")==SUCCESS);
	assert(array->vertices==3);
	int i,j;
	display_matrix(array);


}