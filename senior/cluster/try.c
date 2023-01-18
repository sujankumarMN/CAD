#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"try.h"

My_arr *init(int size)
{
	My_arr *my_arr;
	my_arr=(My_arr *)malloc(sizeof(My_arr));
	my_arr->my_type=(My_type*)malloc(sizeof(My_type)*size);
	my_arr->count=0;
	my_arr->size=size;
	return my_arr;
}
void add_data(My_arr *my_arr,int *arr ,char *index)
{
	int i,size=my_arr->size;
	strcpy(my_arr->my_type[my_arr->count].index,index);
	for(i=0;i<size;i++)
	{
		my_arr->my_type[my_arr->count].connect[i]=arr[i];
	}
	my_arr->count++;
}
void display(My_arr *my_arr)
{
	int i,j,size=my_arr->size;
	for(i=0;i<size;i++)
	{
		printf("%s\t",my_arr->my_type[i].index);
		for(j=0;j<size;j++)
		{
			printf("%d\t",my_arr->my_type[i].connect[j]);
		}
		printf("\n");
	}
}

int find_max_connect(My_arr *my_arr,int *done)
{
	int i,j,sum=0,size=my_arr->size,max=0,index=-1;
	for(i=0;i<size;i++)
	{	
		sum=0;
		if(done[i]==0)
		{
			for(j=0;j<size;j++)
			{
				sum=sum+my_arr->my_type[i].connect[j];
			}
			if(max<=sum)
			{
				max=sum;
				index=i;
			}
		}
	}
	return index;
}

int find_relate(My_type my_type,int size,int *done)
{
	int i,max=0,index=-1;
	for(i=0;i<size;i++)
	{
		if(done[i]==0)
		{
			if(max<=my_type.connect[i])
			{
				max=my_type.connect[i];
				index=i;
			}
		}
	}
	return index;
}

int sum_(int *done,int size)
{
	int i,sum=0;
	for(i=0;i<size;i++)
	{
		sum=sum+done[i];
	}
	return sum;
}

find_not_done(My_arr *my_arr,int *done)
{
	int i;
	for(i=0;i<my_arr->size;i++)
	{
		if(done[i]==0)
			return i;
	}
}

void cluster(My_arr *my_arr,int number_node)
{
	int i,j,index,sub_index,done[100]={0},clust=my_arr->size/number_node;
		printf("clustering...\n");
	for(i=0;i<clust;i++)
	{
		index=find_max_connect(my_arr,done);
		done[index]=1;
		printf("%s\t",my_arr->my_type[index].index);

		for(j=0;j<number_node-1;j++)
		{
			sub_index=find_relate(my_arr->my_type[index],my_arr->size,done);
			if(sub_index!=-1)
			{
				done[sub_index]=1;
				printf("%s\t",my_arr->my_type[sub_index].index);
			}
			/*
			else
			{
				//sub_index=find_not_done(my_arr,done);
				done[sub_index]=1;
				printf("%s\t",my_arr->my_type[sub_index].index);
			}
			*/
		}
		printf("\n");
	}

	while(sum_(done,my_arr->size)!=my_arr->size)
	{
		printf("this node is added to the last partition\n");
		index=find_not_done(my_arr,done);
		done[index]=1;
		printf("%s\n",my_arr->my_type[index].index);
	}
	

}
