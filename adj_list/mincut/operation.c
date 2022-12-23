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
		(my_list+i)->edge_count=0;
		(my_list+i)->visited=0;
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

void random_selection_elements(List *my_list, int n)
{
	int vertices=count_vertices("graph.txt");
	int cluster = ceil((float)vertices/(float)n);
	int i,j,k,count=0;
	for(i=1;i<=cluster;i++)
	{
		
		printf("cluster %d:",i);
		for(j=0;j<n;j++)
			{
				k=rand()%(vertices);
				if((my_list+k)->visited==1)
				{
					
					j--; 
					if(count==(vertices))
						break;
					continue;
				}
				else
				{
					(my_list+k)->visited=1;
					if(k<vertices)
					{
						printf(" %d,",(my_list+k)->vertice_no);
						count++;						
					}
				}				
			}
			printf("\n");
	}
}
void random_selection_cluster(List *my_list, int cluster)
{
	int vertices=count_vertices("graph.txt");
	int n = ceil((float)vertices/(float)cluster);
	int i,j,k,count=0;
	for(i=1;i<=cluster;i++)
	{
		
		printf("cluster %d:",i);
		for(j=0;j<n;j++)
			{
				k=rand()%(vertices);
				if((my_list+k)->visited==1)
				{
					
					j--; 
					if(count==(vertices))
						break;
					continue;
				}
				else
				{
					(my_list+k)->visited=1;
					if(k<vertices)
					{
						printf(" %d,",(my_list+k)->vertice_no);
						count++;						
					}
				}				
			}
			printf("\n");
	}
}

void mincut(List *my_list)
{
	int vertices=count_vertices("graph.txt");
	int n = ceil((float)vertices/(float)2);
	int i,j=0,k,count=0,p,m;
	int a,b;
	int cluster1[n];
	if(vertices%2==0)
		m=n;
	else
		m=n-1;
	int cluster2[m];
	for(i=0;i<vertices;i++)
	{
		k=rand()%(vertices);
				if((my_list+k)->visited==1)
				{
					
					i--; 
					if(count==(vertices))
						break;
					continue;
				}
				else
				{
					(my_list+k)->visited=1;
					if(count<n)
					{
						//printf(" %d,",(my_list+k)->vertice_no);
						cluster1[i]=(my_list+k)->vertice_no;

						count++;						
					}
					else
					{
						cluster2[j]=(my_list+k)->vertice_no;
						j++;
						count++;
					}
				}
				
	}
	printf("\nCLUSTER 1:");
	for(p=0;p<n;p++)
					printf("%d ",cluster1[p]);
	printf("\nCLUSTER 2:");
	for(p=0;p<m;p++)
					printf("%d ",cluster2[p]);

	int index_i,index_j;
	int ICi=0,ECi=0,Di=0,Cij=0;
	int ICj=0,ECj=0,Dj=0;
	int gain;
	index_i=n/2;
	index_j=m/2;
	List * temp;
	Node * tempnode;
	printf("\nVi=%d, Vj=%d",cluster1[index_i],cluster2[index_j]);

	temp=search_vertice(my_list,cluster1[index_i]);
	for(tempnode=temp->head;tempnode!=NULL;tempnode=tempnode->ptr)
	{
		if(tempnode->connect == cluster2[index_j])
			{
				Cij++;
			}
		for(i=0;i<n;i++)
		{
			if(tempnode->connect == cluster1[i])
			{
				ICi++;
			}
			
		}
		for(i=0;i<m;i++)
		{
			if(tempnode->connect == cluster2[i])
			{
				ECi++;
			}
		}

	}
	Di=ECi-ICi;
	printf("\nDi=%d",Di);

	temp=search_vertice(my_list,cluster2[index_j]);
	for(tempnode=temp->head;tempnode!=NULL;tempnode=tempnode->ptr)
	{
		for(i=0;i<n;i++)
		{
			if(tempnode->connect == cluster2[i])
			{
				ICj++;
			}
			
		}
		for(i=0;i<m;i++)
		{
			if(tempnode->connect == cluster1[i])
			{
				ECj++;
			}
		}

	}
	Dj=ECj-ICj;
	gain=Di+Dj-(2*Cij);
	printf("\nDj=%d",Dj);
	printf("\nCij=%d",Cij);
	printf("\ngain=%d",gain);


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
			
			printf("%d with weight: %d\t ",temp->connect,temp->weight);
		}
		printf("\n");
	}

		

}
