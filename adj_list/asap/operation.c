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
int count_levels(char doc[])
{
	FILE *fp;
	int n;
	fp=fopen(doc,"r");
	fscanf(fp,"%d",&n);
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
		(my_list+i)->is_scheduled=0;
		(my_list+i)->edge_count=0;
		(my_list+i)->head=(my_list+i)->tail=NULL;

	}
	return my_list;

}
int insert_vertices(List *my_list,char doc[])
{
	FILE *fp;
	int vertices,i,n;
	char in1[3];
	fp=fopen(doc,"r");
	fscanf(fp,"%d",&vertices);
	fscanf(fp,"%d",&n);
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

Node * getnode(int connect,int no_of_pred)
{
	Node *newnode;
	newnode=(Node *)malloc(sizeof(Node));
	if(newnode==NULL) return NULL;
	newnode->no_of_pred=no_of_pred;
	newnode->connect=connect;
	newnode->ptr=NULL;
	printf("\nconnect=%d,pred:%d",newnode->connect,newnode->no_of_pred);
	return newnode;


}

int insert_connections(List *my_list,char doc[])
{
	FILE *fp;
	List *temp;
	Node *my_node;
	int vertices,i,no_of_pred,levels;
	char in1[3],in2[3];
	fp=fopen(doc,"r");
	fscanf(fp,"%d",&vertices);
	fscanf(fp,"%d",&levels);
	for(i=0;i<vertices;i++)
	{
		fscanf(fp,"%s",in1);
	}
	while(!feof(fp))
	{
		fscanf(fp,"%s %s %d",in1,in2,&no_of_pred);
		temp=search_vertice(my_list,atoi(&in1[1]));
		my_node=getnode(atoi(&in2[1]),no_of_pred);
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
	//printf("vertex: %d, connect %d, pred:%d",(my_list+vertices-1)->vertice_no,my_list->tail->connect,my_list->tail->no_of_pred);
	return INSERTED;

}

void asap(List *my_list)
{
	List *temp;
	Node *tempnode;
	int i,j;
	if(my_list->is_scheduled == 0)
		display_list(my_list);
	for(j=1;j<=count_levels("graph.txt");j++)
	{
		printf("level %d: ",j);
		for(i=0;i<count_vertices("graph.txt");i++)
			{
				temp=search_vertice(my_list,i+1);
				if(temp->is_scheduled == 0)
				{
					for(tempnode=temp->head;tempnode!=NULL;tempnode=tempnode->ptr)
					{
						if(tempnode->no_of_pred == j-1)
							{
								if(temp->is_scheduled == 0)
								{
									printf("V%d  ",temp->vertice_no );
									temp->is_scheduled=1;
								}
								
							}
					}

				}
			}
			printf("\n");	
	}
	printf("\n");
	if(my_list->is_scheduled == 0)
		display_list(my_list);
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
		printf("\nV%d >>> ",(my_list+i)->vertice_no );
		for(temp=(my_list+i)->head;temp!=NULL;temp=temp->ptr)
		{
			printf("predecessors are: V%d ",temp->connect);
			printf(" with predecessors count: %d\t",temp->no_of_pred);
			
		}
		//printf(" with predecessors count: %d\t",my->no_of_pred);
		printf("\n");
	}

		

}