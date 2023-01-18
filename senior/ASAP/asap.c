#include<stdio.h>
#include<stdlib.h>
#include"list.h"

List * initialize_list()
{
	List * my_list;
	my_list=(List *)malloc(sizeof(List));
	my_list->head=NULL;
	my_list->tail=NULL;
	my_list->count=0;
	
	return my_list;
}

Node * get_node(int vertex_no,int pd1,int pd2)
{
	Node * new_node;
	new_node=(Node *)malloc(sizeof(Node));
	new_node->vertex_no=vertex_no;
	new_node->pd1=pd1;
	new_node->pd2=pd2;
	new_node->e=-1;   //IMPORTANT: initially e is -1 for all nodes
	new_node->ptr=NULL;
	
	return new_node;
	
}

int insert_node(List * my_list,int vertex_no,int pd1,int pd2)  //inserting at end
{
	Node *my_node;
	my_node=get_node(vertex_no,pd1,pd2);
	if(my_node==NULL)
		return 0;
	if(my_list->count==0)
		my_list->head=my_list->tail=my_node;
	else
	{
		my_list->tail->ptr=my_node;
		my_list->tail=my_node;
	}
	my_list->count++;
	
	return 1;
}

int asap(List * my_list)
{
	Node * temp;

	int temp1,temp2,result;

	for(temp=my_list->head;temp!=NULL;temp=temp->ptr)// whichever node 
	{//does not have any predecessor it's e will be updated to 0;
		if((temp->pd1==0)&&(temp->pd2==0))
			temp->e=1;
	}
	for(temp=my_list->head;temp!=NULL;temp=temp->ptr)//checks rest nodes
	{
		if(temp->e!=0)// should not check already shedules nodes
		{
			temp1=get_e(my_list,temp->pd1);// sheduling remaining
			temp2=get_e(my_list,temp->pd2);// nodes
			result=max(temp1,temp2);
			temp->e=result+1;
		}	
	}
	printf("ASAP scheduled graph is as follows\n");
	for(temp=my_list->head;temp!=NULL;temp=temp->ptr)//display whole list
	{
		printf("%d is schedules in %d step\n",temp->vertex_no,temp->e);
	}
	return 1;	
}

int  get_e(List * my_list,int pd)
{
	Node * temp;
	for(temp=my_list->head;temp!=NULL;temp=temp->ptr)
	{
		if(temp->vertex_no==pd)
			return temp->e;
	}
	return 0;
}

int max(int a,int b)
{
	if(a>=b)
		return a;
	else
		return b;
}
