#include<stdio.h>
#include<stdlib.h>
#include<math.h>
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
		(my_list+i)->is_visited=0;
		(my_list+i)->sum=0;
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


void sum_it(List *my_list)
{
	int i;
	Node *temp;
	for(i=0;i<count_vertices("graph.txt");i++)
	{
		for(temp=(my_list+i)->head;temp!=NULL;temp=temp->ptr)
		{
			(my_list+i)->sum=(my_list+i)->sum+temp->weight;
		}
		
	}
}

List * max_sum(List *my_list)
{
	int max=0;
	int i;
	List *temp;
	for(i=0;i<count_vertices("graph.txt");i++)
	{
		if((my_list+i)->sum>max && (my_list+i)->is_visited==0)
		{
			max=(my_list+i)->sum;
			temp=(my_list+i);
		}
	}
	
	return temp;
}

Node * max_weight(List *my_list,List *b_list)
{
	List *chk;
	Node *tempnode,*temp;
	int max=0;
	
	for(temp=b_list->head;temp!=NULL;temp=temp->ptr)
	{
		if(temp->weight>max )
		{
			chk=search_vertice(my_list,temp->connect);
			if(chk->is_visited==0)
			{
				max=temp->weight;
				tempnode=temp;			
			}
			
		}
	}
	
	return tempnode;
}

void cluster(List *my_list,int ele)
{
	int vertice=count_vertices("graph.txt");
	int cluster= ceil((float)vertice/(float)ele);
	int i,j,count=0;
	List *buffer;
	List *temp=my_list;
	Node *max_node;
	sum_it(my_list);
	for(i=0;i<cluster;i++)
	{
		temp=max_sum(my_list);
		//printf("v%d ",temp->vertice_no);
		temp->is_visited=1;
		printf("cluster %d:",i+1);
		printf("V%d\t",temp->vertice_no);
		count++;
		
		{

			for(j=0;j<ele-1;j++)
			{
				
				max_node=max_weight(my_list,temp);
				
				buffer=search_vertice(my_list,max_node->connect);
				buffer->is_visited=1;
				count++;
				if(count<=vertice)
					printf("V%d\t",max_node->connect);
			}
			printf("\n");
		}	
	}
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
		printf("%d >>> (%d)",(my_list+i)->vertice_no,(my_list+i)->sum );
		for(temp=(my_list+i)->head;temp!=NULL;temp=temp->ptr)
		{
			
			printf("%d with weight: %d\t",temp->connect,temp->weight);
		}
		printf("\n");
	}
}

List * deallocate(List *my_list)
{
	Node *temp;
	temp=my_list->head;

	while(my_list->head!=NULL)
	{
		my_list->head=my_list->head->ptr;
		free(temp);
		
		temp=my_list->head;
	}
	free(my_list);
	return NULL;

}


