#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"try.h"

int main()
{
	FILE *ptr;
	int i,j,size,arr[100];
	My_arr *my_arr;
	char index[10];

	ptr=fopen("text.txt","r");
	
	fscanf(ptr,"%d",&size);
	my_arr=init(size);

	for(i=0;i<size;i++)
	{
		fscanf(ptr,"%s",index);
		for(j=0;j<size;j++)
		{
			fscanf(ptr,"%d",&arr[j]);
		}
		add_data(my_arr,arr ,index);
	}
	
	display(my_arr);

	cluster(my_arr,3);
	close(ptr);
	return 0;
}
