#include<stdio.h>
#include<stdlib.h>
#include"alap.h"

List * initialize_list()
{
	List * my_list;
	my_list=(List *)malloc(sizeof(List));
	my_list->head=NULL;
	my_list->tail=NULL;
	my_list->count=0;
	
	return my_list;
}

Node * get_node(int data,int sc)
{
	Node * new_node;
	new_node=(Node *)malloc(sizeof(Node));
	new_node->data=data;
	new_node->sc=sc;
	new_node->l=-1;   //IMPORTANT: initially l is -1 for all nodes
	new_node->ptr=NULL;
	
	return new_node;
	
}

int insert_node(List * my_list,int data,int sc)  //inserting at end
{
	Node *my_node;
	my_node=get_node(data,sc);
	if(my_node==NULL)
		return 0;
	if(my_list->count==0)
		my_list->head=my_list->tail=my_node;
	else
	{
		my_node->ptr=my_list->head;
		my_list->head=my_node;
	}
	my_list->count++;
	
	return 1;
}

int alap(List * my_list,int max_time)
{
	Node * temp;
	int temp1;
	for(temp=my_list->head;temp!=NULL;temp=temp->ptr)
	{//does not have any successor it's l will be updated to max time T;
		if(temp->sc==0)
			temp->l=max_time;//update l to T
	}
	for(temp=my_list->head;temp!=NULL;temp=temp->ptr)//checks rest nodes
	{
		if(temp->l!=max_time)
		{
			temp1=get_l(my_list,temp->sc);
			temp->l=temp1-1;
		}
	}
	printf("ALAP scheduled graph is as follows\n");
	for(temp=my_list->head;temp!=NULL;temp=temp->ptr)//display whole list
	{
		printf("%d is scheduled in %d step\n",temp->data,temp->l);
	}
	return 1;
}

int get_l(List  * my_list,int sc)
{
	Node * temp;
	for(temp=my_list->head;temp!=NULL;temp=temp->ptr)
	{
		if(temp->data==sc)
			return temp->l;
	}
	return 0;
}
