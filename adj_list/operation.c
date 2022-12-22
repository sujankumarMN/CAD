#include<stdio.h>
#include<stdlib.h>
#include "header.h"

int count_vertices(char doc[])
{
	FILE *fp;
	int n;
	fp=fopen(doc,"r");
	fscanf(fp,"%d",&n);
	fclose(fp);
	return n;
}

List * init()
{

	List *my_list;
	int i;
	int vertices=count_vertices("graph.txt");
	my_list=(List *)malloc(vertices * sizeof(List));
	if(my_list==NULL) return NULL;
	for(i=0;i<vertices;i++)
	{
		(my_list+i)->vertice_no=0;
		(my_list+i)->edge_count=0;
		(my_list+i)->head=(my_list+i)->tail=NULL;

	}
	return my_list;

}
int insert_vertices(List *my_list,char doc[])
{
	FILE *fp;
	int vertices,i;
	char in1[3];
	fp=fopen(doc,"r");
	fscanf(fp,"%d",&vertices);
	for(i=0;i<vertices;i++)
	{
		fscanf(fp,"%s",in1);
		(my_list+i)->vertice_no= atoi(&in1[1]);
	}
	fclose(fp);
	return INSERTED;	

}
List * search_vertice(List *my_list,int v)
{
	int i;
	for(i=0;i<count_vertices("graph.txt");i++)
	{
		if(v==(my_list+i)->vertice_no)
			return my_list+i;

	}

			return NULL;
}

Node * getnode(int c,int weight)
{
	Node *newnode;
	newnode=(Node *)malloc(sizeof(Node));
	if(newnode==NULL) return NULL;
	newnode->connect=c;
	newnode->weight=weight;
	newnode->ptr=NULL;
	return newnode;

}

int insert_connections(List *my_list,char doc[])
{
	FILE *fp;
	List *temp;
	Node *my_node;
	int vertices,i,weight;
	char in1[3],in2[3];
	fp=fopen(doc,"r");
	fscanf(fp,"%d",&vertices);
	for(i=0;i<vertices;i++)
	{
		fscanf(fp,"%s",in1);
	}
	while(!feof(fp))
	{
		fscanf(fp,"%s %s %d",in1,in2,&weight);
		temp=search_vertice(my_list,atoi(&in1[1]));
		my_node=getnode(atoi(&in2[1]),weight);
		if(temp->edge_count == 0)
		{
			temp->edge_count++;
			temp->head = temp->tail =my_node;

		}
		else
		{
			temp->tail->ptr=my_node;
			temp->tail=my_node;
			temp->edge_count++;
		}
	}
	//printf("weight==%d\n",(my_list+2)->tail->weight);
	fclose(fp);
	return INSERTED;

}
void display_vertices(List *my_list)
{
	int i;
	for(i=0;i<count_vertices("graph.txt");i++)
		printf("%d -->\n",(my_list+i)->vertice_no );
}

void display_list(List *my_list)
{
	int i;
	Node * temp;
	for(i=0;i<count_vertices("graph.txt");i++)
	{
		printf("%d >>> ",(my_list+i)->vertice_no );
		for(temp=(my_list+i)->head;temp!=NULL;temp=temp->ptr)
		{
			
			printf("%d with weight: %d\t",temp->connect,temp->weight);
		}
		printf("\n");
	}

		

}

