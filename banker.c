#include<stdio.h>
#include<stdlib.h>

void print_output(int x[][10],int n,int m)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		printf("\n");
		for(j=0;j<m;j++)
		{
			printf("%d\t",x[i][j]);
		}
	}	
}


void resource_request(int Allocation[10][10],int Need[10][10],int AV[10][10],int process_id,int m)
{
	int request_matrix[1][10];
	int i;
	printf("\n additional request :- \n");
	for(i=0;i<m;i++)
	{
		printf(" Request resource %d : ",i+1);
		scanf("%d",&request_matrix[0][i]);
	}
	
	for(i=0;i<m;i++)
		if(request_matrix[0][i] > Need[process_id][i])
		{
			printf("\n Err encounter\n");
			exit(0);
		}

	for(i=0;i<m;i++)
		if(request_matrix[0][i] > AV[0][i])
		{
			printf("\n Resources unavailable.\n");
			exit(0);
		}
	
	for(i=0;i<m;i++)
	{
		AV[0][i]-=request_matrix[0][i];
		Allocation[process_id][i]+=request_matrix[0][i];
		Need[process_id][i]-=request_matrix[0][i];
	}
}


int safety_algo(int Allocation[][10],int Need[][10],int AV[1][10],int n,int m,int a[])
{

	int i,j,k,x=0;
	int F[10],Available[1][10];
	int pflag=0,flag=0;
	for(i=0;i<n;i++)
		F[i]=0;
	for(i=0;i<m;i++)
		Available[0][i]=AV[0][i];

	for(k=0;k<n;k++)
	{
		for(i=0;i<n;i++)
		{
			if(F[i] == 0)
			{
				flag=0;
				for(j=0;j<m;j++)
				{
					if(Need[i][j] > Available[0][j])
						flag=1;
				}
				if(flag == 0 && F[i] == 0)
				{
					for(j=0;j<m;j++)
						Available[0][j]+=Allocation[i][j];
					F[i]=1;
					pflag++;
					a[x++]=i;
				}
			}
		}
		if(pflag == n)
			return 1;
	}
	return 0;
}



void input_info(int Allocation[][10],int Need[][10],int Maximum[10][10],int Available[1][10],int *n,int *m)
{
	int i,j;
	printf("\n Enter total no. of process : ");
	scanf("%d",n);
	printf("\n Enter total no. of resources : ");
	scanf("%d",m);
	for(i=0;i<*n;i++)
	{
		printf("\n Process %d\n",i+1);
		for(j=0;j<*m;j++)
		{
			printf(" Allocation for resource %d : ",j+1);
			scanf("%d",&Allocation[i][j]);
			printf(" Maximum for resource %d : ",j+1);
			scanf("%d",&Maximum[i][j]);
		}
	}
	printf("\n Available resources : \n");
	for(i=0;i<*m;i++){
		printf(" Resource %d : ",i+1);
		scanf("%d",&Available[0][i]);
	}

	for(i=0;i<*n;i++)
		for(j=0;j<*m;j++)
			Need[i][j]=Maximum[i][j]-Allocation[i][j];

	printf("\n Allocation Matrix");
	print_output(Allocation,*n,*m);
	printf("\n Maximum Requirement Matrix");
	print_output(Maximum,*n,*m);
	printf("\n Need Matrix");
	print_output(Need,*n,*m);

}

int banker_algo(int Allocation[][10],int Need[][10],int Available[1][10],int n,int m)
{
	int j,i,a[10];
	j=safety_algo(Allocation,Need,Available,n,m,a);
	if(j != 0 )
	{
		printf("\n\n");
		for(i=0;i<n;i++)
		     printf(" P%d  ",a[i]);
		printf("\n A safety sequence has detected.\n");
		return 1;
	}
	else
	{
		printf("\n Deadlock occured.\n");
		return 0;
	}
}


int main(){
	int output;
	int Allocation[10][10];
	int Maximum[10][10];
	int Need[10][10];
	int Available[1][10];
	int n,m,process_id,choice;
	printf("\n \t BANKER'S Algo\n");
	input_info(Allocation,Need,Maximum,Available,&n,&m);
	output=banker_algo(Allocation,Need,Available,n,m);
	if(output !=0 ){
		printf("\n Do you want make an additional request ? (1=Yes|0=No)");
		scanf("%d",&choice);
		if(choice == 1)
		{
			printf("\n Enter process no. : ");
			scanf("%d",&process_id);
			resource_request(Allocation,Need,Available,process_id-1,m);
			output=banker_algo(Allocation,Need,Available,n,m);
			if(output == 0 )
				exit(0);
		}
	}
	else
		exit(0);
	return 0;
}
