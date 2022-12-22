#include<stdlib.h>
#include<stdio.h>
#include "header.h"


Array * init()
{
	Array *my_array;
	my_array=(Array *)malloc(sizeof(Array));
	if(NULL==my_array) return NULL;
	my_array->vertices=0;
	//my_array->tsize=0;
	my_array->op_status = INIT_SUCCESS;
	return my_array;
}

int adj_matrix(Array *my_array,char doc[])
{
	FILE *fp;
	int vertices,weight,i,j;
	char in1[3],in2[3];

	fp=fopen(doc,"r");
	fscanf(fp,"%d",&vertices);

	fscanf(fp,"%s %s %s",in1,in1,in1 );
	my_array->vertices=vertices;
	
	while(!feof(fp))
	{
		fscanf(fp,"%s %s %d",in1,in2,&weight);
		
			my_array->adj[atoi(&in1[1])-1][atoi(&in2[1])-1]=weight;
	}
	fclose(fp);
	return SUCCESS;
}

void display_matrix(Array *my_array)
{
	int i,j;
	for(i=0;i<my_array->vertices;i++)
	{
			for(j=0;j<my_array->vertices;j++)
				printf("%d ",my_array->adj[i][j]);
			printf("\n");
	}
}