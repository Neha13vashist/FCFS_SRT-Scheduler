#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>

const int MAX_BUFFER_TIME = 100;

typedef struct Process
{
	int Process_Id;
	int Arrival_Time;
	int Burst_Time;
	int Waiting_Time;
	int Turnaround_Time;
	int flag;
}pr;

int n;
pr P[10];
void Process_info(int);
void FCFS();
void FCFS_Algo(struct Process *, int);
void Display_Gantt();
void SJF_sort();
void round_robin(int);

int main()
{
	printf("Enter the number of processes : ");
	scanf("%d",&n);
	if(n>10)
	{
		printf("You have exceeded the max. limit of processes to be executed");
	}
	else
	{
		Process_info(n);
	}
	return 0;
}

void Process_info(int a)
{
	int i;
	printf("Enter the arrival time and Burst time for the processes\n");
	for(i=0;i<a;i++)
	{
		printf("\tEnter for Process %d :",i);
		scanf("%d%d",&P[i].Arrival_Time,&P[i].Burst_Time);
		P[i].Process_Id=i;
	}
	FCFS();
}


void FCFS_Algo(struct Process *P,int n)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(P[j].Arrival_Time>P[i].Arrival_Time)
			{
				struct Process t = P[i];
				P[i] = P[j];
				P[j] = t;
			}
		}
	}
}

void FCFS(){
	printf("\n\n===========================================================================");
	printf("\n\t\tFirst Come First Serve\t");
	printf("\n===========================================================================\n\n");
	FCFS_Algo(&P,n);
	for(int i=0;i<n;i++)
	{
		printf("%d\t%d\n",P[i].Arrival_Time,P[i].Burst_Time);
	}
}



